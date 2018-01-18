#include "PluginProcessor.h"
#include "PluginEditor.h"


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

const String SkrotAudioProcessor::getName() const {return JucePlugin_Name;}

bool SkrotAudioProcessor::acceptsMidi() const {return false;}

bool SkrotAudioProcessor::producesMidi() const {return false; }

bool SkrotAudioProcessor::isMidiEffect() const {return false;}

double SkrotAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SkrotAudioProcessor::getNumPrograms()
{
    return 1;
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

void SkrotAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    threshold.store (0.5f);
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
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

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
    
    // Clear buffer
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto inputData = buffer.getReadPointer (channel);
        auto channelData = buffer.getWritePointer (channel);
        
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            if (inputData[i] >= threshold.load())
                channelData[i] = 2*threshold.load() - inputData[i];
            else if (inputData[i] <= -threshold.load())
                channelData[i] = -inputData[i] - 2*threshold.load();
            else
                channelData[i] = inputData[i];
            
        }
    }
}

bool SkrotAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* SkrotAudioProcessor::createEditor()
{
    return new SkrotAudioProcessorEditor (*this);
}

void SkrotAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void SkrotAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

void SkrotAudioProcessor::setThreshold(float val)
{
    threshold.store (val);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SkrotAudioProcessor();
}
