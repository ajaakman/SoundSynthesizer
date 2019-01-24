#pragma once

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "BaseWindow.h"
#include "AudioSynthesizer.h" 

#include <array>

#define NUM_OF_KEYS 21

namespace gui {

	class SynthesizerWindow : public BaseWindow<SynthesizerWindow>
	{
	public:

		SynthesizerWindow();
		~SynthesizerWindow();

		PCWSTR  ClassName() const { return L"Circle Window Class"; } // Register the window class. // Window class. Defines the type of windos we're creating.
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		ID2D1Factory								*m_pFactory; // The Dierect2D factory creates Render targets and Device-idnependant resources, such as stroke styles and geometries.
		ID2D1HwndRenderTarget						*m_pRenderTarget; // Render target that is associated with the application window.
		ID2D1LinearGradientBrush					*m_pGradiantBrush;	
		std::array<D2D1_ROUNDED_RECT, NUM_OF_KEYS>	 m_PianoKeys;
		std::array<bool, NUM_OF_KEYS>				 m_bIsKeyPressed;
		audio::AudioSynthesizer						 m_AudioSynthesizer;
		std::array<int, 21>							 m_nKeyCodes{ 81, 50, 87, 51, 69, 82, 53, 84, 54, 89, 55, 85, 73, 57, 79, 48, 80, 219, 187, 221, 8 };
		unsigned int								 m_nLastKeyClick;
		unsigned int								 m_nNumofWhiteKeys;

		D2D1_GRADIENT_STOP							 m_GradientStops[2];
		ID2D1GradientStopCollection					*m_pGradientStops = NULL;		

		HRESULT CreateGraphicsResources(); // Create render target and brush.
		void    OnPaint();
		void    Resize();
		void    CalculateLayout(); 
		void    DiscardGraphicsResources(); // If device is lost.
		void    OnLButtonDown(const int& nPixelX, const int& nPixelY);
		void    OnLButtonUp();
		bool	HitTest(const int& nX, const int& nY, const D2D1_ROUNDED_RECT& key); // Check to see which key the user clicked.
		bool	IsKeyWhite(int nKey);
		bool	IsBlackKeySkip(int nKey);
		void	KeyReleasedUp(const int& nKey);

	public:
		void PianoKeyPress(const int& nKey);
		void PianoKeyRelease(const int& nKey);
		inline void	SetMasterVolume(const double& dNewAmplitude) { m_AudioSynthesizer.SetMasterVolume(dNewAmplitude); }
		void SetWaveAmplitude(const double& dNewAmplitude, const int& nOSC);
		void SetWaveType(const unsigned int& nNewWave, const unsigned int& nNewSawParts, const int& nOSC);
		void SetVibratoFrequency(const double& dNewFrequency, const int& nOSC);
		void SetVibratoAmplitude(const double& dNewAmplitude, const int& nOSC);
		void SetTremoloFrequency(const double& dNewFrequency, const int& nOSC);
		void SetTremoloAmplitude(const double& dNewAmplitude, const int& nOSC);
		void SetTune(const int& nNewTune, const int& nOSC);
		void SetFineTune(const double& dNewTune, const int& nOSC);
		inline void SetAttackTime(const double& dNewTime) { m_AudioSynthesizer.ADSR.SetAttackTime(dNewTime); }
		inline void SetStartAmplitude(const double& dNewAmplitude) { m_AudioSynthesizer.ADSR.SetStartAmplitude(dNewAmplitude); }
		inline void SetDecayTime(const double& dNewTime) { m_AudioSynthesizer.ADSR.SetDecayTime(dNewTime); }
		inline void SetSusatainAmplitude(const double& dNewAmplitude) { m_AudioSynthesizer.ADSR.SetSusatainAmplitude(dNewAmplitude); }
		inline void SetReleaseTime(const double& dNewTime) { m_AudioSynthesizer.ADSR.SetReleaseTime(dNewTime); }
	};

	template <class T> void SafeRelease(T **ppT) // Used to safely release resources when device is lost or window is closed.
	{
		if (*ppT)
		{
			(*ppT)->Release();
			*ppT = NULL;
		}
	}

}