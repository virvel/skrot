#include "PluginProcessor.h"
#include "PluginEditor.h"


SkrotAudioProcessorEditor::SkrotAudioProcessorEditor (SkrotAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    
    setSize (400, 300);
    setResizable (true, true);

    
    threshold = 0.5;
    
    addAndMakeVisible (slider);
    slider.addListener (this);
    slider.setBounds (Rectangle<int> {50,0,200,40});
    slider.setRange(0.0f,1.0f);
    
}

SkrotAudioProcessorEditor::~SkrotAudioProcessorEditor()
{
}


void SkrotAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (juce::Colours::black);

    g.setColour (Colours::white);
    g.setFont (juce::Font {"Helvetica", 10.0f, bold});
    g.drawText ("SKROT", Rectangle<int> {0,0,50,30}, 0);
    
    updateCurve();
    g.strokePath (path, juce::PathStrokeType {1.0f});
    
}

void inline SkrotAudioProcessorEditor::updateCurve()
{
    path.clear();
    
    float sample;
    int width = getLocalBounds().getWidth();
    int height = getLocalBounds().getHeight();
    int y = height/2;
    
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
