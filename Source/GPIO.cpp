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