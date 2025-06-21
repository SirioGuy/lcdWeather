#include "FRONTEND.h"


FRONTEND::FRONTEND(int redPin, int greenPin, int buzzPin, uint8_t address)
  : lcd(address, 16, 2) {
    
    _redPin = redPin;
    _greenPin = greenPin;
    _buzzPin = buzzPin;

  }




void FRONTEND::init(){
  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_buzzPin, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.createChar(6, degree);
  lcd.createChar(7, pascal);
}




void FRONTEND::run(float temp, int hum, int press, int weather){
  _temp = temp;
  _hum = hum;
  _press = press;
  _weather = weather;
  
  int tempRound = static_cast<int>(round(_temp));


  lcd.setCursor(0, 0);
  lcd.print(tempRound);
  lcd.write(byte(6));
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print(_hum);
  lcd.print("%  ");

  lcd.setCursor(5, 1);
  lcd.print(_press);
  lcd.print("h");
  lcd.write(byte(7));
  lcd.print(" ");


  if(_weather == 0){
    lcd.setCursor(12, 0);
    lcd.print(" ");
    sunny();
  }
  else if(_weather == 1){
    lcd.setCursor(12, 0);
    lcd.print(" ");
    cloudy();
  }
  else if(_weather == 2){
    lcd.setCursor(12, 0);
    lcd.print(" ");
    rainy();
  }
  else if(_weather == 3){
    lcd.setCursor(12, 0);
    lcd.print("!");
    stormy();
  }
  else if(_weather == 4){
    lcd.setCursor(12, 0);
    lcd.print("?");
    sunny();
  }
}



void FRONTEND::sunny(){
  lcd.createChar(0, sun0);
  lcd.createChar(1, sun1);
  lcd.createChar(2, sun2);
  lcd.createChar(3, sun3);
  lcd.createChar(4, sun4);
  lcd.createChar(5, sun5);

  lcd.setCursor(13, 0);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));

  lcd.setCursor(13, 1);
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
}

void FRONTEND::cloudy(){
  lcd.createChar(0, cloud0);
  lcd.createChar(1, cloud1);
  lcd.createChar(2, cloud2);
  lcd.createChar(3, cloud3);
  lcd.createChar(4, cloud4);
  lcd.createChar(5, cloud5);

  lcd.setCursor(13, 0);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));

  lcd.setCursor(13, 1);
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
}

void FRONTEND::rainy(){
  lcd.createChar(0, cloud0);
  lcd.createChar(1, cloud1);
  lcd.createChar(2, cloud2);
  lcd.createChar(3, rain3);
  lcd.createChar(4, rain4);
  lcd.createChar(5, rain5);

  lcd.setCursor(13, 0);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));

  lcd.setCursor(13, 1);
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
}

void FRONTEND::stormy(){
  lcd.createChar(0, cloud0);
  lcd.createChar(1, cloud1);
  lcd.createChar(2, cloud2);
  lcd.createChar(3, cloud3);
  lcd.createChar(4, storm4);
  lcd.createChar(5, cloud5);

  lcd.setCursor(13, 0);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));

  lcd.setCursor(13, 1);
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
}



void FRONTEND::redAlert(){
  digitalWrite(_redPin, HIGH);
  digitalWrite(_greenPin, LOW);
}


void FRONTEND::yellowAlert(){
  digitalWrite(_redPin, HIGH);
  digitalWrite(_greenPin, HIGH);
}


void FRONTEND::greenAlert(){
  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, HIGH);
}


void FRONTEND::buzzAlert(){
  for(int i = 0; i <= 3; i++){
    digitalWrite(_buzzPin, HIGH);
    delay(100);
    digitalWrite(_buzzPin, LOW);
    delay(100);
  }
}

