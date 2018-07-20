#include "AudioWaveform.h"

double AudioWaveform::waveformFunction(double sampleTime)
{
	return sin(waveFrequency * 2 * acos(-1) * sampleTime);
}

void AudioWaveform::setWaveFrequency(int newFrequency)
{
	waveFrequency = newFrequency;
}
