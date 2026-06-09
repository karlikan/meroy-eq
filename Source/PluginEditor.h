#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

class MeroyEQAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MeroyEQAudioProcessorEditor (MeroyEQAudioProcessor&);
    ~MeroyEQAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MeroyEQAudioProcessor& audioProcessor;
    CustomLookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeroyEQAudioProcessorEditor)
};
