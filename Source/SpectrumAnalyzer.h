#pragma once

#include <JuceHeader.h>
#include <cstring>

class SpectrumAnalyzer : public juce::Component, private juce::Timer
{
public:
    SpectrumAnalyzer() : forwardFFT (fftOrder), window (fftSize, juce::dsp::WindowingFunction<float>::hann)
    {
        startTimerHz (60);
    }

    void pushNextSampleIntoFifo (float sample) noexcept
    {
        if (fifoIndex == fftSize)
        {
            if (! nextFFTBlockReady)
            {
                std::memset (fftData, 0, sizeof (fftData));
                std::memcpy (fftData, fifo, sizeof (fifo));
                nextFFTBlockReady = true;
            }
            fifoIndex = 0;
        }
        fifo[fifoIndex++] = sample;
    }

    void paint (juce::Graphics& g) override
    {
        g.setColour (juce::Colour::fromFloatRGBA (0.83f, 0.69f, 0.22f, 0.15f)); 
        
        auto width = (float)getLocalBounds().getWidth();
        auto height = (float)getLocalBounds().getHeight();
        
        juce::Path p;
        p.startNewSubPath (0, height);

        for (int i = 0; i < scopeSize; ++i)
        {
            float x = juce::jmap ((float)i, 0.0f, (float)scopeSize, 0.0f, width);
            float y = juce::jmap (scopeData[i], 0.0f, 1.0f, height, 0.0f);
            p.lineTo (x, y);
        }
        
        p.lineTo (width, height);
        p.closeSubPath();
        g.fillPath (p);
    }

private:
    void timerCallback() override
    {
        if (nextFFTBlockReady)
        {
            drawNextFrameOfSpectrum();
            nextFFTBlockReady = false;
            repaint();
        }
    }

    void drawNextFrameOfSpectrum()
    {
        window.multiplyWithWindowingTable (fftData, fftSize);
        forwardFFT.performFrequencyOnlyForwardTransform (fftData);

        auto mindB = -100.0f;
        auto maxdB =    0.0f;

        for (int i = 0; i < scopeSize; ++i)
        {
            auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (float)i / (float)scopeSize) * 0.2f);
            auto fftDataIndex = juce::jlimit (0, fftSize / 2, (int)(skewedProportionX * (float)fftSize / 2));
            auto level = juce::jmap (juce::Decibels::gainToDecibels (fftData[fftDataIndex]) - juce::Decibels::gainToDecibels ((float)fftSize), mindB, maxdB, 0.0f, 1.0f);

            scopeData[i] = level;
        }
    }

    static constexpr int fftOrder = 11;
    static constexpr int fftSize  = 1 << fftOrder;
    static constexpr int scopeSize = 512;

    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;

    float fifo [fftSize];
    float fftData [2 * fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData [scopeSize];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumAnalyzer)
};
