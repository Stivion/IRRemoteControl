# IRRemoteControl
Firmware for ESP8266 microcontroller, that was built to control both Samsung soundbar and Gree-based AC via HTTP.

# Compiling
Project uses Arduino IDE and requires installed dependencies:
* ArduinoJSON (6.21.3)
* IRremoteESP8266 (2.8.6)

# Configurable parameters
`IRRemoteControl.ino` file contains a section with configurable parameters. Here you can change pins for emitting IR signals and provide Wifi network names and password.

Debug mode could be enabled by uncommenting `#define _DEBUG` line. This will enable printing to Serial monitor and also it will wait for 10 seconds at start to ensure that Serial monitor is connected.

# Devices
This project is designed to work specifically with my soundbar and AC devices. They are:
* Samsung HW-Q6CT
* Royal Clima Grida RC-GR28HN
