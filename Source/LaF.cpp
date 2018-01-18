#include "LaF.h"

LaF::LaF()
{
    setColour (ResizableWindow::backgroundColourId, Colour { 30, 30, 30});
    
    
    // Slider colors
    setColour (Slider::backgroundColourId, Colour {10, 10, 10});
    setColour (Slider::thumbColourId, Colour {255 ,255 , 255});
    setColour (Slider::trackColourId, Colour {203, 171, 210});
    setColour (Slider::rotarySliderFillColourId, Colour {15, 30, 255});
    setColour (Slider::rotarySliderOutlineColourId, Colour {15, 30, 255});
    setColour (Slider::textBoxTextColourId, Colour {255,255,255});
    setColour (Slider::textBoxOutlineColourId, Colour {255, 0, 0});
    setColour (Slider::textBoxHighlightColourId, Colour {0, 255, 0});
    setColour (Slider::textBoxBackgroundColourId, Colour {0, 255, 0});
    
    // Label colors
    
    setColour(Label::backgroundColourId, Colour {10,10,10});
    setColour(Label::backgroundWhenEditingColourId, Colour {30,30,30});
    setColour(Label::textColourId, Colour {255,255,255});
    setColour(Label::textWhenEditingColourId, Colour {255,255,255});
    setColour(Label::outlineColourId, Colour {0,255,255});
    setColour(Label::outlineWhenEditingColourId, Colour {255,255,255});
    
}

LaF::~LaF()
{
}

void LaF::drawLinearSlider(Graphics & g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos,
                           float maxSliderPos, const Slider::SliderStyle,
                           Slider & slider)
{
    g.setColour (findColour (Slider::backgroundColourId));
    g.fillRect(x, y+height/2-2, width, 4);
    g.fillRoundedRectangle(static_cast<float> (x), y+height/2.0f-2.0f, static_cast<float> (width), 4.0f, 2.0f);
    
    g.setColour (findColour (Slider::trackColourId));
    g.fillRoundedRectangle(static_cast<float>(x), static_cast<float>(y)+height/2.0f-2.0f,
                           sliderPos-x, 4.0f, 2.0f);

    
    g.setColour (findColour (Slider::thumbColourId));
    g.fillEllipse(sliderPos-5.0f, height/2.0f-5.0f, 10.0f, 10.0f);
    
}

void LaF::drawLabel(Graphics& g, Label& label)
{
    g.setColour (findColour (Label::backgroundColourId));
    g.fillRoundedRectangle(label.getBounds()
                                .translated(0, -label.getHeight()/2)
                                .toFloat(), 2.0f);
    
    g.setColour (findColour (Label::textColourId));
    g.setFont (juce::Font {"Open Sans", 14.0f, bold});
    g.drawText(label.getText(),label.getBounds()
                                    .translated(3,-label.getHeight()/2), 0);
}
