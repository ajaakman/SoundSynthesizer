#include "AudioWaveform.h"
#include <iostream>

namespace audio
{			
	AudioWaveform::AudioWaveform()
		: m_dMasterVolume(0.02)
	{	}

	AudioWaveform::Oscillator::Oscillator()
		: m_dWaveAmplitude(0.1), m_dWaveFrequency(444.0), m_nWaveType(1), m_nSawParts(50), m_dVibratoFreq(5.0), m_dVibratoAmplitude(0.003), m_dTremoloFreq(0.1), m_dTremoloAmplitude(0.01), m_nTune(0), m_dFineTune(0.0)
	{	}

	AudioWaveform::Note::Note()
		: m_nNoteID(0), m_dNoteOnTime(0.0), m_dNoteOffTime(0.0), m_bIsNoteActive(false)
	{	}

	AudioWaveform::Envelope::Envelope()
		: m_dAttackTime(0.1), m_dDecayTime(0.0), m_dReleaseTime(0.5), m_dSustainAmp(1.0), m_dStartAmp(1.0)
	{	}

	double AudioWaveform::WaveformFunction()
	{
		std::unique_lock<std::mutex> lm(mutex);
		double dMasterOut = 0.0;

		for (auto &note : m_Notes)
		{
			bool bNoteFinished = false;
			double dVoice = 0.0;

			double dAmplitude = ADSR.ADSREnvelope(*this, note.m_dNoteOnTime, note.m_dNoteOffTime);
			if (dAmplitude <= 0.0) bNoteFinished = true;

			double dSound = m_dMasterVolume *
				(OSC1.AudioFunction(note.m_dNoteOnTime - GetSampleTime(), AudioWaveform::Scale(note.m_nNoteID + OSC1.m_nTune) + OSC1.m_dFineTune)
					+ OSC2.AudioFunction(note.m_dNoteOnTime - GetSampleTime(), AudioWaveform::Scale(note.m_nNoteID + OSC2.m_nTune) + OSC2.m_dFineTune)
					+ OSC3.AudioFunction(note.m_dNoteOnTime - GetSampleTime(), AudioWaveform::Scale(note.m_nNoteID + OSC3.m_nTune) + OSC3.m_dFineTune));

			dVoice = dAmplitude * dSound;

			dMasterOut += dVoice;

			if (bNoteFinished && note.m_dNoteOffTime > note.m_dNoteOnTime)
				note.m_bIsNoteActive = false;
		}

		for (unsigned int i = 0; i < m_Notes.size(); ++i)
		{
			if (!m_Notes[i].m_bIsNoteActive)
				m_Notes.erase(m_Notes.begin() + i);
		}

		return dMasterOut;
	}

	double AudioWaveform::Oscillator::AudioFunction(const double dTime, const double dHertz)
	{
		double dTremolo = m_dTremoloAmplitude * sin(m_dTremoloFreq * PI_2<double> * dTime);
		double dVibrato = m_dVibratoAmplitude * dHertz * sin(m_dVibratoFreq * PI_2<double> * dTime);
		double dFrequency = dHertz * PI_2<double> * dTime + dVibrato;
		
		switch (m_nWaveType)
		{
		case SQUARE_WAVE:
			return (m_dWaveAmplitude + dTremolo) * signbit((sin(dFrequency)));
			//return  m_dWaveAmplitude * (sin(dFrequency) > 0.0 ? 1.0 : -1.0);
		case TRIANGLE_WAVE:
			return (m_dWaveAmplitude + dTremolo) * (asin(sin(dFrequency)) * 2.0 / PI<double>);
		case SAW_WAVE:
			return (m_dWaveAmplitude + dTremolo) * -2 / PI<double> * (atan(1.0 / tan(dHertz * dTime * PI<double> + dVibrato)));
			//return m_dWaveAmplitude * (((2.0 / PI<double>) * ((dHertz * PI<double> * fmod(dTime, 1.0 / dHertz)) - 1)) );
		case ANALOG_SAW:
		{
			double dOut = 0.0;

			for (int i = 1; i < m_nSawParts; ++i)
				dOut += (sin(i * dFrequency)) / i;

			return (m_dWaveAmplitude + dTremolo) * ((dOut * (2.0 / PI<double>)));
		}
		case NOISE:
			return (m_dWaveAmplitude + dTremolo) * ((2.0 * ((double)rand() / (double)RAND_MAX) - 1.0) );
		default: // Sine wave.
			return (m_dWaveAmplitude + dTremolo) * (sin(dFrequency));
		}
	}
	
	double AudioWaveform::Envelope::ADSREnvelope(const AudioWaveform& wf, const double& dTriggerOnTime, const double& dTriggerOffTime)
	{
		double dAmplitude = 0.0;
		double dReleaseAmplitude = 0.0;

		if (dTriggerOnTime > dTriggerOffTime)
		{
			double dLifeTime = wf.GetSampleTime() - dTriggerOnTime;
			// Attack
			if (dLifeTime <= m_dAttackTime)
				dAmplitude = (dLifeTime / m_dAttackTime) * m_dStartAmp;			
			// Decay
			if (dLifeTime > m_dAttackTime && dLifeTime <= (m_dAttackTime + m_dDecayTime))
				dAmplitude = ((dLifeTime - m_dAttackTime) / m_dDecayTime) * (m_dSustainAmp - m_dStartAmp) + m_dStartAmp;
			// Sustian 
			if (dLifeTime > (m_dAttackTime + m_dDecayTime))
				dAmplitude = m_dSustainAmp;		
		}
		else
		{
			//Release
			double dLifeTime = dTriggerOffTime - dTriggerOnTime;
			
			if (dLifeTime <= m_dAttackTime)
				dReleaseAmplitude = (dLifeTime / m_dAttackTime) * m_dStartAmp;

			if (dLifeTime > m_dAttackTime && dLifeTime <= (m_dAttackTime + m_dDecayTime))
				dReleaseAmplitude = ((dLifeTime - m_dAttackTime) / m_dDecayTime) * (m_dSustainAmp - m_dStartAmp) + m_dStartAmp;

			if (dLifeTime > (m_dAttackTime + m_dDecayTime))
				dReleaseAmplitude = m_dSustainAmp;

			dAmplitude = ((wf.GetSampleTime() - dTriggerOffTime) / m_dReleaseTime) * (0.0 - dReleaseAmplitude) + dReleaseAmplitude;
		}

		if (dAmplitude <= 0.0001)		
			dAmplitude = 0;		

		return dAmplitude;
	}	
	
	void AudioWaveform::NoteTriggered(const int& nKey)
	{
		std::unique_lock<std::mutex> lm(mutex);
		bool bIsKeyActive = false;

		for (unsigned int i = 0; i < m_Notes.size(); i++)
		{
			if (m_Notes[i].m_nNoteID == nKey)
				bIsKeyActive = true;
		}

		if (bIsKeyActive)
		{
			for (unsigned int i = 0; i < m_Notes.size(); i++)
			{
				if (m_Notes[i].m_nNoteID == nKey)
					m_Notes[i].m_dNoteOnTime = GetSampleTime();
			}
		}
		else
		{
			Note note;
			note.m_nNoteID = nKey;
			note.m_dNoteOnTime = GetSampleTime();
			note.m_bIsNoteActive = true;
			m_Notes.push_back(note);
		}
	}

	void AudioWaveform::NoteReleased(const int& nKey)
	{		
		std::unique_lock<std::mutex> lm(mutex);
		for (unsigned int i = 0; i < m_Notes.size(); i++)
		{
			if (m_Notes[i].m_nNoteID == nKey)
				m_Notes[i].m_dNoteOffTime = GetSampleTime();
		}
	}	
	
	double AudioWaveform::Scale(const int& nNoteID)
	{
		return 261.63 * pow(1.0594630943592952645618252949463, nNoteID);
	}

	void AudioWaveform::SetMasterVolume(const double& dNewAmplitude)
	{
		if (dNewAmplitude > 1.0)
			m_dMasterVolume = 1.0;
		else if (dNewAmplitude < 0.0)
			m_dMasterVolume = 0.0;
		else
			m_dMasterVolume = dNewAmplitude;
	}

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

	void AudioWaveform::Oscillator::SetTune(const int& dNewTune)
	{
		if (dNewTune < -36)
			m_nTune = -36;
		else if (dNewTune > 36)
			m_nTune = 36;
		else
			m_nTune = dNewTune;
	}

	void AudioWaveform::Oscillator::SetFineTune(const double& dNewTune)
	{
		if (dNewTune < -1.0)
			m_dFineTune = -1.0;
		else if (dNewTune > 1.0)
			m_dFineTune = 1.0;
		else
			m_dFineTune = dNewTune;
	}

	void AudioWaveform::Envelope::SetAttackTime(const double& dNewTime)
	{
		if (dNewTime < 0.0)
			m_dAttackTime = 0.0;
		else if (dNewTime > 5.0)
			m_dAttackTime = 5.0;
		else
		m_dAttackTime = dNewTime;
	}

	void AudioWaveform::Envelope::SetStartAmplitude(const double& dNewAmplitude)
	{
		if (dNewAmplitude < 0.0)
			m_dStartAmp = 0.0;
		else if (dNewAmplitude > 1.0)
			m_dStartAmp = 1.0;
		else
			m_dStartAmp = dNewAmplitude;
	}

	void AudioWaveform::Envelope::SetDecayTime(const double& dNewTime)
	{
		if (dNewTime < 0.0)
			m_dDecayTime = 0.0;
		else if (dNewTime > 5.0)
			m_dDecayTime = 5.0;
		else
			m_dDecayTime = dNewTime;
	}

	void AudioWaveform::Envelope::SetSusatainAmplitude(const double& dNewAmplitude)
	{
		if (dNewAmplitude < 0.0)
			m_dSustainAmp = 0.0;
		else if (dNewAmplitude > 1.0)
			m_dSustainAmp = 1.0;
		else
			m_dSustainAmp = dNewAmplitude;
	}

	void AudioWaveform::Envelope::SetReleaseTime(const double& dNewTime)
	{
		if (dNewTime < 0.0)
			m_dReleaseTime = 0.0;
		else if (dNewTime > 5.0)
			m_dReleaseTime = 5.0;
		else
			m_dReleaseTime = dNewTime;
	}
}
