#pragma once

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "BaseWindow.h"

class SynthesizerWindow : public BaseWindow<SynthesizerWindow>
{
public:

	SynthesizerWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL){}

	PCWSTR  ClassName() const { return L"Circle Window Class"; } // Register the window class. // Window class. Defines the type of windos we're creating.
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	ID2D1Factory            *pFactory; // The Dierect2D factory creates Render targets and Device-idnependant resources, such as stroke styles and geometries.
	ID2D1HwndRenderTarget   *pRenderTarget; // Render target that is associated with the application window.
	ID2D1SolidColorBrush    *pBrush; // Solid color brush to paint the circle.
	D2D1_ELLIPSE            ellipse;

	HRESULT CreateGraphicsResources(); // Create render target and brush.
	void    OnPaint(); // Draws the circle.
	void    Resize();
	void    CalculateLayout(); // Creates ellipse based on render targets size.
	void    DiscardGraphicsResources(); // If device is lost.

};

template <class T> void SafeRelease(T **ppT) // Used to safely release resources when device is lost or window is closed.
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}