#pragma once

#include <math.h>
#include <atomic>

#define SINE_WAVE 0
#define SQUARE_WAVE 1
#define SAW_WAVE 2
#define TRIANGLE_WAVE 3
#define ANALOG_SAW 4
#define NOISE 5

namespace audio 
{
	class AudioWaveform // This class contains audio function used by the AudioSynthesizer class.
	{
	private:

		std::atomic<unsigned int> m_iWaveFrequency = 440;
		std::atomic<double> m_dbWaveAmplitude = 0.0;
		std::atomic<unsigned int> m_nWaveType;
		std::atomic<unsigned int> m_nSawParts = 100;

	protected:

		double waveformFunction(double dbSampleTime);

	public:

		// Oscillator frequency. Range int 1 - 20000.
		void setWaveFrequency(unsigned int iNewFrequency);
		// Amplitude multiplier. Range double 0.0 - 1.0.
		void setWaveAmplitude(double dbNewAmplitude);
		// Select wave type: SINE_WAVE, SQUARE_WAVE, TRIANGLE_WAVE, SAW_WAVE, ANALOG_SAW or NOISE. Optional argument sets number of parts for analog saw waves. Does nothing for other waveforms.
		void setWaveType(unsigned int nWaveType, unsigned int nNewSawParts = 50);

	};
}
