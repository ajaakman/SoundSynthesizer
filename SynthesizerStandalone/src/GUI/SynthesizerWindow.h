#pragma once

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "BaseWindow.h"
#include "AudioSynthesizer.h" 

#include <array>

namespace gui {

	class SynthesizerWindow : public BaseWindow<SynthesizerWindow>
	{
	public:

		SynthesizerWindow();
		~SynthesizerWindow();

		PCWSTR  ClassName() const { return L"Circle Window Class"; } // Register the window class. // Window class. Defines the type of windos we're creating.
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		ID2D1Factory						*pFactory; // The Dierect2D factory creates Render targets and Device-idnependant resources, such as stroke styles and geometries.
		ID2D1HwndRenderTarget				*pRenderTarget; // Render target that is associated with the application window.
		ID2D1LinearGradientBrush			*p_GradiantBrush;	
		std::array<D2D1_ROUNDED_RECT, 14>	 m_PianoKeys;
		audio::AudioSynthesizer				 m_AudioSynthesizer;

		D2D1_GRADIENT_STOP					 m_GradientStops[2];
		ID2D1GradientStopCollection			*p_GradientStops = NULL;
		
		float								m_NumofWhiteKeys;

		HRESULT CreateGraphicsResources(); // Create render target and brush.
		void    OnPaint(); // Draws the circle.
		void    Resize();
		void    CalculateLayout(); 
		void    DiscardGraphicsResources(); // If device is lost.
		void    OnLButtonDown(int pixelX, int pixelY);
		void    OnLButtonUp();
		bool	HitTest(float x, float y , D2D1_ROUNDED_RECT key); // Check to see which key the user clicked.
		bool	IsKeyWhite(int key);
		bool	IsBlackKeySkip(int key);
		void    PianoKeyPress(int key);

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