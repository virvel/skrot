#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "LaF.h"


class SkrotAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    SkrotAudioProcessorEditor (SkrotAudioProcessor&);
    ~SkrotAudioProcessorEditor();


    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    void updateCurve();

private:
    Slider thresholdSlider;
    Slider powerSlider;
    Path path;
    float threshold;
    float power;
    LaF newLaF;
    SkrotAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkrotAudioProcessorEditor)
};
