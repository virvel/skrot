#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LaF.h"


SkrotAudioProcessorEditor::SkrotAudioProcessorEditor (SkrotAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    
    setSize (400, 300);
    setLookAndFeel(&newLaF);
    
    threshold = 0.5;
    
    addAndMakeVisible (slider);
    slider.addListener (this);
    slider.setBounds (Rectangle<int> {50,0,200,40});
    slider.setRange(0.0f,1.0f);
    
}

SkrotAudioProcessorEditor::~SkrotAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}


void SkrotAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (findColour(ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (juce::Font {"Helvetica", 10.0f, bold});
    g.drawText ("SKROT", Rectangle<int> {0,0,50,30}, 0);
    
    updateCurve();
    g.strokePath (path, juce::PathStrokeType {2.0f});
    
}

// Update path to represent the current threshold value
void inline SkrotAudioProcessorEditor::updateCurve()
{
    path.clear();
    
    float sample;
    int width = getLocalBounds().getWidth();
    int height = getLocalBounds().getHeight();
    int y = height/2;
    
    path.startNewSubPath(0, y);
    
    for (int i = 0; i < width; ++i)
    {
        sample = sin (i*6.28/width);
        
        if (sample >= threshold)
        {
            sample = 2*threshold - sample;
        }
        else if (sample <= -threshold)
        {
            sample = -2*threshold - sample;
        }
        
        path.lineTo (i, y*sample+y);
    }
}

void SkrotAudioProcessorEditor::sliderValueChanged (Slider* s)
{
    processor.setThreshold (static_cast<float> (slider.getValue()));
    threshold = static_cast<float> (slider.getValue());
    this->repaint();
}
    
void SkrotAudioProcessorEditor::resized()
{
    
}
