#pragma once

#include <math.h>
#include <atomic>

class AudioWaveform // This class contains audio function used by the AudioSynthesizer class.
{
private:

	std::atomic<int> waveFrequency = 440;
	std::atomic<float> waveAmplitude = 0.0f;

protected:

	double waveformFunction(double sampleTime);

public:
	// Oscillator frequency. Range 1 - 20000.
	void setWaveFrequency(int newFrequency);
	// Amplitude multiplier. Range 0.0f - 1.0f.
	void setWaveAmplitude(float newAmplitude);

};

