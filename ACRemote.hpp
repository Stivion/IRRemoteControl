#pragma once

#include "IREmitter.hpp"
#include "ACState.hpp"

namespace IRRemoteControl {

    class ACRemote {
    public:
        ACRemote(IRRemoteControl::IREmitter& emitter) : _emitter(emitter) {
            // Set default state, see 'ACState.hpp' for additional details
            _state.power = false;
            _state.tempC = 24;
            _state.fan = 0;
            _state.mode = 3;
            _state.light = true;
            _state.xFan = false;
            _state.sleep = false;
            _state.turbo = false;
            _state.iFeel = false;
            _state.swing.automatic = true;
            _state.swing.position = 1;
            _state.timerMinutes = 0;
            _state.displayTempSource = 0;
        }

        void setState(const IRRemoteControl::ACState& state) {
            _state = state;
            _emitter.sendAC(state);
        }
        
        IRRemoteControl::ACState getState() { return _state; }

    private:
        IRRemoteControl::IREmitter& _emitter;
        IRRemoteControl::ACState _state;
    };

}
