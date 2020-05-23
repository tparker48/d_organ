#include "mcp3008.h"
#include <stdio.h>
#include <unistd.h>
#include <string>

int main() {
  unsigned int micro = 11609;
  int value[3][8];
  while(1)
  {
    value[0][0] = mcp3008_value(0, 11, 9, 10, 8);
    value[0][1] = mcp3008_value(1, 11, 9, 10, 8);
    value[0][2] = mcp3008_value(2, 11, 9, 10, 8);
    value[0][3] = mcp3008_value(3, 11, 9, 10, 8);
    
    value[1][0] = mcp3008_value(0, 11, 9, 10, 23);
    value[1][1] = mcp3008_value(1, 11, 9, 10, 23);
    value[1][2] = mcp3008_value(2, 11, 9, 10, 23);
    value[1][3] = mcp3008_value(3, 11, 9, 10, 23);
    value[1][4] = mcp3008_value(4, 11, 9, 10, 23);
    value[1][5] = mcp3008_value(5, 11, 9, 10, 23);
    value[1][6] = mcp3008_value(6, 11, 9, 10, 23);
    value[1][7] = mcp3008_value(7, 11, 9, 10, 23);
    
    value[2][0] = mcp3008_value(0, 11, 9, 10, 25);
    value[2][1] = mcp3008_value(1, 11, 9, 10, 25);
    value[2][2] = mcp3008_value(2, 11, 9, 10, 25);
    value[2][3] = mcp3008_value(3, 11, 9, 10, 25);
    value[2][4] = mcp3008_value(4, 11, 9, 10, 25);
    value[2][5] = mcp3008_value(5, 11, 9, 10, 25);
    value[2][6] = mcp3008_value(6, 11, 9, 10, 25);
    value[2][7] = mcp3008_value(7, 11, 9, 10, 25);
    
    printf("Group 1: %d %d %d %d\n", value[0][0],value[0][1],value[0][2],value[0][3]);
    printf("Group 2: %d %d %d %d %d %d %d %d\n", value[1][0],value[1][1],value[1][2],value[1][3], value[1][4],value[1][5],value[1][6],value[1][7]);
    printf("Group 3: %d %d %d %d %d %d %d %d\n", value[2][0],value[2][1],value[2][2],value[2][3], value[2][4],value[2][5],value[2][6],value[2][7]);

    usleep(micro);
  }
  
  return 0;
}
