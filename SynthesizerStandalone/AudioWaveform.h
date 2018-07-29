#pragma once

#include <math.h>
//#include <atomic>
#include <boost/atomic.hpp>

namespace audio 
{
	class AudioWaveform // This class contains audio function used by the AudioSynthesizer class.
	{
	private:

		boost::atomic<int> m_iWaveFrequency = 440;
		boost::atomic<double> m_dbWaveAmplitude = 0.0;

	protected:

		double waveformFunction(double dbSampleTime);

	public:

		// Oscillator frequency. Range int 1 - 20000.
		void setWaveFrequency(int iNewFrequency);
		// Amplitude multiplier. Range double 0.0 - 1.0.
		void setWaveAmplitude(double dbNewAmplitude);

	};
}
