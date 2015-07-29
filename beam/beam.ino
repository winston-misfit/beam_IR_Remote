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
unsigned int off_commands[] = {3470, 1560, 550, 1150, 540, 1120, 540, 300, 550, 280, 570, 260, 590, 1110, 540, 300, 550, 260, 590, 1100, 550, 1150, 550, 280, 560, 1120, 540, 300, 550, 290, 550, 1130, 530, 1150, 530, 320, 530, 1130, 530, 1160, 500, 330, 520, 320, 520, 1160, 510, 340, 490, 330, 520, 1160, 490, 360, 490, 360, 450, 380, 460, 390, 430, 410, 400, 450, 380, 450, 380, 470, 340, 510, 340, 490, 320, 530, 310, 530, 300, 550, 280, 550, 300, 550, 290, 560, 270, 550, 280, 560, 290, 550, 300, 550, 270, 1400, 280, 550, 300, 550, 290, 1380, 300, 1380, 300, 550, 290, 560, 270, 550, 290, 550, 290, 550, 300, 550, 290, 1380, 280, 550, 300, 1400, 270, 550, 300, 540, 290, 550, 300, 550, 280, 560, 280, 550, 290, 1390, 300, 550, 270, 560, 290, 550, 280, 550, 300, 550, 300, 550, 270, 550, 290, 560, 280, 550, 300, 550, 290, 560, 270, 550, 280, 560, 290, 550, 300, 550, 290, 550, 280, 550, 290, 540, 300, 550, 300, 550, 270, 550, 300, 550, 280, 550, 300, 550, 300, 550, 270, 550, 300, 550, 280, 550, 300, 550, 290, 560, 270, 550, 280, 570, 280, 550, 300, 550, 290, 550, 280, 550, 290, 540, 300, 550, 300, 1370, 300, 1380, 300, 1400, 270, 1400, 280, 1400, 300, 1370, 300, 550, 280, 550, 300};
unsigned int on_commands[] = {3490, 1550, 540, 1130, 560, 1130, 550, 280, 570, 260, 580, 260, 580, 1120, 520, 300, 540, 300, 530, 1160, 520, 1150, 530, 310, 530, 1160, 510, 330, 510, 320, 510, 1170, 500, 1190, 490, 330, 490, 1200, 470, 1220, 440, 400, 400, 450, 390, 1290, 390, 460, 350, 490, 350, 1320, 340, 500, 340, 510, 310, 540, 300, 550, 290, 540, 290, 560, 270, 550, 300, 550, 290, 550, 290, 550, 290, 560, 270, 550, 300, 550, 290, 550, 290, 550, 290, 560, 270, 550, 300, 1380, 300, 550, 280, 560, 280, 1400, 280, 550, 300, 550, 280, 1390, 300, 1380, 300, 550, 280, 550, 290, 550, 290, 550, 290, 550, 300, 550, 270, 1400, 290, 550, 290, 1390, 290, 550, 290, 550, 290, 550, 290, 550, 290, 550, 280, 560, 280, 1400, 290, 550, 290, 550, 290, 550, 280, 550, 290, 550, 290, 560, 290, 550, 290, 540, 290, 550, 290, 550, 290, 550, 300, 550, 280, 560, 280, 550, 290, 550, 290, 550, 300, 550, 270, 550, 300, 550, 290, 550, 290, 550, 290, 560, 280, 550, 290, 550, 290, 550, 290, 550, 290, 560, 270, 560, 270, 570, 280, 560, 290, 550, 290, 560, 280, 550, 290, 550, 280, 550, 300, 550, 300, 550, 280, 550, 290, 1380, 300, 1400, 280, 550, 290, 550, 280, 550, 300, 550, 280, 1400, 290, 550, 280};

int ac_statue = 0;  // Off default

/*
 * check light sensor
 */
void loop_light_sensor(int interval) {
  int sensorValue = analogRead(A0);
  float f_brightness;
  f_brightness=(float)(1023-sensorValue)*10/sensorValue;

  // Printing...  
  int is_dark = f_brightness > light_control;
  if (ac_statue != is_dark) {
    do_on_light_changed(f_brightness > light_control);
    ac_statue = is_dark;

    Serial.print("Changed to ");
    Serial.print(f_brightness, 1);
    Serial.println("!!!");
  }

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
  Serial.print("sending code");
  Serial.print(codeLen);
  Serial.println("!!!");
  irsend.sendRaw(rawCodes, codeLen, 38);
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
