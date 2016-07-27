// The author disclaims copyright to this source code.
#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include <Arduino.h>
#include "Component.h"

class DigitalInput: public Component, public Input, public DigitalIn {
public:
	DigitalInput(int pin);
	DigitalInput(int pin, bool pullup);
	virtual ~DigitalInput();
	void read();
	bool get();
	void setup();
private:
	int pin;
	bool state;
	bool pullup;
};

#endif

