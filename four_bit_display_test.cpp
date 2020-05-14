#include <Arduino.h>
#include "four_bit_display.h"
#include <string.h>

FourBitDisplay fbd(4,6,3);

void setup()
{
}

void loop()
{
    char *val = "34";
    short arraySize = strlen(val);
    char *just = "r";
    fbd.printToDisplay(val,arraySize,just);
}