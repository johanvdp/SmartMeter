// The author disclaims copyright to this source code.
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(DigitalIn* in1, DigitalIn* in2) {
	aIn = in1;
	bIn = in2;
	a = false;
	b = false;
	aPrev = false;
	bPrev = false;
}

RotaryEncoder::~RotaryEncoder() {
}

void RotaryEncoder::setup() {
	// nothing to do
}

void RotaryEncoder::read() {
	aPrev = a;
	bPrev = b;
	a = aIn->get();
	b = bIn->get();
}

/**
 * change position
 *
 * A B | A B | dir
 * old | new |
 * ---------------
 * 0 0 | 0 0 |
 * 0 0 | 0 1 | ccw
 * 0 0 | 1 0 | cw
 * 0 0 | 1 1 |
 * 0 1 | 0 0 | cw
 * 0 1 | 0 1 |
 * 0 1 | 1 0 |
 * 0 1 | 1 1 | ccw
 * 1 0 | 0 0 | ccw
 * 1 0 | 0 1 |
 * 1 0 | 1 0 |
 * 1 0 | 1 1 | cw
 * 1 1 | 0 0 |
 * 1 1 | 0 1 | cw
 * 1 1 | 1 0 | ccw
 * 1 1 | 1 1 |
 */
void RotaryEncoder::process() {
	static bool CW[] = { //
			false, false, true, false, //
					true, false, false, false, //
					false, false, false, true, //
					false, true, false, false };
	static bool CCW[] = { //
			false, true, false, false, //
					false, false, false, true, //
					true, false, false, false, //
					false, false, true, false };

	int index = 0;
	if (aPrev) {
		index |= 0x08;
	}
	if (bPrev) {
		index |= 0x04;
	}
	if (a) {
		index |= 0x02;
	}
	if (b) {
		index |= 0x01;
	}
	cw.set(CW[index]);
	ccw.set(CCW[index]);
}

DigitalIn* RotaryEncoder::getCCW() {
	return &ccw;
}

DigitalIn* RotaryEncoder::getCW() {
	return &cw;
}
