#ifndef FRONTEND_h
#define FRONTEND_H

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"


class FRONTEND {
  public:
    FRONTEND(int redPin, int greenPin, int buzzPin, uint8_t address);

    void init();
    void run(float temp, int hum, int press, int weather);

    void redAlert();
    void yellowAlert();
    void greenAlert();
    void buzzAlert();

  private:
    LiquidCrystal_I2C lcd;

    int _redPin;
    int _greenPin;
    int _buzzPin;

    int _temp;
    int _hum;
    int _press;
    int _weather;   // Weather type (0 = sunny, 1 = cloudy, 2 = rainy, 3 = stormy, 4 = parcial)

    void sunny();
    void cloudy();
    void rainy();
    void stormy();

    // Custom characters

    byte sun0[8]{
      B00000,
      B00100,
      B00010,
      B00001,
      B00000,
      B00000,
      B00001,
      B01111
    };
    byte sun1[8]{
      B00010,
      B00010,
      B00010,
      B01111,
      B11111,
      B11111,
      B11111,
      B11111
    };
    byte sun2[8]{
      B00000,
      B00010,
      B00100,
      B01000,
      B10000,
      B10000,
      B11000,
      B11111
    };
    byte sun3[8]{
      B00001,
      B00000,
      B00000,
      B00001,
      B00010,
      B00100,
      B00000,
      B00000
    };
    byte sun4[8]{
      B11111,
      B11111,
      B11111,
      B01111,
      B00010,
      B00010,
      B00010,
      B00000
    };
    byte sun5[8]{
      B11000,
      B10000,
      B10000,
      B01000,
      B00100,
      B00010,
      B00000,
      B00000
    };


    byte cloud0[8]{
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00011,
      B00100,
      B00100
    };
    byte cloud1[8]{
      B00000,
      B00000,
      B01111,
      B10000,
      B00000,
      B00000,
      B00000,
      B00000
    };
    byte cloud2[8]{
      B00000,
      B00000,
      B00000,
      B10000,
      B01100,
      B00100,
      B00010,
      B00001
    };
    byte cloud3[8]{
      B00100,
      B00011,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };
    byte cloud4[8]{
      B00000,
      B11111,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };
    byte cloud5[8]{
      B00001,
      B11110,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    };


    byte rain3[8]{
      B00100,
      B00011,
      B00001,
      B00001,
      B00010,
      B00010,
      B00100,
      B00100
    };
    byte rain4[8]{
      B00100,
      B11111,
      B01001,
      B01001,
      B10010,
      B10010,
      B00100,
      B00100
    };
    byte rain5[8]{
      B00101,
      B11110,
      B01000,
      B01000,
      B10000,
      B10000,
      B00000,
      B00000
    };


    byte storm4[8]{
      B00010,
      B00100,
      B01000,
      B11100,
      B00111,
      B00010,
      B00100,
      B01000
    };

    byte degree[8]{
      B00110, 
      B01001, 
      B01001, 
      B00110, 
      B00000, 
      B00000, 
      B00000, 
      B00000
    };

    byte pascal[8]{
      B11110,
      B10001,
      B11110,
      B10000,
      B10111,
      B10001,
      B10111,
      B10111
    };
};


#endif