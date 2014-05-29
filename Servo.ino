// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created
Servo servo2; 

int pos = 0;    // variable to store the servo position 
int pos2 = 90;

const int ledPin =  7;      // the number of the LED pin

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(11);
  Serial.begin(9600);
  myservo.write(pos);
  servo2.write(pos2);
  
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
} 


void loop() 
{ 
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  // print out the value you read:
  Serial.print("A0: ");
  Serial.println(sensorValue);
  Serial.print("A1: ");
  Serial.println(sensorValue2);

  if(sensorValue>200 && sensorValue<400 && sensorValue2>200 && sensorValue2<400) { 
    //Close gate 1: 90->0
    //Open gate 2: 0->90
    Serial.println("Close gate1 and open gate2");
    
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, HIGH);
    
    for(pos; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      Serial.print("Closing gate1: ");
      Serial.println(pos);
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    for(pos2; pos2 > 0; pos2  -= 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      Serial.print("Opening gate2: ");
      Serial.println(pos2);
      servo2.write(pos2);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    
  }
  else {

    Serial.println("Close gate2 and open gate1");
    
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, LOW);
    
    //Open gate 1 : 0->90
    //Close gate 2 : 90->0
    for(pos2; pos2 < 90; pos2 += 1)  // goes from 0 degrees to 180 degrees 
    {      // in steps of 1 degree 
      Serial.print("Closing gate2: ");
      Serial.println(pos2);
      servo2.write(pos2);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    for(pos; pos > 0; pos -= 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree
      Serial.print("Opening gate1: ");
      Serial.println(pos);
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
  }

  delay(500);        // delay in between reads for stability
} 

