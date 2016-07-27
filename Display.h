// The author disclaims copyright to this source code.
#ifndef _OLED_H_
#define _OLED_H_

#include <Arduino.h>

#include "Component.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

// Reset on pin GPIO
#define OLED_RESET 0
// Address on I2C bus
#define OLED_I2C 0x3C

class Display: public Component, public Output {
public:
	Display();
	virtual ~Display();
	void setup();
	void write();
	void print(uint8_t c);
	void print(uint8_t* message, uint16_t length);
private:
	Adafruit_SSD1306* display;
	bool needsRefresh;
};

#endif
