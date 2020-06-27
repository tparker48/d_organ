#include "MainComponent.h"

#ifdef RUNNING_WINDOWS

void MainComponent::updatePotentiometers() {
}

void MainComponent::init() {
    setSize(700, 600);

    for (int mcp = 0; mcp < 4; mcp++)
    {
        for (int pot = 0; pot < 8; pot++)
        {
            mockPotentiometers[mcp][pot] = new Slider();
            mockPotentiometers[mcp][pot]->setSliderStyle(Slider::LinearBarVertical);
            mockPotentiometers[mcp][pot]->setRange(0.0, 1023, 1.0);
            mockPotentiometers[mcp][pot]->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
            mockPotentiometers[mcp][pot]->setPopupDisplayEnabled(true, false, this);
            mockPotentiometers[mcp][pot]->setTextValueSuffix("MCP: " + String(mcp) + ", Pot: " + String(pot));
            mockPotentiometers[mcp][pot]->setValue(512.0);
            addAndMakeVisible(mockPotentiometers[mcp][pot]);
        }
    }
}

void MainComponent::releaseResources() {
    for (int mcp = 0; mcp < 4; mcp++)
    {
        for (int pot = 0; pot < 8; pot++)
        {
            delete mockPotentiometers[mcp][pot];
        }
    }
}

void MainComponent::paint(Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Mock Potentiometer GUI", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void MainComponent::resized() {
    for (int mcp = 0; mcp < 4; mcp++)
    {
        for (int pot = 0; pot < 8; pot++)
        {
            mockPotentiometers[mcp][pot]->setBounds(40 + 10 * pot, 30 + 100 * mcp, 40, 100);
        }
    }
}

#endif