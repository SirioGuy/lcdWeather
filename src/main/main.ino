/*
  ===========================================
  Project Name: Water Level Controller
  Author: Your Name
  Date: March 31, 2025
  ===========================================
  Description:
  - Monitors water level using a sensor
  - Controls a pump based on water level
  - Uses hysteresis to prevent rapid switching

  Hardware:
  - Arduino Uno
  - Water Level Sensors
  - Relay Module
  - Blinker-compatible Display
  ===========================================
*/

// ========== Includes ==========
#include "FRONTEND.h"
// #include DHT library
// #include BMP library


// ========== Pin Definitions ==========
#define GREEN 2
#define RED 3
#define BUZZ 4

#define TEMP A0
#define HUM A1
#define PRESS A2


// ========== Variables ==========

const int DELAY = 1000;   // Delay between lectures/updates (mS)

const int N = 10;
float tempHistory[N] = {0};
int humHistory[N] = {0};
int pressHistory[N] = {0};
int index = 0;

float avgTemp = 0;
float avgHum = 0;
float avgPress = 0;

float lastTemp = 0;
int lastHum = 0;
int lastPress = 0;

float temp;
int hum;
int press;


// ========== Objects ==========
FRONTEND frontend(RED, GREEN, BUZZ, 0x27);


// ===========================================
//               SETUP FUNCTION
// ===========================================
void setup(){
  Serial.begin(9600);
  Serial.println("Estacion Meteorologica - Sirio Guy");

  frontend.init();
}


// ===========================================
//               MAIN LOOP
// ===========================================
void loop(){
  temp = mapTemp();
  hum = mapHum();
  press = mapPress();

  average();
  alerts();
  frontend.run(temp, hum, press, weather());

  delay(DELAY);
}


// ===========================================
//               FUNCTION DEFINITIONS
// ===========================================
float mapTemp(){
  int raw = analogRead(TEMP);
  return raw * (50.0 / 1023.0);
}

int mapHum(){
  int raw = analogRead(HUM);
  return map(raw, 0, 1023, 0, 100);
}

int mapPress(){
  int raw = analogRead(PRESS);
  return map(raw, 0, 1023, 950, 1050);
}

void average(){
  tempHistory[index] = temp;
  humHistory[index] = hum;
  pressHistory[index] = press;
  index = (index + 1) % N;

  avgTemp = 0;
  avgHum = 0;
  avgPress = 0;

  for(int i = 0; i < N; i++){
    avgTemp += tempHistory[i];
    avgHum += humHistory[i];
    avgPress += pressHistory[i];
  }

  avgTemp /= N;
  avgHum /= N;
  avgPress /= N;
}

void alerts(){
  if(avgTemp < 5   ||   avgTemp > 38){
    frontend.redAlert();
  }
  else if(avgTemp < 10   ||   avgTemp > 30){
    frontend.yellowAlert();
  }
  else if(abs(temp - lastTemp) > 3){
    frontend.buzzAlert();
  }


  else if(avgHum < 30   ||   avgHum > 90){
    frontend.redAlert();
  }
  else if(avgHum < 40   ||   avgHum > 85){
    frontend.yellowAlert();
  }
  else if(abs(hum - lastHum) > 10){
    frontend.buzzAlert();
  }


  else if(avgPress < 980   ||   avgPress > 1040){
    frontend.redAlert();
  }
  else if(avgPress < 995   ||   avgPress > 1020){
    frontend.yellowAlert();
  }
  else if(abs(press - lastPress) > 3){
    frontend.buzzAlert();
  }

  else{
    frontend.greenAlert();
  }

  lastTemp = temp;
  lastHum = hum;
  lastPress = press;
}

int weather(){
  if (temp > 25 && hum > 80 && press < 1000) {
    return 3;
  }
  
  // **Rainy**: High hum, lower press
  else if (hum > 80 && press < 1010) {
    return 2;
  }
  
  // **Sunny**: Warm, low hum, normal/high press
  else if (temp >= 20 && temp <= 35 && hum < 60 && press >= 1010) {
    return 0;
  }

  // **Cloudy**: Mild temps, moderate hum, normal press
  else if (temp >= 15 && temp <= 30 && hum >= 60 && hum <= 80) {
    return 1;
  }
  
  // **Partly Cloudy**: Everything else that isn't extreme or unclassified
  else {
    return 4;
  }
}




