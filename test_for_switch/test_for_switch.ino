// Pin definiton 
int ledPin = 1;
int buttonPin = 2;
int switchPin = 3;

// State definition for sampling and checking 
int buttonState = 0;
int lastButtonState = 0;
int switchState = 0;
int lastSwitchState = 0;

//Premade delays for how long heater is on
int stateOne = 10 * 100;
int stateTwo = 20 * 100;
int stateThree = 30 * 100;
int pressedTimesButton = 0;
int pressedTimesSwitch = 0;

bool buttonIsPressed = false;
bool switchIsPressed = false;
bool releasedButton = true;
bool releasedSwitch = true;

void setup() {
  //Debugger
  Serial.begin(9600);
  //Defining inputs and outputs
pinMode(ledPin, OUTPUT);
pinMode(buttonPin, INPUT);
pinMode(switchPin, INPUT);


}

void loop(){
  checkButton();
  checkSwitch();
  }
void checkButton(){
     buttonState = digitalRead(buttonPin);
   if(lastButtonState != buttonState){
   if((buttonState == HIGH) && (releasedButton == true)){
   buttonIsPressed = true;
   buttonState++;
    }
   delay(50);
   lastButtonState = buttonState;
  }
  if((lastButtonState == 1) && (releasedButton == true)){
    pressedTimesButton = lastButtonState+1;
  }
  if(pressedTimesButton >= 4){
    pressedTimesButton = 1;
  }
  if(pressedTimesButton == 0){
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  if(pressedTimesButton == 1){
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(450);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  if(pressedTimesButton == 2){
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(450);
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(450);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  if(pressedTimesButton == 3){
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(450);
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(450);
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(450);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  Serial.println("pressedTimesButton");
  Serial.println(pressedTimesButton);
  delay(500);

}
void checkSwitch(){
     switchState = digitalRead(switchPin);
  if(lastSwitchState != switchState){
    if(switchState == HIGH){
      switchIsPressed = true;
       switchState++;
      }
    delay(100);
     lastSwitchState = switchState;
  }
  if((lastSwitchState == 1) && (releasedSwitch == true)){
    pressedTimesSwitch = lastSwitchState + 1;
  }
    Serial.println("lastSwitchState");
      Serial.println(pressedTimesSwitch);
      delay(500);
}

