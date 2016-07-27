// The author disclaims copyright to this source code.
#include "DigitalInput.h"

DigitalInput::DigitalInput(int p, bool pullup) {
	pin = p;
	state = false;
	DigitalInput::pullup = pullup;
}

DigitalInput::DigitalInput(int p) {
	pin = p;
	state = false;
	DigitalInput::pullup = false;
}

DigitalInput::~DigitalInput() {
}

void DigitalInput::read() {
	state = digitalRead(pin);
}

bool DigitalInput::get() {
	return state;
}

void DigitalInput::setup() {
	if (pullup) {
		pinMode(pin, INPUT_PULLUP);
	} else {
		pinMode(pin, INPUT);
	}
}
