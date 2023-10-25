#pragma once

#include "ACState.hpp"

#include <IRsend.h>
#include <ir_Gree.h>

namespace IRRemoteControl {

    class IREmitter {
    public:
        IREmitter(const uint16_t sendPin);

        void sendSoundbar(uint64_t data);
        void sendAC(const IRRemoteControl::ACState& state);

    private:
        uint16_t _sendPin;
        IRsend _soundbarControl { _sendPin };
        IRGreeAC _acControl { _sendPin };
    };

}
