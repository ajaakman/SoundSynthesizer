#pragma once

#include <math.h>
#include <atomic>

class AudioWaveform
{

private:

	std::atomic<int> waveFrequency = 440;

protected:

	double waveformFunction(double sampleTime);

public:

	void setWaveFrequency(int newFrequency);

};

