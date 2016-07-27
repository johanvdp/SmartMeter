// The author disclaims copyright to this source code.
#include "Bit.h"

Bit::Bit() {
	bit = false;
}

Bit::~Bit() {
}

bool Bit::get() {
	return bit;
}

void Bit::set(bool state) {
	bit = state;
}

void Bit::setup() {
	// nothing to do
}
