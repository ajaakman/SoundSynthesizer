#pragma once
#include <windows.h>

namespace gui
{
	class SynthesizerWindow;
}

namespace clr
{
	class TestWindow
	{
	private:
		void InitMessageLoop();
	public:
		TestWindow();
		~TestWindow();

		HWND Create(const wchar_t* lpWindowName = L"Audio Synthesizer by Artur Jaakman. Use Q2W3ER... Keys to Play!", DWORD dwStyle = WS_OVERLAPPEDWINDOW, DWORD dwExStyle = 0, int x = 796, int y = 404, int width = 1024, int height = 576, HWND hWNDWParent = (HWND)0, HMENU hmenu = (HMENU)0);

		gui::SynthesizerWindow* synth;

		void PianoKeyPress(const int& nKey);

		void PianoKeyRelease(const int& nKey);
		
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
