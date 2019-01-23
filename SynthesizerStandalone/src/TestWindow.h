#pragma once

namespace clr
{

	class TestWindow
	{
	private:
		void InitMessageLoop();

		double m_dMasterVolume;

		double m_dAttackTime;
		double m_dDecayTime;
		double m_dSustainAmp;

		double m_dReleaseTime;
		double m_dStartAmp;

		double m_dWaveAmplitude1;
		unsigned int m_nWaveType1;
		unsigned int m_nSawParts1;

		double m_dVibratoFreq1;
		double m_dVibratoAmplitude1;

		double m_dTremoloFreq1;
		double m_dTremoloAmplitude1;

		int m_nTune1;
		double m_dFineTune1;

		double m_dWaveAmplitude2;
		unsigned int m_nWaveType2;
		unsigned int m_nSawParts2;

		double m_dVibratoFreq2;
		double m_dVibratoAmplitude2;

		double m_dTremoloFreq2;
		double m_dTremoloAmplitude2;

		int m_nTune2;
		double m_dFineTune2;

		double m_dWaveAmplitude3;
		unsigned int m_nWaveType3;
		unsigned int m_nSawParts3;

		double m_dVibratoFreq3;
		double m_dVibratoAmplitude3;

		double m_dTremoloFreq3;
		double m_dTremoloAmplitude3;

		int m_nTune3;
		double m_dFineTune3;
	public:
		TestWindow();
		~TestWindow();
		// Amplitude multiplier. Range double 0.0 - 1.0
		void SetMasterVolume(const double& dNewAmplitude);
		// Oscillator amplitude. Range double 0.0 - 1.0
		void SetWaveAmplitude(const double& dNewAmplitude, const int& nOSC);
		// Select wave type: SINE_WAVE, SQUARE_WAVE, TRIANGLE_WAVE, SAW_WAVE, ANALOG_SAW or NOISE. Optional argument sets number of parts for analog saw waves. Does nothing for other waveforms.
		void SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts, const int& nOSC);
		// Vibrato LFO frequency. Range double 0.0 - 100.0
		void SetVibratoFrequency(const double& dNewFrequency, const int& nOSC);
		// Vibrato amplitude multiplier. Range double 0.0 - 1.0
		void SetVibratoAmplitude(const double& dNewAmplitude, const int& nOSC);
		// Tremolo LFO frequency. Range double 0.0 - 100.0
		void SetTremoloFrequency(const double& dNewFrequency, const int& nOSC);
		// Tremolo amplitude multiplier. Range double 0.0 - 1.0
		void SetTremoloAmplitude(const double& dNewAmplitude, const int& nOSC);
		// Tune OSC. Range int -36 - 36.
		void SetTune(const int& dNewTune, const int& nOSC);
		// Fine tune OSC. Range double 0.0 - 1.0.
		void SetFineTune(const double& dNewTune, const int& nOSC);
		// Attack time. Range double 0.0 - 50
		void SetAttackTime(const double& dNewTime);
		// Start amplitude multiplier. Range double 0.0 - 1.0
		void SetStartAmplitude(const double& dNewAmplitude);
		// Decay time. Range double 0.0 - 50
		void SetDecayTime(const double& dNewTime);
		// Sustain amplitude multiplier. Range double 0.0 - 1.0
		void SetSusatainAmplitude(const double& dNewAmplitude);
		// Release time. Range double 0.0 - 50
		void SetReleaseTime(const double& dNewTime);
	};

}
