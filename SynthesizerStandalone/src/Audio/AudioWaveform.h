#pragma once

#include <math.h>
#include <atomic>
#include <vector>
#include <mutex>

#define SINE_WAVE 0
#define SQUARE_WAVE 1
#define SAW_WAVE 2
#define TRIANGLE_WAVE 3
#define ANALOG_SAW 4
#define NOISE 5

template<typename T>
constexpr T PI = T(3.141592653589793238463L);

template<typename T>
constexpr T PI_2 = T(6.283185307179586476926);

namespace audio 
{
	class AudioWaveform // This class contains audio function used by the AudioSynthesizer class.
	{
	public:
		struct Oscillator
		{
		friend class AudioWaveform;
		private:
			std::atomic<double> m_dWaveAmplitude;
			std::atomic<double> m_dWaveFrequency;
			std::atomic<unsigned int> m_nWaveType;
			std::atomic<unsigned int> m_nSawParts;

			std::atomic<double> m_dVibratoFreq;
			std::atomic<double> m_dVibratoAmplitude;

			std::atomic<double> m_dTremoloFreq;
			std::atomic<double> m_dTremoloAmplitude;

			std::atomic<int> m_nTune;
			std::atomic<double> m_dFineTune;

			// Oscillator frequency. Range int 1.0 - 20000.0
			void SetWaveFrequency(const double& dNewFrequency);
			
			Oscillator();
			// Passed to the Synthesizer
			double AudioFunction(const double dTime, const double dHertz);
		public:
			// Oscillator amplitude. Range double 0.0 - 1.0
			void SetWaveAmplitude(const double& dNewAmplitude);
			// Select wave type: SINE_WAVE, SQUARE_WAVE, TRIANGLE_WAVE, SAW_WAVE, ANALOG_SAW or NOISE. Optional argument sets number of parts for analog saw waves. Does nothing for other waveforms.
			void SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts = 50);
			// Vibrato LFO frequency. Range double 0.0 - 100.0
			void SetVibratoFrequency(const double& dNewFrequency);
			// Vibrato amplitude multiplier. Range double 0.0 - 1.0
			void SetVibratoAmplitude(const double& dNewAmplitude);
			// Tremolo LFO frequency. Range double 0.0 - 100.0
			void SetTremoloFrequency(const double& dNewFrequency);
			// Tremolo amplitude multiplier. Range double 0.0 - 1.0
			void SetTremoloAmplitude(const double& dNewAmplitude);
			// Tune OSC. Range int -36 - 36.
			void SetTune(const int& dNewTune);
			// Fine tune OSC. Range double 0.0 - 1.0.
			void SetFineTune(const double& dNewTune);
		};

		struct Note
		{
		friend class AudioWaveform;
		private:
			int m_nNoteID;
			double m_dNoteOnTime;
			double m_dNoteOffTime;
			bool m_bIsNoteActive;

			Note();
		};

		struct Envelope
		{
		friend class AudioWaveform;
		private:
			std::atomic<double> m_dAttackTime;
			std::atomic<double> m_dDecayTime;
			std::atomic<double> m_dSustainAmp;

			std::atomic<double> m_dReleaseTime;
			std::atomic<double> m_dStartAmp;

			Envelope();

			double ADSREnvelope(const AudioWaveform& wf, const double& dTimeOn, const double& dTimeOff);

		public:
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

	private:
		
		std::vector<Note> m_Notes; 
		std::mutex mutex;// Using a mutex lock anywhere where we're writing to the m_Notes Struct members;

		std::atomic<double> m_dMasterVolume;

	public:
		
		Envelope ADSR;
		Oscillator OSC1;
		Oscillator OSC2;
		Oscillator OSC3;
		// Amplitude multiplier. Range double 0.0 - 1.0
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
