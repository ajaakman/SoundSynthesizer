#include "AudioWaveform.h"

namespace audio
{
	double AudioWaveform::waveformFunction(double dbSampleTime)
	{
		switch (m_nWaveType)
		{
			case SQUARE_WAVE: 
				return m_dbWaveAmplitude * (sin(m_iWaveFrequency * 2 * acos(-1) * dbSampleTime)) > 0.0 ? 1.0 : -1.0;
			case TRIANGLE_WAVE:
				return m_dbWaveAmplitude * (asin(sin(m_iWaveFrequency * 2 * acos(-1) * dbSampleTime)) * 2.0 / acos(-1));
			case SAW_WAVE:
				return m_dbWaveAmplitude * ((2.0 / acos(-1)) * ((m_iWaveFrequency * acos(-1) * fmod(dbSampleTime, 1.0 / m_iWaveFrequency)) - (acos(-1) / 2.0)));
			case ANALOG_SAW:
			{
				double dOut = 0.0;

				for (double i = 1; i < m_nSawParts; i++)
					dOut += (sin(i * (m_iWaveFrequency * 2 * acos(-1)) * dbSampleTime)) / i;

				return m_dbWaveAmplitude * (dOut * (2.0 / acos(-1)));
			}
			case NOISE:
				return m_dbWaveAmplitude * (2.0 * ((double)rand() / (double)RAND_MAX) - 1.0);
			default: // Sine wave.
				return m_dbWaveAmplitude * (sin(m_iWaveFrequency * 2 * acos(-1) * dbSampleTime));
		}
	}

	void AudioWaveform::setWaveFrequency(unsigned int iNewFrequency)
	{
		if (iNewFrequency < 1)
			m_iWaveFrequency = 1;
		else if (iNewFrequency > 20000)
			m_iWaveFrequency = 20000;
		else
			m_iWaveFrequency = iNewFrequency;
	}

	void AudioWaveform::setWaveAmplitude(double dbNewAmplitude)
	{
		if (dbNewAmplitude > 1.0)
			m_dbWaveAmplitude = 1.0;
		else if (dbNewAmplitude < 0.0)
			m_dbWaveAmplitude = 0.0;
		else
			m_dbWaveAmplitude = dbNewAmplitude;
	}
	void AudioWaveform::setWaveType(unsigned int nNewWave, unsigned int nNewSawParts)
	{
		switch (nNewWave)
		{
		case 0: m_nWaveType = SINE_WAVE; break;
		case 1: m_nWaveType = SQUARE_WAVE; break;
		case 2: m_nWaveType = SAW_WAVE; break;
		case 3: m_nWaveType = TRIANGLE_WAVE; break;
		case 4:
		{
			m_nWaveType = ANALOG_SAW;
			if (nNewSawParts > 100)
				m_nSawParts = 100;
			else if (nNewSawParts < 2)
				m_nSawParts = 2;
			else
				m_nSawParts = nNewSawParts;
			break;
		}
		case 5: m_nWaveType = NOISE; break;
		default: m_nWaveType = SINE_WAVE; 
		}
	}
}
