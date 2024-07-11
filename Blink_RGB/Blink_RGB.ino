/*

*/
  int brightness = 0;  // how bright the LED is
  int fadeAmount = 15;  // how many points to fade the LED by
  int IR_SENSOR = 1; // 類比讀取腳設為A0Sensor is connected to the analog A0
  int intSensorResult = 0; //Sensor result
  float fltSensorCalc = 0; //Calculated value
  bool breathing = false;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // read the value from the ir sensor
  intSensorResult = analogRead(IR_SENSOR); //Get sensor value
  fltSensorCalc = (6787.0 / (intSensorResult - 3.0)) - 4.0; //Calculate distance in cm

  Serial.print(fltSensorCalc); //Send distance to computer
  Serial.println(" cm"); //Add cm to result
  if (fltSensorCalc>=80){ // 80cm is the maxium distance for this sensor
    fltSensorCalc = 80;
    breathing = true;
  }
  else {
    breathing = false;
  }

  if(fltSensorCalc<10){
    fltSensorCalc = 10;
  }

  fltSensorCalc = map(fltSensorCalc, 10, 80, 0, 255);

  if(breathing==true){
    for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
      analogWrite(3, fadeValue);  // turn the LED on (HIGH is the voltage level)
      analogWrite(5, fadeValue);  // turn the LED on (HIGH is the voltage level)
      analogWrite(6, fadeValue);  // turn the LED on (HIGH is the voltage level)
      analogWrite(7, 255);  // turn the LED on (HIGH is the voltage level)
      delay(20); //Wait
    }
    for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(3, fadeValue);  // turn the LED on (HIGH is the voltage level)
      analogWrite(5, fadeValue);  // turn the LED on (HIGH is the voltage level)
      analogWrite(6, fadeValue);  // turn the LED on (HIGH is the voltage level)
      analogWrite(7, 255);  // turn the LED on (HIGH is the voltage level)
      delay(20); //Wait
    }
    
  }
  else {
    brightness = 255-fltSensorCalc;
    if (brightness<=0){
      brightness = 0;
    }
    analogWrite(3, brightness);  // turn the LED on (HIGH is the voltage level)
    analogWrite(5, brightness);  // turn the LED on (HIGH is the voltage level)
    analogWrite(6, brightness);  // turn the LED on (HIGH is the voltage level)
    analogWrite(7, 255);  // turn the LED on (HIGH is the voltage level)
    delay(100); //Wait
  }
  
  




}