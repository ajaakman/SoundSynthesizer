#pragma once

#include <math.h>
#include <atomic>
#include <vector>

#define SINE_WAVE 0
#define SQUARE_WAVE 1
#define SAW_WAVE 2
#define TRIANGLE_WAVE 3
#define ANALOG_SAW 4
#define NOISE 5
#define PI   3.141592653589793238463
#define PIPI 6.283185307179586476926

namespace audio 
{
	class AudioWaveform // This class contains audio function used by the AudioSynthesizer class.
	{	

	public:
		struct Oscillator
		{
		private:
			std::atomic<double> m_dWaveAmplitude;
			std::atomic<double> m_dWaveFrequency;
			std::atomic<unsigned int> m_nWaveType;
			std::atomic<unsigned int> m_nSawParts;

			std::atomic<double> m_dVibratoFreq;
			std::atomic<double> m_dVibratoAmplitude;

			std::atomic<double> m_dTremoloFreq;
			std::atomic<double> m_dTremoloAmplitude;
		public:
			Oscillator();
			// Passed to the Synthesizer
			double AudioFunction(const double dTime, const double dHertz);
			// Oscillator frequency. Range int 1 - 20000.
			void SetWaveFrequency(const double& dNewFrequency);
			// Oscillator amplitude. Range double 0.0 - 1.0.
			void SetWaveAmplitude(const double& dNewAmplitude);
			// Select wave type: SINE_WAVE, SQUARE_WAVE, TRIANGLE_WAVE, SAW_WAVE, ANALOG_SAW or NOISE. Optional argument sets number of parts for analog saw waves. Does nothing for other waveforms.
			void SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts = 50);

			void SetVibratoFrequency(const double& dNewFrequency);

			void SetVibratoAmplitude(const double& dNewAmplitude);

			void SetTremoloFrequency(const double& dNewFrequency);

			void SetTremoloAmplitude(const double& dNewAmplitude);
		};

		struct Note
		{
		public:
			int m_nNoteID;
			double m_dNoteOnTime;
			double m_dNoteOffTime;
			bool m_bIsNoteActive;

			Note();
		};

		struct Envelope
		{
		private:
			std::atomic<double> m_dAttackTime;
			std::atomic<double> m_dDecayTime;
			std::atomic<double> m_dSustainAmp;

			std::atomic<double> m_dReleaseTime;
			std::atomic<double> m_dStartAmp;

		public:

			Envelope();

			double ADSREnvelope(const AudioWaveform& wf, const double& dTimeOn, const double& dTimeOff);

		};

	private:
		
		std::vector<Note> m_Notes;

		std::atomic<double> m_dMasterVolume;

	public:
		
		Envelope ADSR;
		Oscillator OSC1;
		Oscillator OSC2;
		Oscillator OSC3;
		// Amplitude multiplier. Range double 0.0 - 1.0.
		void SetMasterVolume(const double& dNewAmplitude);
		
		void NoteTriggered(const int& nKey);
		void NoteReleased(const int& nKey);

	protected:

		AudioWaveform();

		double WaveformFunction();

	private: 

		static double Scale(const int& nNoteID);

		virtual const double& GetSampleTime() const = 0;

	};
}
