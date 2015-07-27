/*
 *Misfit Wearables Beam Team
 *Demo for light sensor
 *by Misfit Beam Team
 * Dylan
 * Phill
 * Winston
 * Yuan
 */

#include <math.h>

/*
 * Pre-define constant
 */
int led = 13;
int light_control = 20;

/*
 * check light sensor
 */
void loop_light_sensor(int interval) {
  int sensorValue = analogRead(A0);
  float f_brightness;
  f_brightness=(float)(1023-sensorValue)*10/sensorValue;

  // Printing...  
  Serial.println("The resistance of the Light sensor is ");
  Serial.print(f_brightness,1);
  Serial.println(" KOhm");
  
  do_on_light_changed(f_brightness > light_control);

  // sleep for a while  
  delay(interval);
}

/*
 * take action when light is changed
 */
void do_on_light_changed(bool is_dark) {
  if (is_dark)
  {
    Serial.println("Turn off....");
    digitalWrite(led, LOW); 
  }
  else
  {
    Serial.println("Turn on....");
    digitalWrite(led, HIGH); 
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);  
}

void loop() {
  loop_light_sensor(1000);
}

