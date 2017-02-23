Parts list for Barnabas maze-robot.

Purchased Arduino R3 option:
- Arduino Uno R3  microcontroller development board

Custom PCB microcontroller option:
- Deluxe ISP-6 programming shrouded header: FCI 75869-131LF
- Piezo
- optional Tempearture Sensor: DS18B20
- optional right angle 1/10" header for FTDI cable instead of Bluetooth: 68015-106HLF
- Bluetooth Module - HC-05, HC-06 or similar.  Initially using with a carrier board and one soldered on wire for RTS (or possibly DTR).  RTS or DTR are used so the Arduino IDE can reset the microcontroller so the bootloader will be able to receive an uploaded sketch automatically.  RTS seems preferable due to it being software controlled, and recent Arduino IDE versions support it automatically.  (DTR is typically automatically controlled by the OS when the serial port is opened/closed, and causes a microcontroller reset every time the serial port is opened, which can be annoying.) 
- start button so robot will be idle until commanded to solve maze (@ericrlin 's idea)

Parts mounted to the Robot Chassis
- Motor controller board: L9110S, four motors with wheels
- 6x Ultrasonic Rangefinders https://www.robot-electronics.co.uk/htm/srf04tech.htm  Note the issue described at http://mc-computing.com/Hardware_Platforms/Arduino/HC-SR04_Ultrasonic_Sensor.html and the workaround provided.  Some of the HC-SR04 sensors have a bug where the device gets stuck if an echo is not heard.  I'm encountering that and other behavior that makes them seem unreliable.  A software fix fix would be most welcome.  Also if a hardware pullup is not present on some rangefinders I'm going to investigate using a software pull up provided by the AVR microcontroller or adding a hardware one.
- TCS230 color sensor http://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/
- optional bump sensor(s) to detect if robot has hit an obstacle


