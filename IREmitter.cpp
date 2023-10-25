#include <Arduino.h>
#include "IREmitter.hpp"

IRRemoteControl::IREmitter::IREmitter(uint16_t sendPin) : _sendPin(sendPin) {
    _soundbarControl.begin(); // It will set pinMode for _sendPin
    _acControl.begin(); // It will set pinMode for _sendPin
}

void IRRemoteControl::IREmitter::sendSoundbar(uint64_t data) {
    _soundbarControl.sendSamsung36(data);
}

void IRRemoteControl::IREmitter::sendAC(const IRRemoteControl::ACState& state) {
    _acControl.setPower(state.power);
    _acControl.setTemp(state.tempC, false); // Use Celsius
    _acControl.setFan(state.fan);
    _acControl.setMode(state.mode);
    _acControl.setLight(state.light);
    _acControl.setXFan(state.xFan);
    _acControl.setSleep(state.sleep);
    _acControl.setTurbo(state.turbo);
    _acControl.setIFeel(state.iFeel);
    _acControl.setSwingVertical(state.swing.automatic, state.swing.position);
    _acControl.setTimer(state.timerMinutes);
    _acControl.setDisplayTempSource(state.displayTempSource);

    _acControl.send();
}
