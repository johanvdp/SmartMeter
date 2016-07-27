// The author disclaims copyright to this source code.
#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <Arduino.h>
#include "Component.h"
#include "Bit.h"

class RotaryEncoder : public Component, public Input, public Process {
public:
	RotaryEncoder(DigitalIn* a, DigitalIn* b);
	virtual ~RotaryEncoder();
	void setup();
	void read();
	void process();
	DigitalIn* getCCW();
	DigitalIn* getCW();
private:
	bool aPrev;
	bool bPrev;
	bool a;
	bool b;
	DigitalIn* aIn;
	DigitalIn* bIn;
	Bit cw;
	Bit ccw;
};

#endif

