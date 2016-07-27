// The author disclaims copyright to this source code.
#ifndef BIT_H
#define BIT_H

#include <Arduino.h>
#include "Component.h"

/**
 * A component storing one bit. Accessible as DigitalIn and DigitalOut.
 */
class Bit: public Component, public DigitalIn, public DigitalOut {
public:
	Bit();
	virtual ~Bit();
	void read();bool get();
	void set(bool state);
	void setup();
private:
	bool bit;
};

#endif

