#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        setColour (juce::Slider::thumbColourId, juce::Colour::fromFloatRGBA (0.83f, 0.69f, 0.22f, 1.0f)); // Gold
        setColour (juce::Slider::rotarySliderFillColourId, juce::Colour::fromFloatRGBA (0.83f, 0.69f, 0.22f, 1.0f));
        setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour::fromFloatRGBA (0.2f, 0.2f, 0.2f, 1.0f));
        
        setColour (juce::TextButton::buttonColourId, juce::Colour::fromFloatRGBA (0.15f, 0.15f, 0.15f, 1.0f));
        setColour (juce::TextButton::textColourOffId, juce::Colour::fromFloatRGBA (0.83f, 0.69f, 0.22f, 1.0f));
    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
        auto fill    = slider.findColour (juce::Slider::rotarySliderFillColourId);

        auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (10);
        auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = 3.0f;
        auto arcRadius = radius - lineW * 0.5f;

        juce::Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
        g.setColour (outline);
        g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            juce::Path valueArc;
            valueArc.addCentredArc (bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, toAngle, true);
            g.setColour (fill);
            g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }

        auto thumbWidth = 4.0f;
        juce::Path thumb;
        thumb.addRectangle (-thumbWidth / 2, -radius, thumbWidth, radius * 0.4f);
        g.setColour (fill);
        g.fillPath (thumb, juce::AffineTransform::rotation (toAngle).translated (bounds.getCentreX(), bounds.getCentreY()));
    }
};
