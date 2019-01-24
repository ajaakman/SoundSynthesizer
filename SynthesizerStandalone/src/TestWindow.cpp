#include "TestWindow.h"
#include "SynthesizerWindow.h"
#include <thread>

namespace clr
{
	TestWindow::TestWindow()
	{
		std::thread thread = std::thread(&TestWindow::InitMessageLoop, this);
		thread.detach();
	}

	void TestWindow::InitMessageLoop()
	{
		gui::SynthesizerWindow window;
		synth = &window;

		((gui::SynthesizerWindow*)synth)->Create(L"Audio Synthesizer by Artur Jaakman. Use Q2W3ER... Keys to Play!", WS_OVERLAPPEDWINDOW); // Create window with name "Synthesizer" and style Overlapped.		

		ShowWindow(((gui::SynthesizerWindow*)synth)->Window(), 1);
	
		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0)) // Run the message loop.
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); 
		}
		synth = nullptr;
	}

	TestWindow::~TestWindow()
	{
	}

	void TestWindow::SetMasterVolume(const double & dNewAmplitude)		
	{ 
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetMasterVolume(dNewAmplitude);
	}
	
	void TestWindow::SetWaveAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetWaveAmplitude(dNewAmplitude, nOSC);
	}
	void TestWindow::SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetWaveType(nNewWave, nNewSawParts, nOSC);
	}
	void TestWindow::SetVibratoFrequency(const double& dNewFrequency, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetVibratoFrequency(dNewFrequency, nOSC);
	}
	void TestWindow::SetVibratoAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetVibratoAmplitude(dNewAmplitude, nOSC);
	}
	void TestWindow::SetTremoloFrequency(const double& dNewFrequency, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetTremoloFrequency(dNewFrequency, nOSC);
	}
	void TestWindow::SetTremoloAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetTremoloAmplitude(dNewAmplitude, nOSC);
	}
	void TestWindow::SetTune(const int& nNewTune, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetTune(nNewTune, nOSC);
	}
	void TestWindow::SetFineTune(const double& dNewTune, const int& nOSC)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetFineTune(dNewTune, nOSC);
	}

	void TestWindow::SetAttackTime(const double& dNewTime) 
	{ 
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetAttackTime(dNewTime);
	}

	void TestWindow::SetStartAmplitude(const double& dNewAmplitude) 
	{ 
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetStartAmplitude(dNewAmplitude);
	}

	void TestWindow::SetDecayTime(const double& dNewTime)
	{ 
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetDecayTime(dNewTime);
	}

	void TestWindow::SetSusatainAmplitude(const double& dNewAmplitude)
	{ 
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetSusatainAmplitude(dNewAmplitude);
	}

	void TestWindow::SetReleaseTime(const double& dNewTime)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->SetReleaseTime(dNewTime);
	}

	void TestWindow::PianoKeyPress(const int& nKey)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->PianoKeyPress(nKey);
	}

	void TestWindow::PianoKeyRelease(const int& nKey)
	{
		if (synth != nullptr)
			((gui::SynthesizerWindow*)synth)->PianoKeyRelease(nKey);
	}

}
