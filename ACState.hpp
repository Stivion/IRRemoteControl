#pragma once

namespace IRRemoteControl {

    struct ACState {
        struct ACSwingState {
            bool automatic;
            uint8_t position; // 1 - auto, 7 - down auto, 9 - middle auto, 11 - up auto, 2 - up, 3 - middle up, 4 - middle, 5 - middle down, 6 - down
        };

        bool power;
        uint8_t tempC; // 16 - 30 degrees
        uint8_t fan; // 0 - auto 1 - 3 from lowest to highest speeds
        uint8_t mode; // 0 - auto, 2 - dry (wet), 1 - cool, 3 - fan, 5 - econo, 4 - heat. // My ac doesn't have econo mode, it is enabled separatelly.
        bool light;
        bool xFan;
        bool sleep;
        bool turbo;
        bool iFeel;
        ACSwingState swing;
        uint16_t timerMinutes; // 0 - 1440 minutes. minimal step is 30 minutes
        uint8_t displayTempSource; // 0 - off (most probable), 1 - set temp, 2 - temp inside
    };

}
