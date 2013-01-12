#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
 int buttonState = 0;         // variable for reading the pushbutton status
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(buttonPin, INPUT);    
 // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);     
} 
 
 
void loop() 
{ 
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {    
    digitalWrite(ledPin, HIGH);   
    myservo.write(170);
    delay(1500);

    myservo.write(10);              // tell servo to go to position in variable 'pos' 
    delay(500);
    digitalWrite(ledPin, LOW); 
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
