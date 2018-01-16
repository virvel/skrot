#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class SkrotAudioProcessorEditor  : public AudioProcessorEditor, public TextEditor::Listener
{
public:
    SkrotAudioProcessorEditor (SkrotAudioProcessor&);
    ~SkrotAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    TextEditor textbox;
    Path path;
    SkrotAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkrotAudioProcessorEditor)
};
