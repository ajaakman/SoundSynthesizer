#include "TestWindow.h"
#include "SynthesizerWindow.h"
#include <thread>

namespace clr
{
	TestWindow::TestWindow()
		:synth(nullptr)
	{		
		synth = new gui::SynthesizerWindow();
	}

	TestWindow::~TestWindow()
	{
		delete reinterpret_cast<gui::SynthesizerWindow*>(synth);
		synth = nullptr;
	}

	void TestWindow::InitMessageLoop()
	{	
		reinterpret_cast<gui::SynthesizerWindow*>(synth)->Create(L"Audio Synthesizer by Artur Jaakman. Use Q2W3ER... Keys to Play!", WS_OVERLAPPEDWINDOW, 0, 796, 404, 1024, 576); // Create window with name "Synthesizer" and style Overlapped.		

		ShowWindow((reinterpret_cast<gui::SynthesizerWindow*>(synth))->Window(), 1);
	
		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0)) // Run the message loop.
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); 
		}
		
		delete reinterpret_cast<gui::SynthesizerWindow*>(synth);
		synth = nullptr;
	}

	HWND TestWindow::Create(const wchar_t* lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int width, int height, HWND hWNDWParent, HMENU hmenu)
	{
		reinterpret_cast<gui::SynthesizerWindow*>(synth)->Create(lpWindowName, dwStyle, dwExStyle, x, y, width, height, hWNDWParent, hmenu); // Create window with name "Synthesizer" and style Overlapped.		
		ShowWindow((reinterpret_cast<gui::SynthesizerWindow*>(synth))->Window(), 1);
		//delete reinterpret_cast<gui::SynthesizerWindow*>(synth);
		//synth = nullptr;
		return reinterpret_cast<gui::SynthesizerWindow*>(synth)->Window();
	}

	void TestWindow::SetMasterVolume(const double & dNewAmplitude)		
	{ 
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.SetMasterVolume(dNewAmplitude);
	}

	void TestWindow::SetWaveAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetWaveAmplitude(dNewAmplitude);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetWaveAmplitude(dNewAmplitude);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetWaveAmplitude(dNewAmplitude);
		}
	}

	void TestWindow::SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetWaveType(nNewWave, nNewSawParts);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetWaveType(nNewWave, nNewSawParts);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetWaveType(nNewWave, nNewSawParts);
		}
	}

	void TestWindow::SetVibratoFrequency(const double& dNewFrequency, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetVibratoFrequency(dNewFrequency);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetVibratoFrequency(dNewFrequency);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetVibratoFrequency(dNewFrequency);
		}
	}

	void TestWindow::SetVibratoAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetVibratoAmplitude(dNewAmplitude);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetVibratoAmplitude(dNewAmplitude);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetVibratoAmplitude(dNewAmplitude);
		}
	}

	void TestWindow::SetTremoloFrequency(const double& dNewFrequency, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetTremoloFrequency(dNewFrequency);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetTremoloFrequency(dNewFrequency);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetTremoloFrequency(dNewFrequency);
		}
	}

	void TestWindow::SetTremoloAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetTremoloAmplitude(dNewAmplitude);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetTremoloAmplitude(dNewAmplitude);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetTremoloAmplitude(dNewAmplitude);
		}
	}

	void TestWindow::SetTune(const int& nNewTune, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetTune(nNewTune);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetTune(nNewTune);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetTune(nNewTune);
		}
	}
	
	void TestWindow::SetFineTune(const double& dNewTune, const int& nOSC)
	{
		if (synth != nullptr)
		{
			if (nOSC == 3) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC3.SetFineTune(dNewTune);
			else if (nOSC == 2) reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC2.SetFineTune(dNewTune);
			else reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.OSC1.SetFineTune(dNewTune);
		}
	}

	void TestWindow::SetAttackTime(const double& dNewTime) 
	{ 
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.ADSR.SetAttackTime(dNewTime);
	}

	void TestWindow::SetStartAmplitude(const double& dNewAmplitude) 
	{ 
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.ADSR.SetStartAmplitude(dNewAmplitude);
	}

	void TestWindow::SetDecayTime(const double& dNewTime)
	{ 
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.ADSR.SetDecayTime(dNewTime);
	}

	void TestWindow::SetSusatainAmplitude(const double& dNewAmplitude)
	{ 
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.ADSR.SetSusatainAmplitude(dNewAmplitude);
	}

	void TestWindow::SetReleaseTime(const double& dNewTime)
	{
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->m_AudioSynthesizer.ADSR.SetReleaseTime(dNewTime);
	}

	void TestWindow::PianoKeyPress(const int& nKey)
	{
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->PianoKeyPress(nKey);
	}

	void TestWindow::PianoKeyRelease(const int& nKey)
	{
		if (synth != nullptr)
			reinterpret_cast<gui::SynthesizerWindow*>(synth)->KeyReleasedUp(nKey);
	}
}
