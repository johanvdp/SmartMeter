// The author disclaims copyright to this source code.
#include "Button.h"

Button::Button(Clock* c, DigitalIn* in, int delayMillis) {
	Button::init(c, in, delayMillis, false);
}

Button::Button(Clock* c, DigitalIn* in, int delayMillis, bool invert) {
	Button::init(c, in, delayMillis, invert);
}

void Button::init(Clock* c, DigitalIn* in, int delayMillis, bool invert) {
	clock = c;
	digitalIn = in;
	delay = delayMillis;
	unfiltered = 0;
	filtered = 0;
	readyTimestamp = 0;
	Button::invert = invert;
}

Button::~Button() {
}

bool Button::get() {
	return filtered;
}

void Button::read() {
	unfiltered = digitalIn->get() ^ invert;
}

void Button::setup() {
	// nothing to do
}

void Button::process() {
	unsigned long now = clock->getTimestamp();
	boolean previousState = filtered;
	if (now > readyTimestamp && unfiltered != filtered) {
		filtered = unfiltered;
		readyTimestamp = now + delay;
	}
	pressed.set(!previousState && filtered);
	released.set(previousState && !filtered);
}

DigitalIn* Button::getPressed() {
	return &pressed;
}

DigitalIn* Button::getReleased() {
	return &released;
}
