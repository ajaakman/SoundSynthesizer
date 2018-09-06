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

		std::atomic<double> m_dbWaveAmplitude;

		std::atomic<double> m_dAttackTime;
		std::atomic<double> m_dDecayTime;
		std::atomic<double> m_dReleaseTime;

		std::atomic<double> m_dSustainAmp;
		std::atomic<double> m_dStartAmp;

		std::atomic<double> m_dTriggerOnTime;
		std::atomic<double> m_dTriggerOffTime;

		std::atomic<bool> m_bNoteOn = false;

	public:

		struct Oscillator
		{			
			std::atomic<double> m_dWaveAmplitude;
			std::atomic<double> m_dWaveFrequency;
			std::atomic<unsigned int> m_nWaveType;
			std::atomic<unsigned int> m_nSawParts;	

			Oscillator();
			// Passed to the Synthesizer
			double AudioFunction(const double& dSampleTime);
			
			// Oscillator frequency. Range int 1 - 20000.
			void SetWaveFrequency(double dNewFrequency);			
			// Oscillator amplitude. Range double 0.0 - 1.0.
			void SetWaveAmplitude(double dNewAmplitude);			
			// Select wave type: SINE_WAVE, SQUARE_WAVE, TRIANGLE_WAVE, SAW_WAVE, ANALOG_SAW or NOISE. Optional argument sets number of parts for analog saw waves. Does nothing for other waveforms.
			void SetWaveType(unsigned int nNewWave, unsigned int nNewSawParts = 50);
		};
	
		Oscillator OSC1;
		Oscillator OSC2;
		Oscillator OSC3;

	public:
		
		// Amplitude multiplier. Range double 0.0 - 1.0.
		void SetWaveAmplitude(double dNewAmplitude);		
		
		void NoteTriggered();
		void NoteReleased();

	protected:

		AudioWaveform();

		double WaveformFunction();

	private: 

		double Envelope();

		virtual double GetSampleTime() const = 0;

	};
}
