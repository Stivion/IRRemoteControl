#pragma once

#include <vector>
#include <ArduinoJson.h>

#include "ACState.hpp"
#include "ACRemote.hpp"

namespace IRRemoteControl {

    class ACStateParser {
    public:
        ACStateParser() = delete;

        static std::vector<String> parse(const ArduinoJson::StaticJsonDocument<384> json, IRRemoteControl::ACState* outState) {
            std::vector<String> validationErrors;

            auto power = json["power"];
            if (power.is<bool>()) { outState->power = power.as<bool>(); }
            else { validationErrors.emplace_back("Field \"power\" must be a boolean"); }

            auto tempC = json["tempC"];
            if (tempC.is<uint8_t>()) {
                uint8_t tempCInt = tempC.as<uint8_t>();
                if (tempCInt < 16 || tempCInt > 30) { validationErrors.emplace_back("Field \"tempC\" must be in range [16, 30]"); }
                else { outState->tempC = tempCInt; }
            } else {
                validationErrors.emplace_back("Field \"tempC\" must be of an unsigned byte type");
            }

            auto fan = json["fan"];
            if (fan.is<uint8_t>()) {
                uint8_t fanInt = fan.as<uint8_t>();
                if (fanInt > 3) { validationErrors.emplace_back("Field \"fan\" must be in range [0, 4]"); }
                else { outState->fan = fanInt; }
            } else {
                validationErrors.emplace_back("Field \"fan\" must be of an unsigned byte type");
            }

            auto mode = json["mode"];
            if (mode.is<uint8_t>()) {
                uint8_t modeInt = mode.as<uint8_t>();
                if (modeInt > 4) { validationErrors.emplace_back("Field \"mode\" must be in range [0, 4]"); }
                else { outState->mode = modeInt; }
            } else {
                validationErrors.emplace_back("Field \"mode\" must be of an unsigned byte type");
            }

            auto light = json["light"];
            if (light.is<bool>()) { outState->light = light.as<bool>(); }
            else { validationErrors.emplace_back("Field \"light\" must be a boolean"); }

            auto xFan = json["xFan"];
            if (xFan.is<bool>()) { outState->xFan = xFan.as<bool>(); }
            else { validationErrors.emplace_back("Field \"xFan\" must be a boolean"); }

            auto sleep = json["sleep"];
            if (sleep.is<bool>()) { outState->sleep = sleep.as<bool>(); }
            else { validationErrors.emplace_back("Field \"sleep\" must be a boolean"); }

            auto turbo = json["turbo"];
            if (turbo.is<bool>()) { outState->turbo = turbo.as<bool>(); }
            else { validationErrors.emplace_back("Field \"turbo\" must be a boolean"); }

            auto iFeel = json["iFeel"];
            if (iFeel.is<bool>()) { outState->iFeel = iFeel.as<bool>(); }
            else { validationErrors.emplace_back("Field \"iFeel\" must be a boolean"); }

            IRRemoteControl::ACState::ACSwingState swingState{};
            auto swing = json["swing"];
            if (swing.isNull()) { validationErrors.emplace_back("Object \"swing\" must not be null"); }
            else {
                auto swingAutomatic = swing["automatic"];
                if (swingAutomatic.is<bool>()) { swingState.automatic = swingAutomatic.as<bool>(); }
                else { validationErrors.emplace_back("Field \"swing.automatic\" must be a boolean"); }

                auto swingPosition = swing["position"];
                if (swingPosition.is<uint8_t>()) {
                    uint8_t swingPositionInt = swingPosition.as<uint8_t>();
                    if (swingPositionInt < 1 || swingPositionInt == 8 || swingPositionInt == 10 || swingPositionInt > 11) {
                        validationErrors.emplace_back("Field \"swing.position\" must have one of the following values: [1, 2, 3, 4, 5, 6, 7, 9, 11]");
                    }
                    else {
                        swingState.position = swingPositionInt;
                    }
                } else {
                    validationErrors.emplace_back("Field \"swing.position\" must be of an unsigned byte type");
                }

                outState->swing = swingState;
            }

            auto timerMinutes = json["timerMinutes"];
            if (timerMinutes.is<uint16_t>()) {
                uint16_t timerMinutesInt = timerMinutes.as<uint16_t>();
                if (timerMinutesInt > 1440) { validationErrors.emplace_back("Field \"timerMinutes\" must be in range [0, 1440]"); }
                else if (timerMinutesInt % 30 != 0) { validationErrors.emplace_back("Field \"timerMinutes\" must be a multiple of 30"); }
                else { outState->timerMinutes = timerMinutesInt; }
            } else {
                validationErrors.emplace_back("Field \"timerMinutes\" must be of an unsigned short type");
            }

            auto displayTempSource = json["displayTempSource"];
            if (displayTempSource.is<uint8_t>()) {
                uint8_t displayTempSourceInt = displayTempSource.as<uint8_t>();
                if (displayTempSource > 2) { validationErrors.emplace_back("Field \"displayTempSource\" must be in range [0, 2]"); }
                else { outState->displayTempSource = displayTempSourceInt; }
            } else {
                validationErrors.emplace_back("Field \"displayTempSource\" must be of an unsigned byte type");
            }

            return validationErrors;
        }
    };
    
}
