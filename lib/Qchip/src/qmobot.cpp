#include "qmobot.h"


Qchip_chip::Qchip_chip(){
	display = new SSD1306Wire(0x3c, SDA_OLED, SCL_OLED, RST_OLED, GEOMETRY_128_64);
}


void Qchip_chip::begin(bool DisplayEnable, bool SerialEnable, bool PABOOST, long BAND) {

	// UART
	if (SerialEnable) {
		Serial.begin(115200);
		Serial.flush();
		delay(50);
		Serial.print("Qchip is ready\r\n");
	}

	// OLED
	if (DisplayEnable)
	{
		display->init();
		display->flipScreenVertically();
		display->setFont(ArialMT_Plain_10);
		display->drawString(0, 0, "Qmobot.com");
		display->display();

		if (SerialEnable){
			Serial.print("you can see OLED printed OLED initial done!\r\n");
		}
	}
}

Qchip_chip Qchip;
