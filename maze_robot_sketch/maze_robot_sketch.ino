// Barnabas Robotics Maze Robot
// started from NewPing v1.8 example sketch NewPing15Sensors

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

#include <NewPing.h>

#define SONAR_NUM     6 // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 50 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

                    // connect motor controller pins as such:
const int AIA = 9;  // (pwm) pin 9 connected to pin A-IA    Left Wheel
const int AIB = 5;  // (pwm) pin 5 connected to pin A-IB    Left Wheel
const int BIA = 10; // (pwm) pin 10 connected to pin B-IA   Right Wheel
const int BIB = 6;  // (pwm) pin 6 connected to pin B-IB    Right Wheel

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

byte speed = 255;   // speed for motor control
byte left = 255;    // for motor control
byte right = 255;   // for motor control

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

  pinMode(AIA, OUTPUT); // set motor driver pins to output
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
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


  if (cm[0] < cm[1])
  {
    Serial.println("Trim Left.");
  }
  else if (cm[0] > cm[1])
  {
    Serial.println("Trim Right.");
  }
  else
  {
    Serial.println("Walk forward.");
  }

  
}

// functions

void move_forward(byte left, byte right)
{
  analogWrite(AIA, 0);
  analogWrite(AIB, left);
  analogWrite(BIA, 0);
  analogWrite(BIB, right);
}

