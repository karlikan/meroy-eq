#pragma once

#include <JuceHeader.h>

class MeroyEQAudioProcessor : public juce::AudioProcessor
{
public:
    static constexpr int maxBands = 24;
    enum class PhaseMode { LowLatency, Natural, Linear };

    MeroyEQAudioProcessor();
    ~MeroyEQAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
    
    #include "SpectrumAnalyzer.h"
    SpectrumAnalyzer spectrumAnalyzer;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    using Filter = juce::dsp::IIR::Filter<float>;
    using FilterChain = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter, Filter, Filter, Filter, Filter, 
                                                 Filter, Filter, Filter, Filter, Filter, Filter, Filter, Filter,
                                                 Filter, Filter, Filter, Filter, Filter, Filter, Filter, Filter>;
    
    FilterChain leftChain, rightChain;
    
    void updateFilters();
    void updateSingleFilter(int index, double sampleRate);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeroyEQAudioProcessor)
};
