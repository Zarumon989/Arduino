void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
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
