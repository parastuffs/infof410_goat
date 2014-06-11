// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

//unsigned long time = millis(); return elapsed milliseconds since startup.


#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created
Servo servo2; 

int pos;    // variable to store the servo position 
int pos2;

const int ledPin =  7;      // the number of the LED pin
const int buz = 8;

int gateConf;
unsigned long startTime;
const int SAS_TIMER = 5000;
boolean userIn;

#define but1 A4
#define but2 A5
#define infra1 (analogRead(A4) > 550)
int infra1Count;
#define infra2 (analogRead(A5) > 500)
int infra2Count;
#define cardIn (analogRead(A0) > 0 && analogRead(A1) > 0)

int bite = 0;

void setup() 
{ 
  pos = 0;//Opened
  pos2 = 90;//Closed
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(11);
  Serial.begin(9600);
  myservo.write(pos);
  delay(150);
  servo2.write(pos2);
  delay(150);
  
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(buz, OUTPUT);
  
  gateConf = 1;
  userIn = false;
  infra1Count = 0;
  infra2Count = 0;
} 

void changeGateConf(int conf)
{
  gateConf = conf;
  switch (conf) {
    case 0:
      //from 1
      //Close gate 1
      for(pos; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        //Serial.print("Closing gate1: ");
        //Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      }
      //We could simply write myservo.write(90), but the rotation would be too quick.
      //gate 2 already closed
      break;
     case 1:
       Serial.println("Close gate2 and open gate1");
    
      //Open gate 1 : 0->90
      //Close gate 2 : 180->90
      for(pos2; pos2 > 90; pos2 -= 1)  // goes from 0 degrees to 180 degrees 
      {      // in steps of 1 degree 
        //Serial.print("Closing gate2: ");
        //Serial.println(pos2);
        servo2.write(pos2);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      }
      for(pos; pos > 0; pos -= 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree
        //Serial.print("Opening gate1: ");
        //Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      }
      break;
     case 2:
       //gateConf = 2
      //Close gate 1: 90->0
      //Open gate 2: 0->90
      Serial.println("Close gate1 and open gate2");
      
      
      for(pos; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        //Serial.print("Closing gate1: ");
        //Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      }
      for(pos2; pos2 < 180; pos2  += 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        //Serial.print("Opening gate2: ");
        //Serial.println(pos2);
        servo2.write(pos2);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      }
      break;
      
     default:
       Serial.println("BIG PROBLEEM.");
       break;
  }  
}

boolean processCard()
{
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  if(sensorValue>200 && sensorValue<400 && sensorValue2>200 && sensorValue2<400)
    return true;
  else
    return false;
}

void alarm(boolean on)
{
  if(on) {
    //analogWrite(buz, 500);
    bite = 0;
    digitalWrite(buz,HIGH);
  }
  else {
    bite = 1;
    digitalWrite(buz,LOW);
  }
  Serial.print("buz: ");
  Serial.println(bite);
}

void eject()
{
  digitalWrite(ledPin, LOW);
  //alarm(true);
  //alarm(false);
  changeGateConf(1);
  Serial.println("GET OUT. NOW");
  while(!infra1) {
    Serial.println("GET OUT. NOW");
    alarm(true);
    delay(150);
  }
  while(infra1);
  alarm(false);
  
}
  
void displaySensors()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int but1Value = analogRead(but1);
  int but2Value = analogRead(but2);
  int infra1Value = analogRead(A4);
  int infra2Value = analogRead(A5);
  
  // print out the value you read:
  /*Serial.print("A0: ");
  Serial.println(sensorValue);
  Serial.print("A1: ");
  Serial.println(sensorValue2);
  Serial.print("but 1: ");
  Serial.println(but1Value);
  Serial.print("but 2: ");
  Serial.println(but2Value);*/
  if(infra1Value > 550) {
    Serial.print("Infra 1: ");
    Serial.println(infra1Value);
  }
  if(infra2Value > 500) {
    Serial.print("Infra 2: ");
    Serial.println(infra2Value);
  }
}
  


void loop() 
{ 
  
  //displaySensors();

  //infra1!
  if(infra1 && gateConf == 1 && !userIn) {
    userIn = true;
    Serial.print("userIn: ");
    Serial.println(userIn);
    gateConf = 0;
    changeGateConf(gateConf);
    startTime = millis();
  }
  
  if(infra2 && gateConf == 2) {
    gateConf = 1;
    userIn = false;
    changeGateConf(gateConf);
  }
  
  if(gateConf == 0 || gateConf == 2) {
    if((millis() - startTime) <= SAS_TIMER) {
      if(cardIn) {
        if(processCard()) {
          digitalWrite(ledPin, HIGH);
          gateConf = 2;
          changeGateConf(gateConf);
        }
        else
          digitalWrite(ledPin, LOW);
      }
      else
        digitalWrite(ledPin, LOW);
    }
    else {
      Serial.print("startTime = ");
      Serial.println(startTime);
      Serial.print("current time = ");
      Serial.println(millis());
      eject();
      userIn = false;
    }
      
  }
      

  delay(50);        // delay in between reads for stability
} 

