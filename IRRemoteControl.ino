#include <ArduinoJson.h>

#include "WirelessServer.hpp"
#include "IREmitter.hpp"
#include "SoundbarRemote.hpp"
#include "ACState.hpp"
#include "ACStateParser.hpp"
#include "ACRemote.hpp"

// BEGIN configurable parameters
// #define _DEBUG

const uint64_t BaudRate = 115200;

const char* WifiNetworkName = "";     // Set to your Wifi network name
const char* WifiNetworkPassword = ""; // Set to your Wifi network password

const uint16_t SoundbarEmitPin = 15; // D8
const uint16_t ACEmitPin = 16; // D0
const uint16_t WiFiServerPort = 80; // HTTP
// END configurable parameters

IRRemoteControl::WirelessServer _server(WiFiServerPort);
IRRemoteControl::IREmitter _soundbarEmitter(SoundbarEmitPin);
IRRemoteControl::IREmitter _acEmitter(ACEmitPin);
IRRemoteControl::SoundbarRemote _soundbarRemote(_soundbarEmitter);
IRRemoteControl::ACRemote _acRemote(_acEmitter);

void setup() {
#ifdef _DEBUG
    Serial.begin(BaudRate, SERIAL_8N1, SERIAL_TX_ONLY);
    // Wait for Serial connection to be established
    delay(10000);
#endif
    bool isConnected = _server.connectToWiFi(WifiNetworkName, WifiNetworkPassword);
    if (!isConnected) {
        // Enable builtin LED to display WiFi error
        pinMode(LED_BUILTIN, OUTPUT);
#ifdef _DEBUG
        _server.printError(Serial);
#endif
    }

#ifdef _DEBUG
    if (isConnected) {
        Serial.println("Successfully connected to WiFi");
    }
#endif

    // BEGIN map endpoints
    _server.mapPost("/soundbar/power",          []() { _soundbarRemote.power();         _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/toggle-input",   []() { _soundbarRemote.toggleInput();   _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/bluetooth-pair", []() { _soundbarRemote.bluetoothPair(); _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/up",             []() { _soundbarRemote.up();            _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/down",           []() { _soundbarRemote.down();          _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/left",           []() { _soundbarRemote.left();          _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/right",          []() { _soundbarRemote.right();         _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/play-pause",     []() { _soundbarRemote.playPause();     _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/mute",           []() { _soundbarRemote.mute();          _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/sound-mode",     []() { _soundbarRemote.soundMode();     _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/settings",       []() { _soundbarRemote.settings();      _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/volume-up",      []() { _soundbarRemote.volumeUp();      _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/volume-down",    []() { _soundbarRemote.volumeDown();    _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/subwoofer-up",   []() { _soundbarRemote.subwooferUp();   _server.sendStatusCode(204); });
    _server.mapPost("/soundbar/subwoofer-down", []() { _soundbarRemote.subwooferDown(); _server.sendStatusCode(204); });

    _server.mapPost("/ac/state", []() {
        String requestBody = _server.getRawBody();
        ArduinoJson::StaticJsonDocument<384> doc;
        ArduinoJson::DeserializationError error = ArduinoJson::deserializeJson(doc, requestBody);
        if (error) {
            String errorMessage = "{\"error\": \"Unable to deserialize request body: ";
            errorMessage += error.c_str();
            errorMessage += "\"}";

            uint16_t code = error == DeserializationError::Code::NoMemory ? 500 : 400;
            _server.sendJson(code, errorMessage);
            return;
        }

        IRRemoteControl::ACState state{};
        auto validationErrors = IRRemoteControl::ACStateParser::parse(doc, &state);
        if (!validationErrors.empty()) {
            DynamicJsonDocument json(2048);
            for (auto i = 0; i < validationErrors.size(); i++) {
                json[i]["error"] = validationErrors[i];
            }

            String output;
            ArduinoJson::serializeJson(json, output);
            _server.sendJson(400, output);
            return;
        }

        _acRemote.setState(state);
        _server.sendStatusCode(204);
    });

    _server.mapGet("/ac/state", []() {
        auto acState = _acRemote.getState();
        
        ArduinoJson::StaticJsonDocument<256> doc;
        doc["power"] = acState.power;
        doc["tempC"] = acState.tempC;
        doc["fan"] = acState.fan;
        doc["mode"] = acState.mode;
        doc["light"] = acState.light;
        doc["xFan"] = acState.xFan;
        doc["sleep"] = acState.sleep;
        doc["turbo"] = acState.turbo;
        doc["iFeel"] = acState.iFeel;
        ArduinoJson::JsonObject swing = doc.createNestedObject("swing");
        swing["automatic"] = acState.swing.automatic;
        swing["position"] = acState.swing.position;
        doc["timerMinutes"] = acState.timerMinutes;
        doc["displayTempSource"] = acState.displayTempSource;

        String output;
        ArduinoJson::serializeJson(doc, output);
        _server.sendJson(200, output);
    });
    // END map endpoints

    _server.begin();
}

void loop() {
    // Blink builtin LED to indicate that board couldn't connect to WiFi
    if (!_server.isConnected()) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        return;
    }

    _server.run();
}
