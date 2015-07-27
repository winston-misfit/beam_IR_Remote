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

bool status = 1;

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

/*
 *  AC controller information mapping
 */
unsigned int off_commands[] = {3500,1550,550,1150,500,1200,500,350,500,300,550,300,550,300,0,850,550,250,550,300,550,300,65486,900,550,1150,550,250,550,1150,550,300,500,300,550,1150,550,1150,550,300,500,1200,500,1150,550,300,500,350,500,1150,550,300,550,300,500,1200,500,350,450,350,500,350,500,350,500,350,450,400,400,450,400,450,350,500,350,500,350,450,350,500,350,500,350,500,300,550,300,550,300,550,250,600,250,550,300,550,300,1400,300,550,250,600,250,1400,300,1400,300,550,300,500,300,550,300,550,300,550,300,550,300,1350,300,550,300,550,300,1400,300,550,250,550,300,550,300,550,300,550,300,550,250,600,250,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,1400,300,550,300,550,250,550,300,550,300,550,300,1400,300,550,250};
unsigned int on_commands[] = {3550,1500,600,1050,600,1100,600,250,600,200,650,200,650,1050,600,250,600,250,600,1100,550,1100,600,250,600,1100,550,300,550,250,600,1100,550,1150,500,350,500,1150,550,1150,500,350,500,350,500,1150,550,300,550,300,500,1200,450,400,450,350,500,350,450,400,450,400,400,450,400,450,350,500,350,500,350,500,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,1400,250,550,300,550,300,1400,300,550,300,550,250,1400,300,1400,300,550,250,600,250,550,300,550,300,550,300,550,300,1400,250,550,300,550,300,1400,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,600,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,550,250,550,300,550,300,550,300,550,300,550,300,1400,250,550,300,1400,300,550,300,550,250,600,250,1400,300,550,300};
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

    if (status) {
      turn_off_AC();
      status = 0;
    }
  }
  else
  {
    Serial.println("Turn on....");
    digitalWrite(led, HIGH); 

    if (!status) {
      turn_on_AC();
      status = 1;
    }
  }
}

void sendCode(unsigned int* rawCodes, int codeLen) {
  irsend.sendRaw(rawCodes, codeLen, 38);
  Serial.println("Sent raw");
}

void turn_off_AC() {
  delay(50);
  
  digitalWrite(led, HIGH);
  Serial.println(sizeof(off_commands) / sizeof(int));
  sendCode(off_commands, sizeof(off_commands) / sizeof(int));
  digitalWrite(led, LOW);

  delay(50);
}

void turn_on_AC() {
  delay(50);
  
  digitalWrite(led, HIGH);
  Serial.println(sizeof(on_commands) / sizeof(int));
  sendCode(on_commands, sizeof(on_commands) / sizeof(int));
  digitalWrite(led, LOW);

  delay(50);
}
void loop() {
  loop_light_sensor(1000);
}
