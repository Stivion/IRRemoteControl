#pragma once

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include <map>
#include <optional>
#include <vector>

namespace IRRemoteControl {

    class WirelessServer {
    public:
        WirelessServer(uint16_t port);

        bool connectToWiFi(const char* ssid, const char* password);
        void mapGet(const char* route, void (*handler)());
        void mapPost(const char* route, void (*handler)());
        void mapPatch(const char* route, void (*handler)());
        void sendStatusCode(uint16_t statusCode);
        void sendJson(uint16_t statusCode, String json);
        String getRawBody();
        void begin();
        void run();

        bool isConnected();
        void printError(Print& p);
        String getStatusName(wl_status_t status);

    private:
        uint16_t _port;
        ESP8266WebServer _server { _port };
    };
}
