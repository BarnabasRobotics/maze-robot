# maze-robot
The idea is an inexpensive, flexible robotic system which would allow people to build and program a robot capible of navigating and autonomously solving a maze!
This builds on the [Barnabas Robotics](https://www.barnabasrobotics.com/) -> [Barnabas Racer](https://shop.barnabasrobotics.com/collections/robots-and-coding/products/barnabas-racer-arduino-compatible-2wd-servo-motor-car-kit-ages-11).

Design goals:
- Small, inexpensive two-wheeled car chassis.  Two drive wheels, one or two caster wheels.
- Arduino Uno or compatible microcontroller board
- Microcontroller board is programmable via bluetooth, through standard Arduino IDE
- Six ultrasonic rangefinders.  Two pointed to the left, two pointed to the right, one straight ahead, one to the rear.  The rangefinders work well to show the distance to objects from around 1 inch (2 cm) to around 9 feet away (3 meters), but they have trouble when they aren't approximatley at a right angle to the object they are detecting.  If the angle is too great (over about 15 degrees) not enough of the sound bounces back for it to get a reliable range.

The current platform is being prototyped with cardboard and hot glue, but the production system is intended to be an acrylic 6" or 8" circle atop the Barnabas Robotics Car Chassis.  The current prototype uses M3 standoffs to the aluminum chassis and M2 standoffs to the ultrasonic rangefinders.

The idea is the two ultrasonic rangefinders on each side would let the robot drive parallel to one wall or centered between walls.  On finding a wall in front of it it could turn to the left or to the right, and the side ultrasonic sensors during the turn could let it aligh itself parallel to the wall, and during movement it would continuiously be aligning its path of travel parallel to the wall(s).

Abstraction is king, so it is desired that low level functions handle the messy details of interfacing with the real world, so beginners can solve a real-world maze with this physical robot with similar effort to solving the Blockly Games Maze https://blockly-games.appspot.com/maze

Inital motors were gearbox construction in micro-servo form factor run from a small H-bridge controller, but they proved unsatisfactory.  The current testing is with micro-servo continuious rotation servos.  This takes the I/O for two wheels from four to two pins.

Optional features:
- Switch to disable bluetooth to demonstrate autonomous operation during competition
- Color sensor facing down, potentially maze could have checkerboard pattern of black vs white so robot could better register cells it is entering to map out the course for optimal route planning, and potentially green for the starting slot and red for the finish spot.
- RGB status light
- direction indicating lights - one on each side to show which way the robot is trimming as it is walking parallel to a wall
- Piezo beeper
- Start button so robot would be idle until commanded to solve the maze.
- header so board can be built to use FTDI USB to TTL Serial cable rather than Bluetooth
- Optional pre-paired USB to Bluetooth dongle, to help with classroom use.  For home use pairing the computer to the robot makes sense, one less thing to loose, but for a classroom we want to prevent pairing with the wrong robot, so having a unique name and password set on the robot's bluetooth device which match a labeled USB to Bluetooth dongle will make the class go better - you have robot 1, you get Bluetooth dongle 1.

Note that the robot can communicate to and from a computer, tablet or smartphone over bluetooth, so this can be a remote control car or can even send telemetry or an autonomously plotted map of the maze.
