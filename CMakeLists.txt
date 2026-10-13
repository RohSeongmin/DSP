cmake_minimum_required(VERSION 3.22)

project(DSP VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(external/JUCE)

juce_add_plugin(DSPInstrument
    COMPANY_NAME "RohSeongmin"
    PLUGIN_MANUFACTURER_CODE Rsmn
    PLUGIN_CODE Dsp1
    PRODUCT_NAME "DSP Instrument"

    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE

    FORMATS Standalone
)

target_sources(DSPInstrument PRIVATE
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
)

target_compile_features(DSPInstrument PRIVATE cxx_std_20)

target_compile_definitions(DSPInstrument PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(DSPInstrument
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)