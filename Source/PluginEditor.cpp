#include "PluginEditor.h"

namespace
{
    const juce::Colour background { 0xff15171c };
    const juce::Colour accent     { 0xff35c4b0 };
}

VolsedEditor::VolsedEditor (VolsedProcessor& p)
        : AudioProcessorEditor (&p), audioProcessor (p)
{
    lookAndFeel.setColourScheme (juce::LookAndFeel_V4::getMidnightColourScheme());
    lookAndFeel.setColour (juce::Slider::rotarySliderFillColourId, accent);
    lookAndFeel.setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff2a2e37));
    lookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colours::white);
    lookAndFeel.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    lookAndFeel.setColour (juce::TextButton::buttonColourId, juce::Colour (0xff22262e));
    lookAndFeel.setColour (juce::TextButton::buttonOnColourId, accent);
    lookAndFeel.setColour (juce::TextButton::textColourOffId, juce::Colours::white.withAlpha (0.75f));
    lookAndFeel.setColour (juce::TextButton::textColourOnId, juce::Colour (0xff0e1013));
    setLookAndFeel (&lookAndFeel);

    gainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setRotaryParameters (juce::degreesToRadians (225.0f), juce::degreesToRadians (495.0f), true);
    gainSlider.setDoubleClickReturnValue (true, 0.0);
    gainSlider.setTitle ("Output gain");
    gainSlider.textFromValueFunction = [] (double value)
    {
        return juce::String (value > 0.05 ? "+" : "") + juce::String (value, 1) + " dB";
    };
    gainSlider.valueFromTextFunction = [] (const juce::String& text)
    {
        return text.retainCharacters ("0123456789.-").getDoubleValue();
    };
    addAndMakeVisible (gainSlider);

    bypassButton.setClickingTogglesState (true);
    bypassButton.setTitle ("Bypass");
    addAndMakeVisible (bypassButton);

    gainAttachment   = std::make_unique<SliderAttachment> (audioProcessor.apvts, ParamIDs::outputGain, gainSlider);
    bypassAttachment = std::make_unique<ButtonAttachment> (audioProcessor.apvts, ParamIDs::bypass, bypassButton);

    setResizable (true, true);
    setResizeLimits (270, 300, 720, 800);
    getConstrainer()->setFixedAspectRatio (0.9);
    setSize (360, 400);
}

VolsedEditor::~VolsedEditor()
{
    setLookAndFeel (nullptr);
}

void VolsedEditor::paint (juce::Graphics& g)
{
    g.fillAll (background);

    const auto h = static_cast<float> (getHeight());

    g.setColour (juce::Colours::white.withAlpha (0.92f));
    g.setFont (juce::FontOptions (h * 0.075f, juce::Font::bold));
    g.drawText ("VOLSED", titleBounds, juce::Justification::centred);

    g.setColour (accent);
    const auto line = titleBounds.withTrimmedTop (titleBounds.getHeight() - 2)
            .withSizeKeepingCentre (juce::roundToInt (getWidth() * 0.12f), 2);
    g.fillRect (line);

    g.setColour (juce::Colours::white.withAlpha (0.55f));
    g.setFont (juce::FontOptions (h * 0.04f));
    g.drawText ("OUTPUT", labelBounds, juce::Justification::centred);
}

void VolsedEditor::resized()
{
    const auto w = static_cast<float> (getWidth());
    const auto h = static_cast<float> (getHeight());

    auto area = getLocalBounds().reduced (juce::roundToInt (w * 0.07f));

    titleBounds = area.removeFromTop (juce::roundToInt (h * 0.13f));
    area.removeFromTop (juce::roundToInt (h * 0.03f));

    auto footer = area.removeFromBottom (juce::roundToInt (h * 0.11f));
    bypassButton.setBounds (footer.withSizeKeepingCentre (juce::jmin (footer.getWidth(), juce::roundToInt (w * 0.45f)),
                                                          footer.getHeight()));
    area.removeFromBottom (juce::roundToInt (h * 0.03f));

    labelBounds = area.removeFromTop (juce::roundToInt (h * 0.06f));

    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false,
                                juce::roundToInt (w * 0.35f),
                                juce::jmax (20, juce::roundToInt (h * 0.07f)));
    gainSlider.setBounds (area);
}