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
/*
This is slightly quicker by a few microseconds than a switch statement.
This is an ASCII lookup table. The reason it includes all off statements before
the 0 is because it allows me to turn off any rubbish that gets printed to the display.
Adding any more items to the lookup table does not hamper performance.
*/


    const static byte bits[] =
            {
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b10111111, //-
                    0b11111111, //off
                    0b11111111, //off
                    0b11000000, //0
                    0b11111001, //1
                    0b10100100, //2
                    0b10110000, //3
                    0b10011001, //4
                    0b10010010, //5
                    0b10000010, //6
                    0b11111000, //7
                    0b10000000, //8
                    0b10010000, //9
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b11111111, //off
                    0b10001000, //A
                    0b10000011, //B
                    0b11000110, //C
                    0b10100001, //D
                    0b10000110, //E
                    0b10001110 //F
            };

    return bits[val];
}

void FourBitDisplay::printToDisplay(char* value, short arraySize ,char *justify)
{
    shiftOut(_dioPin, _sclkPin, MSBFIRST, 0b11111111); //Clear the display
    if(*justify == 'r')
    {
        size_t len = strlen(value);
        char *t = value + len-1;
        char reversed[arraySize];
        short num = 0;

        while(t >= value)
        {
            reversed[num] = *t;
            t = t - 1;
            num++;
        }

        const char *digitalPins = "1248";
        for(unsigned short s = 0; s <arraySize; s++)
        {
            digitalWrite(_rclkPin, LOW);
            // shift out the bits:

            if(reversed[s] == '.')
            {
                byte byteWithDot = (getBits(reversed[s+1]) & 0b01111111);
                shiftOut(_dioPin, _sclkPin, MSBFIRST, byteWithDot);

                for(unsigned short f = s+1; f <= arraySize; f++)
                {
                    reversed[f] = reversed[f+1];
                }

            }
            else
            {
                shiftOut(_dioPin, _sclkPin, MSBFIRST, getBits(reversed[s]));
            }

            shiftOut(_dioPin, _sclkPin, MSBFIRST, digitalPins[s]);

            //take the latch pin high so the LEDs will light up:

            digitalWrite(_rclkPin, HIGH);
        }
    }
    else
    {
        const char *digitalPins = "8421";
        for(unsigned short s = 0; s <arraySize; s++)
        {
            digitalWrite(_rclkPin, LOW);
            // shift out the bits:

            if(value[s+1] == '.')
            {
                byte byteWithDot = (getBits(value[s]) & 0b01111111);
                shiftOut(_dioPin, _sclkPin, MSBFIRST, byteWithDot);

                for(unsigned short f = s+1; f <= arraySize; f++)
                {
                    value[f] = value[f+1];
                }

            }
            else
            {
                shiftOut(_dioPin, _sclkPin, MSBFIRST, getBits(value[s]));
            }
            shiftOut(_dioPin, _sclkPin, MSBFIRST, digitalPins[s]);

            //take the latch pin high so the LEDs will light up:

            digitalWrite(_rclkPin, HIGH);
        }
    }
}