#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

// reference for the display code
// https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbox

// initialize display library
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

// output string buffer
char psiString[7];

class DisplayController
{
public:
	static void init() {
		u8g2.begin();
	};

	static void helloWorld() {
		u8g2.firstPage();
		do {
			u8g2.setFont(u8g2_font_helvR14_tr);
			u8g2.drawStr(0,20,"Hello World!!");
		} while ( u8g2.nextPage() );
	};

	static void showPressureSelection(float psi) {
		u8g2.firstPage();
		u8g2.setFont(u8g2_font_helvR14_tr);

		int psiDigit = (int) psi;
		int psiDecimal = (int) (psi * 10) % 10;

		sprintf(psiString, "%01d.%01d psi", psiDigit, psiDecimal);

		u8g2.drawStr(20, 20, psiString);
	};

	static void showValveOpening(float valve) {
		int width = (int) (valve * 128 + 0.5);
		u8g2.drawBox(0, 26, width, 6);
	};

	static void submit() {
		u8g2.sendBuffer();
	};

};

#endif