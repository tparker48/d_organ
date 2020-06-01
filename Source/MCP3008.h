// This class was created as a modification some code by Gabriel Perez-Cerezo
// The original comments from that code have been preserved:

/*
  COPYRIGHT (c) 2013 Gabriel Perez-Cerezo. <http://gpcf.eu>

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

#ifndef JUCE_GPIO_MCP3008_H
#define JUCE_GPIO_MCP3008_H

#include "GPIO.h"
#include <stdio.h>

namespace JUCE_GPIO
{
  class MCP3008
  {
    public:
      MCP3008();
      void clocked_write(int clockpin, int out, int value);
      int clocked_read(int clockpin, int in);
      void mcp3008_select_chip(int bin[], int inputnum);
      int power_of_2(int exp);
      int mcp3008_value(int inputnum, int clock, int in, int out, int cs);

    private:
      JUCE_GPIO::GPIO my_gpio;
  };
}

#endif