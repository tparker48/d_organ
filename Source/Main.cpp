#include <JuceHeader.h>
#include "MainComponent.h"


class dorganApplication  : public JUCEApplication
{
public:

    dorganApplication() {}

    void initialise (const String& commandLine) override
    {
    }

    void shutdown() override
    {
    }

    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }

private:

};

START_JUCE_APPLICATION (dorganApplication)