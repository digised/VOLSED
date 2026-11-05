#include "PluginProcessor.h"
#include "PluginEditor.h"

VolsedProcessor::VolsedProcessor()
        : AudioProcessor (BusesProperties()
                                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
          apvts (*this, nullptr, "PARAMS", createLayout())
{
    outputGainParam = apvts.getRawParameterValue (ParamIDs::outputGain);
    bypassParameter = dynamic_cast<juce::AudioParameterBool*> (apvts.getParameter (ParamIDs::bypass));
}

juce::AudioProcessorValueTreeState::ParameterLayout VolsedProcessor::createLayout()
{
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add (std::make_unique<AudioParameterFloat> (
            ParameterID { ParamIDs::outputGain, 1 }, "Output Gain",
            NormalisableRange<float> (-12.0f, 12.0f, 0.1f), 0.0f,
            AudioParameterFloatAttributes().withLabel ("dB")));

    layout.add (std::make_unique<AudioParameterBool> (
            ParameterID { ParamIDs::bypass, 1 }, "Bypass", false));

    return layout;
}

float VolsedProcessor::getTargetGain() const
{
    if (bypassParameter->get())
        return 1.0f;

    return juce::Decibels::decibelsToGain (outputGainParam->load());
}

void VolsedProcessor::prepareToPlay (double sampleRate, int)
{
    smoothedGain.reset (sampleRate, 0.02);
    smoothedGain.setCurrentAndTargetValue (getTargetGain());
}

bool VolsedProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& out = layouts.getMainOutputChannelSet();
    return (out == juce::AudioChannelSet::stereo() || out == juce::AudioChannelSet::mono())
           && out == layouts.getMainInputChannelSet();
}

void VolsedProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const int numSamples = buffer.getNumSamples();
    const int numIn      = getTotalNumInputChannels();
    const int numOut     = getTotalNumOutputChannels();

    for (int ch = numIn; ch < numOut; ++ch)
        buffer.clear (ch, 0, numSamples);

    smoothedGain.setTargetValue (getTargetGain());

    if (! smoothedGain.isSmoothing() && juce::approximatelyEqual (smoothedGain.getTargetValue(), 1.0f))
        return;

    auto* const* data = buffer.getArrayOfWritePointers();

    for (int i = 0; i < numSamples; ++i)
    {
        const float g = smoothedGain.getNextValue();

        for (int ch = 0; ch < numIn; ++ch)
            data[ch][i] *= g;
    }
}

juce::AudioProcessorEditor* VolsedProcessor::createEditor()
{
    return new VolsedEditor (*this);
}

void VolsedProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.copyState().createXml())
        copyXmlToBinary (*xml, destData);
}

void VolsedProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VolsedProcessor();
}