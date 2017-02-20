Parts list for Barnabas maze-robot.

Purchased Arduino R3 option:
- Arduino Uno R3  microcontroller development board

Custom PCB microcontroller option:
- Deluxe ISP-6 programming shrouded header: FCI 75869-131LF
- Piezo
- optional Tempearture Sensor: DS18B20
- optional right angle 1/10" header for FTDI cable instead of Bluetooth: 68015-106HLF
- Bluetooth Module - HC-05, HC-06 or similar.  Initially using with a carrier board and one soldered on wire for RTS (or possibly DTR).  RTS or DTR are used so the Arduino IDE can reset the microcontroller so the bootloader will be able to receive an uploaded sketch automatically.  RTS seems preferable due to it being software controlled, and recent Arduino IDE versions support it automatically.  (DTR is typically automatically controlled by the OS when the serial port is opened/closed, and causes a microcontroller reset every time the serial port is opened, which can be annoying.) 
- start button so robot will be idle until commanded to solve maze (@ericrlin's idea)

Parts mounted to the Robot Chassis
- Motor controller board: L9110S, four motors with wheels
- 5x Ultrasonic Rangefinders
- TCS230 color sensor http://howtomechatronics.com/tutorials/arduino/arduino-color-sensing-tutorial-tcs230-tcs3200-color-sensor/
- optional bump sensor(s) to detect if robot has hit an obstacle


