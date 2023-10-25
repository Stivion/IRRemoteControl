#include "WirelessServer.hpp"

IRRemoteControl::WirelessServer::WirelessServer(uint16_t port) : _port(port) {}

bool IRRemoteControl::WirelessServer::connectToWiFi(const char* ssid, const char* password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    wl_status_t wifiStatus = WiFi.status();
    uint16_t iterationsLimit = 60;
    uint16_t i = 0;
    while (wifiStatus == WL_DISCONNECTED && i++ != iterationsLimit) { 
        delay(500);
        wifiStatus = WiFi.status();
    }

    return wifiStatus == WL_CONNECTED;
}

void IRRemoteControl::WirelessServer::mapGet(const char* route, void (*handler)()) {
    _server.on(route, HTTP_GET, handler);
}

void IRRemoteControl::WirelessServer::mapPost(const char* route, void (*handler)()) {
    _server.on(route, HTTP_POST, handler);
}

void IRRemoteControl::WirelessServer::mapPatch(const char* route, void (*handler)()) {
    _server.on(route, HTTP_PATCH, handler);
}

void IRRemoteControl::WirelessServer::sendStatusCode(uint16_t statusCode) {
    _server.send(statusCode);
}

void IRRemoteControl::WirelessServer::sendJson(uint16_t statusCode, String json) {
    _server.send(statusCode, "application/json", json);
}

String IRRemoteControl::WirelessServer::getRawBody() {
    return _server.arg("plain");
}

void IRRemoteControl::WirelessServer::begin() {
    _server.begin();
}

void IRRemoteControl::WirelessServer::run() {
    _server.handleClient();
}

bool IRRemoteControl::WirelessServer::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void IRRemoteControl::WirelessServer::printError(Print& p) {
    String statusName = getStatusName(WiFi.status());
    p.println(
        F(
            "Unable to connect to WiFi network.\r\n"
            "List of status codes: \r\n"
            "WL_IDLE_STATUS: Wi-Fi is in process of changing between statuses.\r\n"
            "WL_NO_SSID_AVAIL: configured SSID can't be reached.\r\n"
            "WL_CONNECTED: successfully connected.\r\n"
            "WL_CONNECT_FAILED: connection failed.\r\n"
            "WL_CONNECT_WRONG_PASSWORD: incorrect password.\r\n"
            "WL_DISCONNECTED: module is not configured."
        )
    );

    p.print("Current Wi-Fi status is: ");
    p.println(statusName);
}

String IRRemoteControl::WirelessServer::getStatusName(wl_status_t status) {
    switch (status) {
        case WL_IDLE_STATUS:
            return "WL_IDLE_STATUS";
        case WL_NO_SSID_AVAIL:
            return "WL_NO_SSID_AVAIL";
        case WL_CONNECTED:
            return "WL_CONNECTED";
        case WL_CONNECT_FAILED:
            return "WL_CONNECT_FAILED";
        case WL_WRONG_PASSWORD:
            return "WL_WRONG_PASSWORD";
        default:
            return "WL_DISCONNECTED";
    }
}
