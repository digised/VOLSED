#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class VolsedEditor : public juce::AudioProcessorEditor
{
public:
    explicit VolsedEditor (VolsedProcessor&);
    ~VolsedEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    VolsedProcessor& audioProcessor;
    juce::LookAndFeel_V4 lookAndFeel;

    juce::Slider gainSlider;
    juce::TextButton bypassButton { "BYPASS" };

    juce::Rectangle<int> titleBounds;
    juce::Rectangle<int> labelBounds;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<SliderAttachment> gainAttachment;
    std::unique_ptr<ButtonAttachment> bypassAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolsedEditor)
};