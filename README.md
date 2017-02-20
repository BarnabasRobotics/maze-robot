# maze-robot
The idea is an inexpensive, flexible robotic system which would allow a middle or high school aged person to build a robot capible of navigating and autonomously solving a maze.
This builds on the Barnabas Robotics Barnabas Car Kit.

Design goals:
*small, inexpensive four-wheeled car chassis
*Arduino Uno or compatible microcontroller board
*microcontroller board is programmable via bluetooth, through standard Arduino IDE
*five ultrasonic rangefinders.  two pointed to the left, two pointed to the right, one straight ahead
The rangefinders work well to show the distance to objects between around 1" to 6' away, but they have trouble when they aren't approximatley at a right angle to the object they are detecting.  If the angle is too great, over about 15 degrees not enough of the sound bounces back for it to get a range.

The current platform is being prototyped with cardboard and Lego bricks, but the production system is intended to be an acrylic rectangle or circle atop the Barnabas Robotics Car Chassis.

The idea is the two ultrasonic rangefinders on each side would let the robot drive parallel to walls, or centered between walls.  On finding a wall in front of it it could turn to the left or to the right, and the side ultrasonic sensors during the turn could let it aligh itself parallel to the wall, and during movement it would continuiously be aligning its path of travel parallel to the wall(s).  Abstraction is king, so it is desired that low level functions handle those messy details of interfacing to the real world, so beginners can solve a real-world maze with this physical robot with similar effort to solving the Blockly Games Maze https://blockly-games.appspot.com/maze

Optional features:
*switch to disable bluetooth to demonstrate autonomous operation during competition
*color sensor facing down, potentially maze could have checkerboard pattern of black or gray vs white so robot could better register cells it is entering to map out the course for optimal route planning, and potentially red for the starting slot and green for the finish spot
*RGB status light
*piezo beeper
*start button so robot would be idle until commanded to solve the maze

Note that the robot can communicate to and from a computer, tablet or smartphone over bluetooth, so this can be a remote control car or can even send telemetry or an autonomously plotted map of the maze.
