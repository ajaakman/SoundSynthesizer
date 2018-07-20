#include "AudioWaveform.h"

double AudioWaveform::waveformFunction(double sampleTime)
{
	return waveAmplitude * (sin(waveFrequency * 2 * acos(-1) * sampleTime));
}

void AudioWaveform::setWaveFrequency(int newFrequency)
{
	if (newFrequency < 1)
		waveFrequency = 1;
	else if (newFrequency > 20000)
		waveFrequency = 20000;
	else
		waveFrequency = newFrequency;
}

void AudioWaveform::setWaveAmplitude(float newAmplitude)
{
	if (newAmplitude > 1.0f)
		waveAmplitude = 1.0f;
	else if (newAmplitude < 0.0f)
		waveAmplitude = 0.0f;
	else
		waveAmplitude = newAmplitude;
}
