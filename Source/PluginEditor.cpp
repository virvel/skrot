#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LaF.h"


SkrotAudioProcessorEditor::SkrotAudioProcessorEditor (SkrotAudioProcessor& p)
: AudioProcessorEditor (&p), threshold {0.5}, processor (p)
{
    
    setSize (400, 300);
    setLookAndFeel (&newLaF);
    
    addAndMakeVisible (thresholdSlider);
    thresholdSlider.addListener (this);
    thresholdSlider.setBounds (Rectangle<int> {50,0,200,40});
    thresholdSlider.setRange (0.0f,1.0f);
    
    addAndMakeVisible (powerSlider);
    powerSlider.addListener (this);
    powerSlider.setBounds (Rectangle<int> {50, 30, 200, 40});
    powerSlider.setRange (0, 10);
    
}

SkrotAudioProcessorEditor::~SkrotAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}


void SkrotAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (juce::Font {"Open Sans", 14.0f, bold});
    g.drawText ("SKROT", Rectangle<int> {5,0,50,30}, 0);
    
    updateCurve();
    g.setColour (Colour {203, 171, 210});
    g.strokePath (path, juce::PathStrokeType {3.0f,
                                              juce::PathStrokeType::curved,
                                              juce::PathStrokeType::rounded});
    
}

// Update path to represent the current threshold value
void inline SkrotAudioProcessorEditor::updateCurve()
{
    path.clear();
    
    float sample;
    int width = getLocalBounds().getWidth();
    int height = getLocalBounds().getHeight();
    int y = height/2;
    
    path.startNewSubPath (0, y);
    
    for (int i = 0; i < width; ++i)
    {
        sample = sin (i*6.28/width);
        
        sample = pow (sample,static_cast<int>(power)*2+1);
        
        if (sample >= threshold){
            sample = 2*threshold - sample;}
        else if (sample <= -threshold)
            sample = -2*threshold - sample;
        

        path.lineTo (i, y*sample+y);
    }
}

void SkrotAudioProcessorEditor::sliderValueChanged (Slider* s)
{
    processor.setThreshold (thresholdSlider.getValue());
    threshold = thresholdSlider.getValue();
    power = powerSlider.getValue();
    repaint();
}
    
void SkrotAudioProcessorEditor::resized()
{
    
}
