// Barnabas Robotics Maze Robot
// started from NewPing v1.8 example sketch NewPing15Sensors

const byte ENABLE_MOTORS = 1;   // used to disable motors for software development and sensor test

#include <NewPing.h>
#include <Servo.h>

#define SONAR_NUM     6 // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 50 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

const byte motor_left_pin = 9;
const byte motor_right_pin = 10;

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[SONAR_NUM] = {      // Sensor object array.
                                  // Each sensor's trigger pin, echo pin, and max distance to ping.
                                  //
                                  // connect ultrasonic rangefinder pins as such:
                                  //
  NewPing(A0, A0, MAX_DISTANCE),  // left rear 
  NewPing(A1, A1, MAX_DISTANCE),  // left front 
  NewPing(A2, A2, MAX_DISTANCE),  // front
  NewPing(A3, A3, MAX_DISTANCE),  // right front
  NewPing(A4, A4, MAX_DISTANCE),  // right rear
  NewPing(A5, A5, MAX_DISTANCE),  // rear
};

void setup() 
{
  Serial.begin(115200);
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
  { 
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
  }

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT); 

  servo_left.attach(motor_left_pin);
  servo_right.attach(motor_right_pin);
}

void loop() 
{
  for (uint8_t i = 0; i < SONAR_NUM; i++)  // Loop through all the sensors.
  {
    if (millis() >= pingTimer[i])          // Is it this sensor's time to ping?
    {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = MAX_DISTANCE + 1;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  // Other code that *DOESN'T* analyze ping results can go here.
}

void echoCheck()  // If ping received, set the sensor distance to array.
{
  if (sonar[currentSensor].check_timer())
  {
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
  }
}

void oneSensorCycle()  // Sensor ping cycle complete, do something with the results.
{
  // The following code would be replaced with your code that does something with the ping results.
  
  
  for (uint8_t i = 0; i < SONAR_NUM; i++) 
  {
    Serial.print(cm[i]);
    Serial.print("cm\t");
  }
  //Serial.println();

  const byte HIGH_SPEED = 100;
  const byte LOW_SPEED = 50;

  if (1)
  {
    move_motors(HIGH_SPEED, HIGH_SPEED);
  }
  else if (cm[5] < 20) // if an obstacle is ahead
  {
    move_motors(0,0);
    Serial.println("Stop.");
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);

  }
  else if (cm[4] < cm[3])
  {
    move_motors(LOW_SPEED, HIGH_SPEED);
    Serial.println("Trim Left.");
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }
  else if (cm[4] > cm[3])
  {
    move_motors(HIGH_SPEED, LOW_SPEED);
    Serial.println("Trim Right.");
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  }
  else
  {
    move_motors(HIGH_SPEED, HIGH_SPEED);
    Serial.println("Walk forward.");
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  }  
}

// functions

void move_motors(int left, int right)
// left and right motors take speed from -100 to 100.  -100 is maximum
// speed reverse, 0 is stop, 100 is maximum speed forward.
{
  if (ENABLE_MOTORS)
  {
    int scaled_speed = map(left, -100, 100, 0, 180);
    servo_left.write(scaled_speed);
    int scaled_speed = map(right, -100, 100, 0, 180);
    servo_right.write(scaled_speed);
  }
}

// https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
// ---------------------------------------------------------------------------
// This example code was used to successfully communicate with 15 ultrasonic sensors. You can adjust
// the number of sensors in your project by changing SONAR_NUM and the number of NewPing objects in the
// "sonar" array. You also need to change the pins for each sensor for the NewPing objects. Each sensor
// is pinged at 33ms intervals. So, one cycle of all sensors takes 495ms (33 * 15 = 495ms). The results
// are sent to the "oneSensorCycle" function which currently just displays the distance data. Your project
// would normally process the sensor results in this function (for example, decide if a robot needs to
// turn and call the turn function). Keep in mind this example is event-driven. Your complete sketch needs
// to be written so there's no "delay" commands and the loop() cycles at faster than a 33ms rate. If other
// processes take longer than 33ms, you'll need to increase PING_INTERVAL so it doesn't get behind.
// ---------------------------------------------------------------------------

// http://www.bajdi.com
// L9110 motor driver controlling 2 small DC motors 
