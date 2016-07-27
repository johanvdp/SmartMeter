// The author disclaims copyright to this source code.
#include "P1Interface.h"

P1Interface::P1Interface(Clock* c) {
	clock = c;
	start();
}

void P1Interface::start() {
	messageLength = 0;
	state = WAIT;
}

void P1Interface::setup() {
	Serial.begin(9600, SERIAL_7E1, SERIAL_RX_ONLY, 255);
	start();
}

void P1Interface::store(int data) {
	if (messageLength < MAX_MESSAGE_LENGTH) {
		message[messageLength] = data;
		messageLength++;
	} else {
		start();
	}
}

// Data readout
//
// The Metering System transmits the data message, as described below, immediately following the activation through the Request signal.
// /XXX5Identification CR LF CR LF Data ! CR LF
//
// For our meter:
// /KMP5 KA6Uxxxxxxxxxxx
//
// 0-0:96.1.1(xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx)
// 1-0:1.8.1(06739.940*kWh)
// 1-0:1.8.2(05960.836*kWh)
// 1-0:2.8.1(00000.000*kWh)
// 1-0:2.8.2(00000.000*kWh)
// 0-0:96.14.0(0001)
// 1-0:1.7.0(0000.30*kW)
// 1-0:2.7.0(0000.00*kW)
// 0-0:96.13.1()
// 0-0:96.13.0()
// 0-1:24.1.0(3)
// 0-1:96.1.0(xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx)
// 0-1:24.3.0(160616230000)(08)(60)(1)(0-1:24.2.1)(m3)
// (04003.384)
// !
//
void P1Interface::read() {

	if (state == WAIT || state == DATA || state == END1 || state == END2) {
		if (Serial.available()) {
			int data = Serial.read();

			if (state == WAIT) {
				// wait for start of message
				// discard everything else
				if (data == '/') {
					// start of message detected
					store(data);
					state = DATA;
				}
			} else if (state == DATA) {
				// receive message
				store(data);
				if (data == '!') {
					// end of message detected
					state = END1;
				}
			} else if (state == END1) {
				// assume cr
				store(data);
				state = END2;
			} else if (state == END2) {
				// assume lf
				store(data);
				memset(message + messageLength, 0,
						MAX_MESSAGE_LENGTH - messageLength);
				state = READY;
			}
		}
	}
}

bool P1Interface::isReady() {
	return state == READY;
}

uint8_t* P1Interface::getMessage() {
	return message;
}

uint16_t P1Interface::getMessageLength() {
	return messageLength;
}

