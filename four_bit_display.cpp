/* Written by Christopher Hamer Thursday 14th April 2016.
 * Website: monotok.org
 * Released into public domain
 */

#include "Arduino.h"
#include "four_bit_display.h"

FourBitDisplay::FourBitDisplay(short rclk, short sclk, short dio)
{
    pinMode( rclk, OUTPUT );
    _rclkPin = rclk;
    pinMode( sclk, OUTPUT );
    _sclkPin = sclk;
    pinMode( dio, OUTPUT );
    _dioPin = dio;
}

byte FourBitDisplay::getBits(char val)
{
    byte b;

    if(val != 'c')
    {
        val = toupper(val);
    }

    switch(val)
    {
        case 'A':
            b = 0b10001000;
            break;
        case 'B':
            b = 0b10000011;
            break;
        case 'C':
            b = 0b11000110;
            break;
        case 'c':
            b = 0b10100111;
            break;
        case 'D':
            b = 0b10100001;
            break;
        case 'E':
            b = 0b10000110;
            break;
        case 'F':
            b = 0b10001110;
            break;
        case '0':
            b = 0b11000000;
            break;
        case '1':
            b = 0b11111001;
            break;
        case '2':
            b = 0b10100100;
            break;
        case '3':
            b = 0b10110000;
            break;
        case '4':
            b = 0b10011001;
            break;
        case '5':
            b = 0b10010010;
            break;
        case '6':
            b = 0b10000010;
            break;
        case '7':
            b = 0b11111000;
            break;
        case '8':
            b = 0b10000000;
            break;
        case '9':
            b = 0b10010000;
            break;
        case '.':
            b = 0b01111111;
            break;
        case '-':
            b = 0b10111111;
            break;
        default:
            b = 0b11111111;
    }

    return b;
}

void FourBitDisplay::printToDisplay(char* value, char *justify)
{
    if(*justify == 'r')
    {
        size_t len = strlen(value);
        char *t = value + len-1;
        char reversed[sizeof(value)];
        short num = 0;

        while(t >= value)
        {
            reversed[num] = *t;
            t = t - 1;
            num++;
        }

        const char *digitalPins = "1248";
        for(unsigned short s = 0; s <4; s++)
        {
            digitalWrite(_rclkPin, LOW);
            // shift out the bits:

            shiftOut(_dioPin, _sclkPin, MSBFIRST, getBits(reversed[s]));

            shiftOut(_dioPin, _sclkPin, MSBFIRST, digitalPins[s]);

            //take the latch pin high so the LEDs will light up:
            digitalWrite(_rclkPin, HIGH);
        }
    }
    else
    {
        const char *digitalPins = "8421";
        for(unsigned short s = 0; s <4; s++)
        {
            digitalWrite(_rclkPin, LOW);
            // shift out the bits:

            shiftOut(_dioPin, _sclkPin, MSBFIRST, getBits(value[s]));

            shiftOut(_dioPin, _sclkPin, MSBFIRST, digitalPins[s]);

            //take the latch pin high so the LEDs will light up:
            digitalWrite(_rclkPin, HIGH);
        }
    }
}
