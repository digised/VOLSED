cmake_minimum_required(VERSION 3.22)
project(Volsed VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(FetchContent)
FetchContent_Declare(JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG        8.0.6
        GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(Volsed
        COMPANY_NAME             "Amin"
        PLUGIN_MANUFACTURER_CODE Amin
        PLUGIN_CODE              Vlsd
        FORMATS                  VST3 Standalone
        PRODUCT_NAME             "Volsed"
        VST3_CATEGORIES          Fx
        IS_SYNTH                 FALSE
        NEEDS_MIDI_INPUT         FALSE
        NEEDS_MIDI_OUTPUT        FALSE
        COPY_PLUGIN_AFTER_BUILD  FALSE
        ICON_BIG                 "volsed.png")

juce_generate_juce_header(Volsed)

target_sources(Volsed PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp)

target_include_directories(Volsed PRIVATE Source)

target_compile_definitions(Volsed PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(Volsed
        PRIVATE
        juce::juce_audio_utils
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)