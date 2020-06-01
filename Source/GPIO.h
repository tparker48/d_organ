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

#ifndef JUCE_GPIO_GPIO_H
#define JUCE_GPIO_GPIO_H

#include <stdio.h>

namespace JUCE_GPIO
{
  class GPIO
  {
  public:
    void init(int pin, char *direction); // sets the direction of a pin. Allowed values are "in" and "out"
    void write(int pin, int value); // sets the output value of the pin. Allowed values are 1 and 0.
    int read(int pin); // reads input value from the specified GPIO pin. Returns 1 or 0.
  private:
    const char path[21] = "/sys/class/gpio/gpio";
    char pinpath[40];
  };
}

#endif