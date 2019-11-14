

#ifndef _QMOBOT_H_
#define _QMOBOT_H_


#include <Arduino.h>
#include <Wire.h>
#include "oled/SSD1306Wire.h"


class Qchip_chip {

 public:
    Qchip_chip();

    void begin(bool DisplayEnable=true, bool SerialEnable=true, bool PABOOST=true, long BAND=470E6);
    SSD1306Wire *display;

};
extern Qchip_chip Qchip;

#endif
