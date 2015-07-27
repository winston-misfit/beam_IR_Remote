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
#include <IRremote.h>

/*
 * Pre-define constant
 */
int led = 13;
int light_control = 20;

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

/*
 *  AC controller information mapping
 */
unsigned int off_commands[] = {3150, 1500, 600, 1000, 600, 950, 3150, 950, 600, 200, 600, 300, 550, 1050, 500, 1100, 450, 400, 450, 1150, 450, 350, 450, 400, 450, 1150, 400, 1200, 400, 450, 400, 1150, 400, 1200, 400, 450, 400, 450, 400, 1200, 350, 450, 400, 450, 400, 1200, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 400, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 400, 400, 450, 400, 450, 350, 1250, 400, 400, 400, 450, 400, 1200, 400, 1200, 400, 400, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 1200, 400, 400, 400, 1250, 350, 450, 400, 450, 400, 400, 400, 450, 400, 450, 400, 450, 400, 400, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 500, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 1200, 400, 1200, 350, 1250, 350, 450, 400, 1200, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 1200, 400, 450, 350, 450, 400, 1200, 400, 450, 400, 1200, 400, 400, 400, 1200, 400, 1200, 400};
unsigned int on_commands[] = {3200, 1500, 600, 1000, 600, 950, 3150, 950, 600, 250, 550, 300, 550, 1050, 500, 1100, 450, 400, 450, 1150, 450, 350, 450, 400, 400, 1200, 400, 1200, 400, 450, 400, 1200, 350, 1250, 350, 450, 400, 450, 400, 1200, 400, 450, 350, 450, 400, 1200, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 500, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 400, 400, 450, 400, 1200, 400, 450, 350, 500, 350, 1200, 400, 450, 350, 500, 350, 1200, 400, 1200, 400, 450, 400, 450, 350, 450, 400, 450, 350, 500, 350, 500, 350, 1200, 400, 450, 400, 1200, 400, 450, 400, 400, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 500, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 350, 500, 350, 450, 400, 1200, 400, 1200, 350, 1250, 400, 400, 400, 1200, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 400, 400, 450, 400, 450, 400, 400, 400, 450, 400, 1200, 400, 450, 400, 400, 400, 450, 400, 1200, 400, 1200, 350, 450, 400, 1200, 400, 1200, 400};

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
    turn_off_AC();
  }
  else
  {
    Serial.println("Turn on....");
    digitalWrite(led, HIGH); 
    turn_on_AC();
  }
}

void sendCode(unsigned int* rawCodes, int codeLen) {
  irsend.sendRaw(rawCodes, codeLen, 38);
  Serial.println("Sent raw");
}

void turn_off_AC() {
  digitalWrite(led, HIGH);
  sendCode(off_commands, sizeof(off_commands) / sizeof(int));
  digitalWrite(led, LOW);
}

void turn_on_AC() {
  digitalWrite(led, HIGH);
  sendCode(on_commands, sizeof(on_commands) / sizeof(int));
  digitalWrite(led, LOW);
}
void loop() {
  loop_light_sensor(1000);
}
