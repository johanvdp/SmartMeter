// The author disclaims copyright to this source code.
#include "Display.h"

Display::Display() {
	display = new Adafruit_SSD1306(OLED_RESET);
	needsRefresh = true;
}

Display::~Display() {
	if (display) {
		delete display;
	}
}

void Display::setup() {
	display->begin(SSD1306_SWITCHCAPVCC, OLED_I2C);
	display->clearDisplay();
	display->setTextSize(1);
	display->setTextColor(WHITE);
	display->setCursor(0, 0);
	display->setTextWrap(true);
	needsRefresh = true;
}

void Display::write() {
	if (needsRefresh) {
		needsRefresh = false;
		display->display();
	}
}

void Display::print(uint8_t* message, uint16_t length) {
	for (int i = 0; i < length; i++) {
		print(message[i]);
	}
}

void Display::print(uint8_t c) {
	display->write((uint8_t) c);
	int cursorY = display->getCursorY();
	if (cursorY > 32) {
		display->scrollup(8);
	}
	needsRefresh = true;
}
