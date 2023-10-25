#pragma once

#include "IREmitter.hpp"

namespace IRRemoteControl {

    class SoundbarRemote {
    public:
        SoundbarRemote(IRRemoteControl::IREmitter& emitter) : _emitter(emitter) {}

        void power()         { sendButton(IRRemoteControl::SoundbarRemote::Button::Power);         }
        void toggleInput()   { sendButton(IRRemoteControl::SoundbarRemote::Button::ToggleInput);   }
        void bluetoothPair() { sendButton(IRRemoteControl::SoundbarRemote::Button::BluetoothPair); }
        void up()            { sendButton(IRRemoteControl::SoundbarRemote::Button::Up);            }
        void down()          { sendButton(IRRemoteControl::SoundbarRemote::Button::Down);          }
        void left()          { sendButton(IRRemoteControl::SoundbarRemote::Button::Left);          }
        void right()         { sendButton(IRRemoteControl::SoundbarRemote::Button::Right);         }
        void playPause()     { sendButton(IRRemoteControl::SoundbarRemote::Button::PlayPause);     }
        void mute()          { sendButton(IRRemoteControl::SoundbarRemote::Button::Mute);          }
        void soundMode()     { sendButton(IRRemoteControl::SoundbarRemote::Button::SoundMode);     }
        void settings()      { sendButton(IRRemoteControl::SoundbarRemote::Button::Settings);      }
        void volumeUp()      { sendButton(IRRemoteControl::SoundbarRemote::Button::VolumeUp);      }
        void volumeDown()    { sendButton(IRRemoteControl::SoundbarRemote::Button::VolumeDown);    }
        void subwooferUp()   { sendButton(IRRemoteControl::SoundbarRemote::Button::SubwooferUp);   }
        void subwooferDown() { sendButton(IRRemoteControl::SoundbarRemote::Button::SubwooferDown); }

    private:
        IRRemoteControl::IREmitter& _emitter;

        // Codes was extracted using https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRrecvDumpV3/IRrecvDumpV3.ino
        enum Button {
            Power          = 0xCF000EF1,
            ToggleInput    = 0xCF00AE51,
            BluetoothPair  = 0xCF00ED12,
            Up             = 0xCF002DD2,
            Down           = 0xCF00AD52,
            Left           = 0xCF000DF2,
            Right          = 0xCF008D72,
            PlayPause      = 0xCF0051AE,
            Mute           = 0xCF008E71,
            SoundMode      = 0xCF00DE21,
            Settings       = 0xCF00659A,
            VolumeUp       = 0xCF00EE11,
            VolumeDown     = 0xCF001EE1,
            SubwooferUp    = 0xCF0041BE,
            SubwooferDown  = 0xCF00C13E
        };

        void sendButton(IRRemoteControl::SoundbarRemote::Button button) { _emitter.sendSoundbar(button); }
    };

}
