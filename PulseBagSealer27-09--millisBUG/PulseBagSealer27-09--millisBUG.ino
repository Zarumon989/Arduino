
/******************************************Temperature*******************************/

#define SERIESRESISTOR 10000    
#define THERMISTORNOMINAL 10000
int THERMISTORPIN = A1; //The connector pin for the temperature sensor(A1)
#define BCOEFFICIENT 3950
#define TEMPERATURENOMINAL 25  
// float values for the temperature formula
float steinhart;
float reading;
float tempValue;
int desiredTemp = 102;

/***************************************Buttons, Heater & Led***************************/

int timeButton = 2;   // Time increasing button (3)
int caseButton = 4;   // Clamp open/closed device (4)
int mosfetPin = 3;    // MOSFET (0)
int ledPin = 1;       // LED diode (1)

int mosfetPWM = 767;  // MOSFET PWM value

int vreme = 0;        // Time set from timeButton 
int zgolemuvanje = 1; // By what value the time increases for each press

/**************************************Booleans*************************************/

boolean buttonTimeState = false;     // timeButton state
boolean buttonCaseClosed = false;    // case clamp state

/**************************************Millis()*************************************/

unsigned long previousMillis = 0;
unsigned long timeDelay;

void setup() {
pinMode (mosfetPin, OUTPUT);
pinMode (ledPin, OUTPUT);
pinMode (timeButton, INPUT);
pinMode (caseButton, INPUT);
pinMode (THERMISTORPIN, INPUT);

digitalWrite (mosfetPin, LOW);
digitalWrite (ledPin, LOW);
Serial.begin(9600); // debugging purposes only
}

/***********************Main loop to check the functions***************************/
void loop(){
  checkTimeButton();
  checkTemp();
  myDelay();
  execute();
}
/**************************** Time setting button function ******************************/
void checkTimeButton()  {
  //the blinking led is configured here
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  
if (digitalRead(timeButton) == LOW && !buttonTimeState && vreme < 10) {
    buttonTimeState = true;
      vreme += zgolemuvanje; 
      Serial.println(vreme);
        digitalWrite(ledPin, HIGH);
        delay((200*vreme));
        digitalWrite(ledPin, LOW);
    }
  else if ( digitalRead(timeButton) == HIGH && buttonTimeState) {
        buttonTimeState = false;
    }
if (digitalRead(timeButton) == LOW && !buttonTimeState && vreme >= 10) {
   vreme = 0; 
   Serial.println(vreme);
      }
}
/******************************* Thermometer function ************************************/
void checkTemp(){
   reading = analogRead(THERMISTORPIN);
 
//  Serial.print("Analog reading "); 
//  Serial.println(reading);
 
  // convert the value to resistance
  reading = (1023 / reading)  - 1;     // (1023/ADC - 1) 
  reading = SERIESRESISTOR / reading;  // 10K / (1023/ADC - 1)
//  Serial.print("Thermistor resistance "); 
//  Serial.println(reading);


  steinhart = reading / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  tempValue = steinhart;
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");

}

/************************************** The delay function which is used to check the temperature ********************************/

void myDelay(){
  // Split the work time in 5 parts regardless if its 1,2,3 or 5 seconds.
  // This will help us to have a much more constant temperature checkup on whats going on during the heating element on.
  // When it reaches the desired temperature it will stop with heating
  timeDelay = ((vreme * 1000));
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > timeDelay){
    previousMillis = currentMillis;
    if(tempValue < desiredTemp && !buttonCaseClosed){
       analogWrite(mosfetPin, mosfetPWM);
       delay(timeDelay);
       digitalWrite(mosfetPin, LOW);
    }
    else if (tempValue >= desiredTemp){
          digitalWrite(mosfetPin, LOW);
    }
  
 }
}
/******************************* The execution program for heating ************************************/

void execute(){
  if (digitalRead(caseButton) == LOW && !buttonCaseClosed) {
    buttonCaseClosed = true;
   Serial.println("Case Closed");
       myDelay();
  //     Serial.println("raboti greaco");
}
else if (digitalRead(caseButton) == HIGH && buttonCaseClosed) {
    buttonCaseClosed = false; 
  }
}
