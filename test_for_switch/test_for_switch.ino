// Pin definiton 
int ledPin=1;
int buttonPin=2;
int switchPin=3;

// State definition for sampling and checking 
int buttonState = 0;
int lastButtonState = 0;
int switchState = 0;
int lastSwitchState = 0;

//Premade delays for how long heater is on
int stateOne = 10 * 100;
int stateTwo = 20 * 100;
int stateThree = 30 * 100;

void setup() {
  //Debugger
  Serial.begin(9600);
  //Defining inputs and outputs
pinMode(ledPin, OUTPUT);
pinMode(buttonPin, INPUT);
pinMode(switchPin, INPUT);


}

void loop(){
   buttonState = digitalRead(buttonPin);
   if(lastButtonState != buttonState){
   if(buttonState == LOW){

   buttonState++;
    }
   delay(100);
   lastButtonState = buttonState;
   if(lastButtonState>= 4){
    buttonState=1;
    lastButtonState = buttonState;
   }
  }
  
//  if(lastButtonState = 0){
//    digitalWrite(ledPin, HIGH);
//    delay(100);
//    digitalWrite(ledPin, LOW);
//    delay(100);
//  }
//  if(lastButtonState = 1){
//    digitalWrite(ledPin, HIGH);
//    delay(600);
//    digitalWrite(ledPin, LOW);
//    delay(450);
//    digitalWrite(ledPin, HIGH);
//    delay(100);
//    digitalWrite(ledPin, LOW);
//    delay(100);
//  }
//  if(lastButtonState = 2){
//    digitalWrite(ledPin, HIGH);
//    delay(600);
//    digitalWrite(ledPin, LOW);
//    delay(450);
//    digitalWrite(ledPin, HIGH);
//    delay(600);
//    digitalWrite(ledPin, LOW);
//    delay(450);
//    digitalWrite(ledPin, HIGH);
//    delay(100);
//    digitalWrite(ledPin, LOW);
//    delay(100);
//  }
//  if(lastButtonState = 3){
//    digitalWrite(ledPin, HIGH);
//    delay(600);
//    digitalWrite(ledPin, LOW);
//    delay(450);
//    digitalWrite(ledPin, HIGH);
//    delay(600);
//    digitalWrite(ledPin, LOW);
//    delay(450);
//    digitalWrite(ledPin, HIGH);
//    delay(600);
//    digitalWrite(ledPin, LOW);
//    delay(450);
//    digitalWrite(ledPin, HIGH);
//    delay(100);
//    digitalWrite(ledPin, LOW);
//    delay(100);
//  }
  
  Serial.println("lastButtonState");
  Serial.println(lastButtonState);
  delay(500);

   switchState = digitalRead(switchPin);
  if(lastSwitchState != switchState){
    if(switchState == LOW){
       switchState++;
      }
    delay(100);
     lastSwitchState = switchState;
  }
    Serial.println("lastSwitchState");
  Serial.println(lastSwitchState);
  delay(500);
}

