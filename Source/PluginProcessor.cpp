#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SkrotAudioProcessor::SkrotAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

SkrotAudioProcessor::~SkrotAudioProcessor()
{
}

//==============================================================================
const String SkrotAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SkrotAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SkrotAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SkrotAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SkrotAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SkrotAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SkrotAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SkrotAudioProcessor::setCurrentProgram (int index)
{
}

const String SkrotAudioProcessor::getProgramName (int index)
{
    return {};
}

void SkrotAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SkrotAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    threshold.store(0.5f);
}

void SkrotAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SkrotAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SkrotAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();


    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        auto inputData = buffer.getReadPointer (channel);
        
        float* channelData = buffer.getWritePointer (channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            
            if (*inputData >= threshold.load()) {
                *channelData = 2*threshold.load() - *inputData;
            }
            else if (*inputData <= -threshold.load())
            {
                *channelData = - *inputData - 2*threshold.load();
            }
            else {
                *channelData = *inputData;
            }
            channelData++;
            inputData++;
        }
    }
}

//==============================================================================
bool SkrotAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* SkrotAudioProcessor::createEditor()
{
    return new SkrotAudioProcessorEditor (*this);
}

//==============================================================================
void SkrotAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SkrotAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SkrotAudioProcessor();
}
