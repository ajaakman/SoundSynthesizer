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
		ID2D1Factory								*pFactory; // The Dierect2D factory creates Render targets and Device-idnependant resources, such as stroke styles and geometries.
		ID2D1HwndRenderTarget						*pRenderTarget; // Render target that is associated with the application window.
		ID2D1LinearGradientBrush					*p_GradiantBrush;	
		std::array<D2D1_ROUNDED_RECT, NUM_OF_KEYS>	 m_PianoKeys;
		std::array<bool, NUM_OF_KEYS>				 m_bIsKeyPressed;
		audio::AudioSynthesizer						 m_AudioSynthesizer;
		std::array<int, 20>							 m_KeyCodes{ 81, 50, 87, 51, 69, 82, 53, 84, 54, 89, 55, 85, 73, 57, 79, 48, 80, 219, 187, 221 };
		int											 m_nLastKeyClick;

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
		bool	HitTest(int x, int y , D2D1_ROUNDED_RECT key); // Check to see which key the user clicked.
		bool	IsKeyWhite(int key);
		bool	IsBlackKeySkip(int key);
		void    PianoKeyPress(int key);
		void	KeyReleasedUp(int key);
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