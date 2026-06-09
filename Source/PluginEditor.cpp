#include "PluginProcessor.h"
#include "PluginEditor.h"

MeroyEQAudioProcessorEditor::MeroyEQAudioProcessorEditor (MeroyEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel (&lookAndFeel);
    addAndMakeVisible (audioProcessor.spectrumAnalyzer);
    setSize (1000, 600);
}

MeroyEQAudioProcessorEditor::~MeroyEQAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

void MeroyEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromFloatRGBA (0.1f, 0.1f, 0.1f, 1.0f)); 
    
    auto bounds = getLocalBounds();
    auto titleArea = bounds.removeFromTop (60);
    
    g.setColour (juce::Colour::fromFloatRGBA (0.83f, 0.69f, 0.22f, 1.0f)); 
    g.setFont (juce::Font ("Arial", 32.0f, juce::Font::bold));
    g.drawText ("MEROY EQ", titleArea.reduced (20, 0), juce::Justification::left, true);
    
    g.setColour (juce::Colour::fromFloatRGBA (0.2f, 0.2f, 0.2f, 1.0f));
    g.drawHorizontalLine (titleArea.getBottom(), 0, bounds.getWidth());
}

void MeroyEQAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop (60); // Header
    auto footerHeight = 120;
    auto visualArea = bounds.removeFromTop (bounds.getHeight() - footerHeight);
    
    audioProcessor.spectrumAnalyzer.setBounds (visualArea);
}
