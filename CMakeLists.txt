cmake_minimum_required(VERSION 3.22)

project(MeroyEQ VERSION 1.0.0)

# Set up JUCE
include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(juce)

juce_add_plugin(MeroyEQ
    COMPANY_NAME "Vibecode"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE "Vibe"
    PLUGIN_CODE "MryE"
    FORMATS VST3
    PRODUCT_NAME "Meroy EQ"
)

target_sources(MeroyEQ PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

target_compile_definitions(MeroyEQ PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(MeroyEQ PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_dsp
    juce::juce_gui_extra
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_events
    juce::juce_core
    juce::juce_data_structures
)

juce_generate_juce_header(MeroyEQ)
