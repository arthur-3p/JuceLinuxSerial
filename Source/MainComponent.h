#pragma once

#include <JuceHeader.h>
#include "../serialib/lib/serialib.h"

//==============================================================================
class MainComponent
: public juce::Component
, public juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void timerCallback() override;
    
private:
    //==============================================================================
    char openDevice();
    
    serialib serial;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
