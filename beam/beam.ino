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
#include <Time.h>
#include <TimeAlarms.h>

/*
 * Pre-define constant
 */
int led = 13;
int light_control = 20;

IRsend irsend;

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

void setup()
{
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  pinMode(led, OUTPUT);
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
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
void loop_light_sensor() {
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
  Serial.println("turn AC off");  
  digitalWrite(led, HIGH);
  sendCode(off_commands, sizeof(off_commands) / sizeof(int));
  digitalWrite(led, LOW);
}

void turn_on_AC() {
  Serial.println("turn AC on");  
  digitalWrite(led, HIGH);
  sendCode(on_commands, sizeof(on_commands) / sizeof(int));
  digitalWrite(led, LOW);
}

int midnightAlarmId = -1;

void setupAlarm() {
  if (midnightAlarmId != -1) {
    Alarm.disable(midnightAlarmId);
  }
  midnightAlarmId = Alarm.alarmRepeat(23,59,59,turn_off_AC);
}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
       setupAlarm();
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void loop_clock_sync() {
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }
}

void loop() {
  loop_clock_sync();
  loop_light_sensor();
  Alarm.delay(1000);
}
