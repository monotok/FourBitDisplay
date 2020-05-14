/*
 *
	This is the driver functions for writing to the Bangood 4 Bit 7 segment display.
	The module has two 74HC595 shift registers on the back.
 *
 * Written by Christopher Hamer Thursday 14th April 2016.
 * Website: monotok.org
 * Released into public domain
 *

Below is the segment drawn out to show which letters correspond to which bit in the schematic diagram.

	--a---
	f-   -b
	--g---
	e-   -c
	---d-- - DP

The first byte sent to the register is segment 'A' at the right hand side and segment 'DP' at the
left most side. For example this byte will be sent to display 'C'. The zero's are on and the 1's are
off. This is because the display is a common anode display (CAD).

	C = 0b11000110

There are two 74HC595 shift registers so we need to send 16 bits (two bytes) to the chip. This second register controls which display unit to show the previous byte. This is not inverted so '1' is now on and '0' is
now off. The four left most bits do not matter, these are not connected to anything. This can be seen in the
schematic diagram. These pins are: QH, QF, QG and QE. The right hand most 4 bits are the DIG0, DIG1, DIG2 and DIG3. These control which display unit displays the previous 8 bits.

For example:

0b11111001 will turn on the first (right most) and last (left most) display unit. So it will be "C OFF OFF C".
To display just one C on the right then it will be:
0b11110001

*/
#ifndef
_FOUR_BIT_DISPLAY_H_
#define
_FOUR_BIT_DISPLAY_H_

class FourBitDisplay
{
public:
    FourBitDisplay(short rclk, short sclk, short dio);
    byte getBits(char val);
    void printToDisplay(char *value, short arraySize, char *justify);

private:
    short _rclkPin;
    short _sclkPin;
    short _dioPin;
};


#endif //_FOUR_BIT_DISPLAY_H_
