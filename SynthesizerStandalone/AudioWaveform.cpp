#include "AudioWaveform.h"

double AudioWaveform::waveformFunction(double dbSampleTime)
{
	return m_dbWaveAmplitude * (sin(m_iWaveFrequency * 2 * acos(-1) * dbSampleTime));
}

void AudioWaveform::setWaveFrequency(int iNewFrequency)
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
