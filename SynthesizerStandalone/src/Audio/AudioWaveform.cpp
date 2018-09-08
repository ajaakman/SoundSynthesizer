#include "AudioWaveform.h"
#include <iostream>

namespace audio
{		
	AudioWaveform::AudioWaveform()
		: m_dWaveAmplitude(0.0), m_dAttackTime(0.1), m_dDecayTime(0.0), m_dReleaseTime(0.5), m_dSustainAmp(1.0), m_dStartAmp(1.0), m_dTriggerOnTime(0.0), m_dTriggerOffTime(0.0), m_bNoteOn(false)
	{	}

	AudioWaveform::Oscillator::Oscillator()
		: m_dWaveAmplitude(1.0), m_dWaveFrequency(444.0), m_nWaveType(0), m_nSawParts(50), m_dVibratoFreq(0.0), m_dVibratoAmplitude(0.0), m_dTremoloFreq(0.1), m_dTremoloAmplitude(0.01)
	{	}

	void AudioWaveform::Oscillator::SetWaveFrequency(const double& dNewFrequency)
	{
		if (dNewFrequency < 1.0)
			m_dWaveFrequency = 1.0;
		else if (dNewFrequency > 20000.0)
			m_dWaveFrequency = 20000.0;
		else
			m_dWaveFrequency = dNewFrequency;
	}

	void AudioWaveform::Oscillator::SetWaveAmplitude(const double& dNewAmplitude)
	{
		if (dNewAmplitude < 0.0)
			m_dWaveAmplitude = 0.0;
		else if (dNewAmplitude > 1.0)
			m_dWaveAmplitude = 1.0;
		else
			m_dWaveAmplitude = dNewAmplitude;
	}

	void AudioWaveform::Oscillator::SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts)
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

	void AudioWaveform::Oscillator::SetVibratoFrequency(const double& dNewFrequency)
	{
		if (dNewFrequency < 0.0)
			m_dVibratoFreq = 0.0;
		else if (dNewFrequency > 100.0)
			m_dVibratoFreq = 100.0;
		else
			m_dVibratoFreq = dNewFrequency;
	}

	void AudioWaveform::Oscillator::SetVibratoAmplitude(const double& dNewAmplitude)
	{
		if (dNewAmplitude < 0.0)
			m_dVibratoAmplitude = 0.0;
		else if (dNewAmplitude > 1.0)
			m_dVibratoAmplitude = 1.0;
		else
			m_dVibratoAmplitude = dNewAmplitude;
	}

	void AudioWaveform::Oscillator::SetTremoloFrequency(const double& dNewFrequency)
	{
		if (dNewFrequency < 0.0)
			m_dTremoloFreq = 0.0;
		else if (dNewFrequency > 100.0)
			m_dTremoloFreq = 100.0;
		else
			m_dTremoloFreq = dNewFrequency;
	}

	void AudioWaveform::Oscillator::SetTremoloAmplitude(const double& dNewAmplitude)
	{
		if (dNewAmplitude < 0.0)
			m_dTremoloAmplitude = 0.0;
		else if (dNewAmplitude > 1.0)
			m_dTremoloAmplitude = 1.0;
		else
			m_dTremoloAmplitude = dNewAmplitude;
	}

	double AudioWaveform::Oscillator::AudioFunction(const AudioWaveform& wf)
	{
		double dTremolo = m_dTremoloAmplitude * m_dWaveFrequency * sin(m_dTremoloFreq * 2.0 * acos(-1) * wf.GetSampleTime());
		double dVibrato = m_dVibratoAmplitude * m_dWaveFrequency * sin(m_dVibratoFreq * 2.0 * acos(-1) * wf.GetSampleTime());
		double dFrequency = m_dWaveFrequency * 2.0 * acos(-1) * wf.GetSampleTime() + dVibrato;
		
		switch (m_nWaveType)
		{
		case SQUARE_WAVE:
			return  m_dWaveAmplitude * (sin(dFrequency) ) > 0.0 ? 1.0 : -1.0;
		case TRIANGLE_WAVE:
			return m_dWaveAmplitude * ((asin(sin(dFrequency)) * 2.0 / acos(-1)) );
		case SAW_WAVE:
			return m_dWaveAmplitude * (((2.0 / acos(-1)) * ((m_dWaveFrequency * acos(-1) * fmod(wf.GetSampleTime(), 1.0 / m_dWaveFrequency)) - (acos(-1) / 2.0))) );
		case ANALOG_SAW:
		{
			double dOut = 0.0;

			for (double i = 1; i < m_nSawParts; ++i)
				dOut += (sin(i * dFrequency)) / i;

			return m_dWaveAmplitude * ((dOut * (2.0 / acos(-1))) * dTremolo);
		}
		case NOISE:
			return m_dWaveAmplitude * ((2.0 * ((double)rand() / (double)RAND_MAX) - 1.0) );
		default: // Sine wave.
			return m_dWaveAmplitude * (sin(dFrequency) );
		}
	}

	double AudioWaveform::Envelope()
	{
		double dAmplitude = 0.0;
		double dReleaseAmplitude = 0.0;

		if (m_dTriggerOnTime > m_dTriggerOffTime)
		{
			double dLifeTime = GetSampleTime() - m_dTriggerOnTime;
			// Attack
			if (dLifeTime <= m_dAttackTime)
				dAmplitude = (dLifeTime / m_dAttackTime) * m_dStartAmp;			
			// Decay
			if (dLifeTime > m_dAttackTime && dLifeTime <= (m_dAttackTime * m_dDecayTime))
				dAmplitude = ((dLifeTime - m_dAttackTime) / m_dDecayTime) * (m_dSustainAmp - m_dStartAmp) + m_dStartAmp;
			// Sustian 
			if (dLifeTime > (m_dAttackTime + m_dDecayTime))
				dAmplitude = m_dSustainAmp;		
		}
		else
		{
			//Release
			double dLifeTime = m_dTriggerOffTime - m_dTriggerOnTime;
			
			if (dLifeTime <= m_dAttackTime)
				dReleaseAmplitude = (dLifeTime / m_dAttackTime) * m_dStartAmp;

			if (dLifeTime > m_dAttackTime && dLifeTime <= (m_dAttackTime + m_dDecayTime))
				dReleaseAmplitude = ((dLifeTime - m_dAttackTime) / m_dDecayTime) * (m_dSustainAmp - m_dStartAmp) + m_dStartAmp;

			if (dLifeTime > (m_dAttackTime + m_dDecayTime))
				dReleaseAmplitude = m_dSustainAmp;

			dAmplitude = ((GetSampleTime() - m_dTriggerOffTime) / m_dReleaseTime) * (0.0 - dReleaseAmplitude) + dReleaseAmplitude;
		}
		if (dAmplitude <= 0.0001)
		{
			dAmplitude = 0;
		}

		return dAmplitude;
	}

	double AudioWaveform::WaveformFunction()
	{
		return m_dWaveAmplitude * (Envelope() * (OSC1.AudioFunction(*this) + OSC2.AudioFunction(*this) + OSC3.AudioFunction(*this)));
	}
		
	void AudioWaveform::NoteTriggered(const int& key)
	{
		m_dTriggerOnTime = GetSampleTime();
		m_bNoteOn = true;
	}

	void AudioWaveform::NoteReleased(const int& key)
	{
		m_dTriggerOffTime = GetSampleTime();
		m_bNoteOn = false;
	}	

	void AudioWaveform::SetWaveAmplitude(const double& dNewAmplitude)
	{
		if (dNewAmplitude > 1.0)
			m_dWaveAmplitude = 1.0;
		else if (dNewAmplitude < 0.0)
			m_dWaveAmplitude = 0.0;
		else
			m_dWaveAmplitude = dNewAmplitude;
	}
}
