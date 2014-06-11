// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

//unsigned long time = millis(); return elapsed milliseconds since startup.


#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created
Servo servo2; 

int pos = 0;    // variable to store the servo position 
int pos2 = 90;

const int ledPin =  7;      // the number of the LED pin
const int buz = 8;

int gateConf;
unsigned long startTime;
const int SAS_TIMER = 5000;
boolean userIn;

#define but1 A4
#define but2 A5
#define infra1 (analogRead(A4) > 1000)
int infra1Count;
#define infra2 (analogRead(A5) > 1000)
int infra2Count;
#define cardIn (analogRead(A0) > 0 && analogRead(A1) > 0)

int bite = 0;

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(11);
  Serial.begin(9600);
  myservo.write(pos);
  servo2.write(pos2);
  
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
      //gate 2 already closed
      break;
     case 1:
       Serial.println("Close gate2 and open gate1");
    
      //Open gate 1 : 0->90
      //Close gate 2 : 90->0
      for(pos2; pos2 < 90; pos2 += 1)  // goes from 0 degrees to 180 degrees 
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
      for(pos2; pos2 > 0; pos2  -= 1)  // goes from 0 degrees to 180 degrees 
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
  alarm(false);
}
  
void displaySensors()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int but1Value = analogRead(but1);
  int but2Value = analogRead(but2);
  
  // print out the value you read:
  Serial.print("A0: ");
  Serial.println(sensorValue);
  Serial.print("A1: ");
  Serial.println(sensorValue2);
  Serial.print("but 1: ");
  Serial.println(but1Value);
  Serial.print("but 2: ");
  Serial.println(but2Value);
}
  


void loop() 
{ 
  
  //displaySensors();

  //infra1!
  if(infra1 && infra1Count == 0) {
    //The problem is that we keep the button down for too long, entering multiple times
    //in this branch. We avoid that by having a counter.
    //The incrementation is larger thant the decrementation to leave us time to left the 
    //finger from the button.
    infra1Count+=2;
    userIn = !userIn;
    Serial.print("userIn: ");
    Serial.println(userIn);
    if(userIn) {
      gateConf = 0;
      changeGateConf(gateConf);
      startTime = millis();
    }
  }
  else {
    infra1Count = (infra1Count<0)?0:infra1Count-1;
  }
  
  if(infra2 && gateConf == 2 && infra2Count == 0) {
    infra2Count+=2;
    gateConf = 1;
    userIn=false;
    changeGateConf(gateConf);
  }
  else {
    infra2Count = (infra2Count < 0)?0:infra2Count-1;
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
    }
      
  }
      

  delay(50);        // delay in between reads for stability
} 

