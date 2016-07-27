// The author disclaims copyright to this source code.
#include <Arduino.h>

#include "Button.h"
#include "DigitalInput.h"
#include "RotaryEncoder.h"
#include "Display.h"
#include "P1Interface.h"

/**
 * The SmartMeter application.
 *
 * D1mini edge connector
 * ---------------------
 *
 * pin   | label | ESP  | arduino | circuitry                             | function            |
 * :---: | :---: | :--: | :-----: | :------------------------------------ | :------------------ |
 * JP1.1 | 5V    |      |         | USB 5V                                |                     |
 * JP1.2 |  G    |      |         |                                       |                     |
 * JP1.3 | D4    | IO2  |      2  | pull-up 10k, I2C SCL, LED active low  | ROT CLK             |
 * JP1.4 | D3    | IO0  |      0  | pull-up 10k, I2C SDA                  | ROT DT              |
 * JP1.5 | D2    | IO4  |      4  |                                       | I2C SDA             |
 * JP1.6 | D1    | IO5  |      5  |                                       | I2C SCL             |
 * JP1.7 | RX    |      |         |                                       | P1 RX               |
 * JP1.8 | TX    |      |         |                                       |                     |
 * JP2.1 | 3V3   |      |         |                                       |                     |
 * JP2.2 | D8    | IO15 |     15  | pull-down 10k                         | SPI SS              |
 * JP2.3 | D7    | IO13 |     13  |                                       | SPI MOSI            |
 * JP2.4 | D6    | IO12 |     12  |                                       | SPI MISO            |
 * JP2.5 | D5    | IO14 |     14  |                                       | SPI CLK             |
 * JP2.6 | D0    | IO16 |     16  |                                       | ROT SW              |
 * JP2.7 | A0    |      |         | 100k/220k divider                     |                     |
 * JP2.8 | RST   |      |         | active low                            |                     |
 *
 */

Clock clock;
DigitalInput pinCLK(D4);
DigitalInput pinDT(D3);
DigitalInput pinSW(D0);
Button filterCLK(&clock, &pinCLK, 50, true);
Button filterDT(&clock, &pinDT, 50, true);
Button filterSW(&clock, &pinSW, 50, true);
RotaryEncoder encoder(&filterCLK, &filterDT);
DigitalIn* ccw;
DigitalIn* cw;
Display display;
P1Interface p1(&clock);


void setup() {
	Serial.begin(9600, SERIAL_7E1, SERIAL_RX_ONLY, 255);
	clock.setup();
	pinCLK.setup();
	pinDT.setup();
	pinSW.setup();
	filterCLK.setup();
	filterDT.setup();
	encoder.setup();
	display.setup();
	p1.setup();

	cw = encoder.getCW();
	ccw = encoder.getCCW();
}

void loop() {

	clock.read();
	pinCLK.read();
	pinDT.read();
	pinSW.read();
	filterCLK.read();
	filterDT.read();
	filterSW.read();
	encoder.read();
	p1.read();

	filterCLK.process();
	filterDT.process();
	filterSW.process();
	encoder.process();

	if (cw->get()) {
		display.print('+');
	}
	if (ccw->get()) {
		display.print('-');
	}
	if (filterSW.getPressed()->get()) {
		display.print('#');
	}

	if (p1.isReady()) {
		uint8_t* message = p1.getMessage();
		uint16_t messageLength = p1.getMessageLength();
		display.print(message, messageLength);
		p1.start();
	}

	display.write();
}

