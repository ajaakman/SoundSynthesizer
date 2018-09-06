#include "AudioWaveform.h"

namespace audio
{		
	AudioWaveform::AudioWaveform()
		: m_dbWaveAmplitude(0.0), m_dAttackTime(0.5), m_dDecayTime(0.0), m_dReleaseTime(1.0), m_dSustainAmp(1.0), m_dStartAmp(1.0), m_dTriggerOnTime(0.0), m_dTriggerOffTime(0.0), m_bNoteOn(false)
	{	}

	AudioWaveform::Oscillator::Oscillator()
		: m_dWaveAmplitude(1.0), m_dWaveFrequency(444.0), m_nWaveType(0), m_nSawParts(50)
	{	}

	void AudioWaveform::Oscillator::SetWaveFrequency(double dNewFrequency)
	{
		if (dNewFrequency < 1.0)
			m_dWaveFrequency = 1.0;
		else if (dNewFrequency > 20000.0)
			m_dWaveFrequency = 20000.0;
		else
			m_dWaveFrequency = dNewFrequency;
	}

	void AudioWaveform::Oscillator::SetWaveAmplitude(double dNewAmplitude)
	{
		if (dNewAmplitude < 0.0)
			dNewAmplitude = 0.0;
		else if (dNewAmplitude > 1.0)
			dNewAmplitude = 1.0;
		else
			m_dWaveAmplitude = dNewAmplitude;
	}

	void AudioWaveform::Oscillator::SetWaveType(unsigned int nNewWave, unsigned int nNewSawParts)
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

	double AudioWaveform::Oscillator::AudioFunction(const double& dSampleTime)
	{
		switch (m_nWaveType)
		{
		case SQUARE_WAVE:
			return  m_dWaveAmplitude * (sin(m_dWaveFrequency * 2 * acos(-1) * dSampleTime)) > 0.0 ? 1.0 : -1.0;
		case TRIANGLE_WAVE:
			return m_dWaveAmplitude * (asin(sin(m_dWaveFrequency * 2 * acos(-1) * dSampleTime)) * 2.0 / acos(-1));
		case SAW_WAVE:
			return m_dWaveAmplitude * ((2.0 / acos(-1)) * ((m_dWaveFrequency * acos(-1) * fmod(dSampleTime, 1.0 / m_dWaveFrequency)) - (acos(-1) / 2.0)));
		case ANALOG_SAW:
		{
			double dOut = 0.0;

			for (double i = 1; i < m_nSawParts; i++)
				dOut += (sin(i * (m_dWaveFrequency * 2 * acos(-1)) * dSampleTime)) / i;

			return m_dWaveAmplitude * (dOut * (2.0 / acos(-1)));
		}
		case NOISE:
			return m_dWaveAmplitude * (2.0 * ((double)rand() / (double)RAND_MAX) - 1.0);
		default: // Sine wave.
			return m_dWaveAmplitude * (sin(m_dWaveFrequency * 2 * acos(-1) * dSampleTime));
		}
	}

	double AudioWaveform::Envelope()
	{
		double dAmplitude = 0.0;
		double dLifeTime = GetSampleTime() - m_dTriggerOnTime;

		if (m_bNoteOn)
		{
			// Attack
			if (dLifeTime <= m_dAttackTime)
				dAmplitude = (dLifeTime / m_dAttackTime) * m_dStartAmp;
			// Decay
			if (dLifeTime > m_dAttackTime && dLifeTime <= (m_dAttackTime * m_dDecayTime))
				dAmplitude = ((dLifeTime - m_dAttackTime) / m_dDecayTime) * (m_dSustainAmp - m_dStartAmp) + m_dStartAmp;
			// Sustian 
			if (dLifeTime > (m_dAttackTime + m_dDecayTime))
			{
				dAmplitude = m_dSustainAmp;
			}
		}
		else
		{
			//Release
			dAmplitude = ((GetSampleTime() - m_dTriggerOffTime) / m_dReleaseTime) * (0.0 - m_dSustainAmp) + m_dSustainAmp;
		}
		if (dAmplitude <= 0.0001)
		{
			dAmplitude = 0;
		}

		return dAmplitude;
	}

	double AudioWaveform::WaveformFunction()
	{
		return m_dbWaveAmplitude * (Envelope() * (OSC1.AudioFunction(GetSampleTime()) + OSC2.AudioFunction(GetSampleTime()) + OSC3.AudioFunction(GetSampleTime())));
	}
		
	void AudioWaveform::NoteTriggered()
	{
		m_dTriggerOnTime = GetSampleTime();
		m_bNoteOn = true;
	}

	void AudioWaveform::NoteReleased()
	{
		m_dTriggerOffTime = GetSampleTime();
		m_bNoteOn = false;
	}	

	void AudioWaveform::SetWaveAmplitude(double dNewAmplitude)
	{
		if (dNewAmplitude > 1.0)
			m_dbWaveAmplitude = 1.0;
		else if (dNewAmplitude < 0.0)
			m_dbWaveAmplitude = 0.0;
		else
			m_dbWaveAmplitude = dNewAmplitude;
	}
}
