// The author disclaims copyright to this source code.
#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "Component.h"
#include "Clock.h"
#include "Bit.h"

class Button: public Component, public Input, public Process, public DigitalIn {
public:
	Button(Clock* c, DigitalIn* in, int delayMillis);
	Button(Clock* c, DigitalIn* in, int delayMillis, bool invert);
	void init(Clock* c, DigitalIn* in, int delayMillis, bool invert);
	virtual ~Button();
	void read();
	bool get();
	void setup();
	void process();
	DigitalIn* getPressed();
	DigitalIn* getReleased();

private:
	Clock* clock;
	DigitalIn* digitalIn;
	Bit pressed;
	Bit released;
	bool invert;
	bool filtered;
	bool unfiltered;
	int delay;
	unsigned long readyTimestamp;
};

#endif

