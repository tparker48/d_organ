// This class was created as a modification some code by Gabriel Perez-Cerezo
// The original comments from that code have been preserved:

/* 
 To use this library, you first need to export the pins.
 A script to do this on a Raspberry Pi is available at 
 <http://gpcf.eu/projects/embedded/code/gpio.sh>

   GPIO.h (C) 2013 Gabriel Perez-Cerezo 
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "GPIO.h"

void JUCE_GPIO::GPIO::init(int pin, char *direction)
{
    FILE *f;
    sprintf(pinpath, "%s%d/direction", path,  pin);
    f = fopen(pinpath, "w");
    fprintf(f, "%s", direction);
    fclose(f);
}

void JUCE_GPIO::GPIO::write(int pin, int value)
{
    sprintf(pinpath, "%s%d/value", path, pin);
    FILE *f;
    f = fopen(pinpath, "w");
    fprintf(f, "%d", value);
    fclose(f);
}

int JUCE_GPIO::GPIO::read(int pin)
{
    sprintf(pinpath, "%s%d/value", path, pin);
    FILE *f;
    f = fopen(pinpath, "r");
    int x;
    if ((x = fgetc(f))!=EOF){
        x = (x==49); /* Returns 1 if the input value is HIGH. (fgetc returns 49 when the input value is HIGH). Returns 0 if it is low.*/
    }else{
        x = -1;        // -1 is returned when there is an error.
    }
    fclose(f);
    return x;   
}