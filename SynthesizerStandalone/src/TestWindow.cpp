#include "TestWindow.h"
#include <thread>
#include "SynthesizerWindow.h"

namespace clr
{
	TestWindow::TestWindow()
	{
		std::thread thread = std::thread(&TestWindow::InitMessageLoop, this);
		thread.detach();
		m_dMasterVolume = 0.0;

		m_dAttackTime = 0.0;
		m_dDecayTime = 0.0;
		m_dSustainAmp = 0.0;

		m_dReleaseTime = 0.0;
		m_dStartAmp = 0.0;

		m_dWaveAmplitude1 = 0.0;
		m_nWaveType1 = 0;
		m_nSawParts1 = 0;

		m_dVibratoFreq1 = 0.0;
		m_dVibratoAmplitude1 = 0.0;
		m_dTremoloFreq1 = 0.0;
		m_dTremoloAmplitude1 = 0.0;

		m_nTune1 = 0;
		m_dFineTune1 = 0.0;


		m_dWaveAmplitude2 = 0.0;
		m_nWaveType2 = 0;
		m_nSawParts2 = 0;

		m_dVibratoFreq2 = 0.0;
		m_dVibratoAmplitude2 = 0.0;
		m_dTremoloFreq2 = 0.0;
		m_dTremoloAmplitude2 = 0.0;

		m_nTune2 = 0;
		m_dFineTune2 = 0.0;

		m_dWaveAmplitude3 = 0.0;
		m_nWaveType3 = 0;
		m_nSawParts3 = 0;

		m_dVibratoFreq3 = 0.0;
		m_dVibratoAmplitude3 = 0.0;
		m_dTremoloFreq3 = 0.0;
		m_dTremoloAmplitude3 = 0.0;

		m_nTune3 = 0;
		m_dFineTune3 = 0.0;
	}

	void TestWindow::InitMessageLoop()
	{
		gui::SynthesizerWindow window;

		window.Create(L"Audio Synthesizer by Artur Jaakman. Use Q2W3ER... Keys to Play!", WS_OVERLAPPEDWINDOW); // Create window with name "Synthesizer" and style Overlapped.		

		ShowWindow(window.Window(), 1);
	
		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0)) // Run the message loop.
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			window.SetMasterVolume(m_dMasterVolume);

			window.SetAttackTime(m_dAttackTime);
			window.SetDecayTime(m_dDecayTime);
			window.SetReleaseTime(m_dReleaseTime);
			window.SetStartAmplitude(m_dStartAmp);
			window.SetSusatainAmplitude(m_dSustainAmp);

			window.SetWaveAmplitude(m_dWaveAmplitude1, 1);
			window.SetWaveType(m_nWaveType1, m_nSawParts1, 1);
			window.SetTune(m_nTune1, 1);
			window.SetFineTune(m_dFineTune1, 1);

			window.SetTremoloAmplitude(m_dTremoloAmplitude1, 1);
			window.SetTremoloFrequency(m_dTremoloFreq1, 1);
			window.SetVibratoAmplitude(m_dVibratoAmplitude1, 1);
			window.SetVibratoFrequency(m_dVibratoFreq1, 1);

			window.SetWaveAmplitude(m_dWaveAmplitude2, 2);
			window.SetWaveType(m_nWaveType2, m_nSawParts2, 2);
			window.SetTune(m_nTune2, 2);
			window.SetFineTune(m_dFineTune2, 2);

			window.SetTremoloAmplitude(m_dTremoloAmplitude2, 2);
			window.SetTremoloFrequency(m_dTremoloFreq2, 2);
			window.SetVibratoAmplitude(m_dVibratoAmplitude2, 2);
			window.SetVibratoFrequency(m_dVibratoFreq2,2);

			window.SetWaveAmplitude(m_dWaveAmplitude3, 3);
			window.SetWaveType(m_nWaveType3, m_nSawParts3, 3);
			window.SetTune(m_nTune3, 3);
			window.SetFineTune(m_dFineTune3, 3);

			window.SetTremoloAmplitude(m_dTremoloAmplitude3, 3);
			window.SetTremoloFrequency(m_dTremoloFreq3, 3);
			window.SetVibratoAmplitude(m_dVibratoAmplitude3, 3);
			window.SetVibratoFrequency(m_dVibratoFreq3, 3);
		}
	}

	TestWindow::~TestWindow()
	{
	}

	void TestWindow::SetMasterVolume(const double & dNewAmplitude)	{ m_dMasterVolume = dNewAmplitude; }
	
	void TestWindow::SetWaveAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (nOSC == 1) m_dWaveAmplitude1 = dNewAmplitude;
		else if (nOSC == 2) m_dWaveAmplitude2 = dNewAmplitude;
		else m_dWaveAmplitude3 = dNewAmplitude;
	}
	void TestWindow::SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts, const int& nOSC)
	{
		if (nOSC == 1)
		{
			m_nWaveType1 = nNewWave;
			m_nSawParts1 = nNewSawParts;
		}
		else if (nOSC == 2) 
		{
			m_nWaveType2 = nNewWave;
			m_nSawParts2 = nNewSawParts;
		}
		else 
		{
			m_nWaveType3 = nNewWave;
			m_nSawParts3 = nNewSawParts;
		}
	}
	void TestWindow::SetVibratoFrequency(const double& dNewFrequency, const int& nOSC)
	{
		if (nOSC == 1) m_dVibratoFreq1 =dNewFrequency;
		else if (nOSC == 2) m_dVibratoFreq2 = dNewFrequency;
		else m_dVibratoFreq3 = dNewFrequency;
	}
	void TestWindow::SetVibratoAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (nOSC == 1) m_dVibratoAmplitude1 = dNewAmplitude;
		else if (nOSC == 2) m_dVibratoAmplitude2 = dNewAmplitude;
		else m_dVibratoAmplitude3 = dNewAmplitude;
	}
	void TestWindow::SetTremoloFrequency(const double& dNewFrequency, const int& nOSC)
	{
		if (nOSC == 1) m_dTremoloFreq1 = dNewFrequency;
		else if (nOSC == 2) m_dTremoloFreq2 = dNewFrequency;
		else m_dTremoloFreq3 = dNewFrequency;
	}
	void TestWindow::SetTremoloAmplitude(const double& dNewAmplitude, const int& nOSC)
	{
		if (nOSC == 1) m_dTremoloAmplitude1 = dNewAmplitude;
		else if (nOSC == 2) m_dTremoloAmplitude2 = dNewAmplitude;
		else m_dTremoloAmplitude3 = dNewAmplitude;
	}
	void TestWindow::SetTune(const int& nNewTune, const int& nOSC)
	{
		if (nOSC == 1) m_nTune1 = nNewTune;
		else if (nOSC == 2) m_nTune2 = nNewTune;
		else m_nTune3 = nNewTune;
	}
	void TestWindow::SetFineTune(const double& dNewTune, const int& nOSC)
	{
		if (nOSC == 1) m_dFineTune1 = dNewTune;
		else if (nOSC == 2) m_dFineTune2 = dNewTune;
		else m_dFineTune3 = dNewTune;
	}

	void TestWindow::SetAttackTime(const double& dNewTime) { m_dAttackTime = dNewTime; }
	void TestWindow::SetStartAmplitude(const double& dNewAmplitude) { m_dSustainAmp = dNewAmplitude; }
	void TestWindow::SetDecayTime(const double& dNewTime) { m_dDecayTime = dNewTime; }
	void TestWindow::SetSusatainAmplitude(const double& dNewAmplitude) { m_dSustainAmp = dNewAmplitude; }
	void TestWindow::SetReleaseTime(const double& dNewTime) { m_dReleaseTime = dNewTime; }

}
