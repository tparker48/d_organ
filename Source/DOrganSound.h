#pragma once
#include <JuceHeader.h>

class DOrganSound: public SynthesiserSound
{
public:
    bool appliesToNote(int) {return true;}
    bool appliesToChannel(int) {return true;}
};