/*

*/
#include <Adafruit_NeoPixel.h>
#define PIN 6 // 腳位(可更改)
#define DELAYVAL 20 // 時間間隔(可更改)
#define NUMPIXELS 12 // 數量(可更改)
Adafruit_NeoPixel pixels(NUMPIXELS, PIN); //設定腳位及數量(不可更改)

  int brightness = 0;  // how bright the LED is
  int fadeAmount = 15;  // how many points to fade the LED by
  int IR_SENSOR = 0; // 類比讀取腳設為A0Sensor is connected to the analog A0
  int intSensorResult = 0; //Sensor result
  float fltSensorCalc = 0; //Calculated value
  bool breathing = false;


// the setup function runs once when you press reset or power the board
void setup() {
  //
  pixels.begin(); //啟用pixels服務
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

  //Serial.print(fltSensorCalc); //Send distance to computer
  //Serial.println(" cm"); //Add cm to result
  if (fltSensorCalc>=80){ // 80cm is the maxium distance for this sensor
    fltSensorCalc = 80;
    breathing = true;
     Serial.println("0");
  }
  else {//if (fltSensorCalc<=20)
    breathing = false;
    Serial.println("1");
  }

  if(fltSensorCalc<10){
    fltSensorCalc = 10;
  }

  fltSensorCalc = map(fltSensorCalc, 10, 80, 0, 255);

  if(breathing==true){
    //RGBLed_1_breath();
    NeoPixel_12_breath();
  }
  else {
    //RGBLed_1_Brith();
    NeoPixel_12_brith();
  }
}

void NeoPixel_12_breath(){
  for(int j=0; j<50; j++){
    for(int i=0; i<NUMPIXELS; i++){ //設定「每一顆」燈的顏色
      pixels.setPixelColor(i, pixels.Color( 0, 255, 255 )); //設定燈的顏色
    }
    pixels.setBrightness(j); //亮度調整
    pixels.show(); //顯示
    delay(DELAYVAL); //延遲
  }
  for(int j=50; j>0; j--){
    for(int i=0; i<NUMPIXELS; i++){ //設定「每一顆」燈的顏色
      pixels.setPixelColor(i, pixels.Color( 0, 255, 255 )); //設定燈的顏色
    }
    pixels.setBrightness(j); //亮度調整
    pixels.show(); //顯示
    delay(DELAYVAL); //延遲
  }
}

void NeoPixel_12_brith(){
  for(int i=0; i<NUMPIXELS; i++){ //設定「每一顆」燈的顏色
    pixels.setPixelColor(i, pixels.Color( 255, 255, 255 )); //設定燈的顏色
  }
  pixels.setBrightness(100); //亮度調整
  pixels.show(); //顯示
  delay(DELAYVAL); //延遲
}

void RGBLed_1_breath(){
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

void RGBLed_1_Brith(){
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