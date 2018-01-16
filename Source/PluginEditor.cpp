#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SkrotAudioProcessorEditor::SkrotAudioProcessorEditor (SkrotAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    addAndMakeVisible(textbox);
    textbox.addListener(this);
    textbox.setBounds(100,0, 100, 100);
    
    setSize (400, 300);
}

SkrotAudioProcessorEditor::~SkrotAudioProcessorEditor()
{
}

//==============================================================================
void SkrotAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (juce::Colours::black);

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("SKROT", getLocalBounds(), Justification::centred, 1);
    
    for (int i = 0; i < 100; i++)
    {
        path.lineTo(static_cast<float>(i), static_cast<float>(i));
    }
    
    g.strokePath(path, juce::PathStrokeType(2.0f));
    
    
}

void textEditorTextChanged (TextEditor& textbox)
{
    std::cout << textbox.getText();
}

void SkrotAudioProcessorEditor::resized()
{
    
}
