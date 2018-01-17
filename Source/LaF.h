#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class LaF: public LookAndFeel_V4 {
    
    public:
        LaF();
        ~LaF();

    void drawLinearSlider(Graphics &, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider &) override;

    
};
