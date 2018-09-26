
#include<EEPROM.h>

#define SERIESRESISTOR 10000    

#define THERMISTORNOMINAL 10000
 
// What pin to connect the sensor to
int THERMISTORPIN =A1;

#define BCOEFFICIENT 3950

#define TEMPERATURENOMINAL 25  

float steinhart;
float reading;

int timeButton = 2;  // Pin za zgolemvanje na vremeto 
int caseButton = 4;   // Pin za kapakot od greacot
int mosfetPin = 3;    // MOSFET Attiny-0 arduino-3
int ledPin = 1;       // LED dioda
int mosfetPWM = 767;  // PWM na mosfet

int vreme = 0;        // postaveno vreme 
int zgolemuvanje = 1; // za kolku se zgolemuva vremeto 
/***********************************************************/

boolean buttonTimeState = false;     // State na timeButton pinot
boolean buttonCaseClosed = false;    // State za kapakot od greacot

unsigned long currentMillis;
unsigned long startMillis;  // Stores timing for caseButton
unsigned long interval = 1000;
/***********************************************************/


void setup() {
pinMode (mosfetPin, OUTPUT);
pinMode (ledPin, OUTPUT);
pinMode (timeButton, INPUT);
pinMode (caseButton, INPUT);
pinMode (THERMISTORPIN, INPUT);

digitalWrite (mosfetPin, LOW);
digitalWrite (ledPin, LOW);
Serial.begin(9600);
EEPROM.read(45);
}

void loop() {
  checkTimeButton();
}

void checkTimeButton()  {
  digitalWrite(ledPin, LOW);
  delay(30);
  digitalWrite(ledPin, HIGH);
  delay(30);
  digitalWrite(ledPin, LOW);
  delay(30);
  
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

/*****************************************************************/
  reading = analogRead(THERMISTORPIN);
 
  Serial.print("Analog reading "); 
  Serial.println(reading);
 
  // convert the value to resistance
  reading = (1023 / reading)  - 1;     // (1023/ADC - 1) 
  reading = SERIESRESISTOR / reading;  // 10K / (1023/ADC - 1)
  Serial.print("Thermistor resistance "); 
  Serial.println(reading);


  steinhart = reading / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C

Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");

/***************************************************/
if (digitalRead(caseButton) == LOW && !buttonCaseClosed && steinhart < 30) {
    buttonCaseClosed = true;
    EEPROM.write(45, vreme);
      startMillis = millis();
      unsigned long vremeNaGreac = vreme * interval;
      Serial.println(EEPROM.read(1));
      Serial.println("Case Closed");     
        if ((startMillis) < vremeNaGreac) {
          analogWrite(mosfetPin, mosfetPWM);
     }    
         else if ((startMillis) >= vremeNaGreac) {
          digitalWrite(mosfetPin, LOW);
          startMillis= millis();
     }
     
    }
      
else if (digitalRead(caseButton) == HIGH && buttonCaseClosed || steinhart >= 30) {
    buttonCaseClosed = false; 
  }
 }  

/***************************************************/

