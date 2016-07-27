// The author disclaims copyright to this source code.
#ifndef P1INTERFACE_H
#define P1INTERFACE_H

#include "Arduino.h"
#include "Component.h"
#include "Clock.h"

class P1Interface: public Component, public Input {
public:
	P1Interface(Clock* c);
	virtual ~P1Interface() {};
	void setup();
	void read();
	bool isReady();
	uint8_t* getMessage();
	uint16_t getMessageLength();
	void start();
private:
	static const int MAX_MESSAGE_LENGTH = 500;
	void store(int data);
	Clock* clock;
	uint8_t message[MAX_MESSAGE_LENGTH];
	uint16_t messageLength = 0;
	typedef enum {
		// wait for start of message
		WAIT = 0,
		// receiving message
		DATA,
		// expect CR
		END1,
		// expect LF
		END2,
		// message available
		READY
	} State;
	State state;
};

#endif
