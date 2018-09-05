#include "SynthesizerWindow.h"
#include <iostream>

namespace gui {

	SynthesizerWindow::SynthesizerWindow()
		: pFactory(NULL), pRenderTarget(NULL), p_GradiantBrush(NULL)
	{
		for (unsigned int i = 0; i < m_PianoKeys.size(); ++i)
		{
			if (IsKeyWhite(i)) m_NumofWhiteKeys += 1.0f;
		}
		m_AudioSynthesizer.setWaveType(ANALOG_SAW);
	}

	SynthesizerWindow::~SynthesizerWindow()
	{
		SafeRelease(&pRenderTarget);
		SafeRelease(&p_GradiantBrush);
	}

	LRESULT SynthesizerWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) // Respond to window messages.
	{
		switch (uMsg)
		{
		case WM_CREATE: // Try to create Direct 2Dfactory on window creation.
			if (FAILED(D2D1CreateFactory(
				D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
			{
				return -1;  // Fail CreateWindowEx.
			}
			return 0;

		case WM_DESTROY: // Runs after close but not before destroy.
			DiscardGraphicsResources();
			SafeRelease(&pFactory);
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			OnPaint();
			return 0;

		case WM_SIZE:
			Resize();
			return 0;

		case WM_LBUTTONDOWN:
			OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;

		case WM_LBUTTONUP:
			OnLButtonUp();
			return 0;

		case WM_KEYDOWN:			
			for (unsigned int i = 0; i < m_KeyCodes.size(); ++i)
			{
				if (m_KeyCodes[i] == wParam)
					PianoKeyPress(i);
			}			
			return 0;

		case WM_KEYUP:
			for (unsigned int i = 0; i < m_KeyCodes.size(); ++i)
			{
				if (m_KeyCodes[i] == wParam)
					KeyReleasedUp(i);					
			}
			return 0;
		}
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam); // Default action.
	}

	HRESULT SynthesizerWindow::CreateGraphicsResources() // Create render target and brush.
	{
		HRESULT hr = S_OK; // Return S_OK if render target already exists.
		if (pRenderTarget == NULL)
		{
			RECT rc;
			GetClientRect(m_hwnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			hr = pFactory->CreateHwndRenderTarget( // Create render target.
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(m_hwnd, size), // Window handle and size in pixels.
				&pRenderTarget);

			if (SUCCEEDED(hr)) // Create solid color brush.
			{
				
				

				if (SUCCEEDED(hr)) // ???
				{
					CalculateLayout();
				}
			}
		}
		return hr;
	}

	void SynthesizerWindow::OnPaint() 
	{
		HRESULT hr = CreateGraphicsResources(); // Create render target and brush.
		if (SUCCEEDED(hr))
		{
			PAINTSTRUCT ps;
			BeginPaint(m_hwnd, &ps);

			m_GradientStops[0].position = 0.0f;
			m_GradientStops[1].position = 1.0f;

			pRenderTarget->BeginDraw(); // Signals start of drawing.

			pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black)); // Fills entire render target with a solid color.

			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i) // White Key Outline.
			{			
				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::LightGray, 1);
				if (IsKeyWhite(i))
				{	
					pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
					pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom)), p_GradientStops, &p_GradiantBrush);
					pRenderTarget->DrawRoundedRectangle(m_PianoKeys[i], p_GradiantBrush, 2.0f);
					SafeRelease(&p_GradientStops);
					SafeRelease(&p_GradiantBrush);
				}
			}
			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i) // White Key Fill.
			{
				if (IsKeyWhite(i))
				{
					if (m_bIsKeyPressed[i] == true)
					{
						m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
						m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Gainsboro, 1);
					}
					else
					{
						m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DarkGray, 1);
						m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::White, 1);
					}

					pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
					pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom* 2.5f)), p_GradientStops, &p_GradiantBrush);
					pRenderTarget->FillRoundedRectangle(m_PianoKeys[i], p_GradiantBrush);
					SafeRelease(&p_GradientStops);
					SafeRelease(&p_GradiantBrush);					
				}
			}
			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i) // Black Key Outline.
			{
				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Gray, 1);
				if (!IsKeyWhite(i))
				{						
					pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
					pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom)), p_GradientStops, &p_GradiantBrush);
					pRenderTarget->DrawRoundedRectangle(m_PianoKeys[i], p_GradiantBrush, 2.0f);
					SafeRelease(&p_GradientStops);
					SafeRelease(&p_GradiantBrush);
				}
			}
			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i) // Black Key Fill.
			{
				if (!IsKeyWhite(i))
				{
					if (m_bIsKeyPressed[i] == true)
					{
						m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
						m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Gray, 1);
					}
					else
					{
						m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Black, 1);
						m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
					}
					pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
					pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom* 3.5f)), p_GradientStops, &p_GradiantBrush);
					pRenderTarget->FillRoundedRectangle(m_PianoKeys[i], p_GradiantBrush);
					SafeRelease(&p_GradientStops);
					SafeRelease(&p_GradiantBrush);
				}
			}

			hr = pRenderTarget->EndDraw(); // Signals end of drawing.
			if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
			{
				DiscardGraphicsResources();
			}
			EndPaint(m_hwnd, &ps);
		}
	}

	void SynthesizerWindow::Resize()
	{
		if (pRenderTarget != NULL)
		{
			RECT rc;
			GetClientRect(m_hwnd, &rc); // Gets new size of client area.

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			pRenderTarget->Resize(size);
			CalculateLayout(); 
			InvalidateRect(m_hwnd, NULL, FALSE); // Forces Repainting.
		}
	}

	void SynthesizerWindow::CalculateLayout() 
	{
		if (pRenderTarget != NULL)
		{
			D2D1_SIZE_F size = pRenderTarget->GetSize(); // Returns size of render target in DPIs.
				
			int j = 0;
			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i)
			{
				if (IsKeyWhite(i)) // White Keys
				{
					m_PianoKeys[i] = D2D1::RoundedRect(D2D1::RectF( size.width / m_NumofWhiteKeys * j + size.width / 400.0f,
																	size.height / 150.0f, 
																	size.width / m_NumofWhiteKeys * (j + 1) - size.width / 400.0f,
																	size.height - size.height / 150.0f), 
																	4.0f, 4.0f);
				++j;
				}
			}
			j = 0;
			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i)
			{
				if (!IsKeyWhite(i)) // Black Keys
				{
					m_PianoKeys[i] = D2D1::RoundedRect(D2D1::RectF((	size.width / m_NumofWhiteKeys * j + size.width / (m_NumofWhiteKeys * 5.5f)) + (size.width / m_NumofWhiteKeys) / 2.0f,
																		size.height / 200.0f,
																		(size.width / m_NumofWhiteKeys * (j + 1) - size.width / (m_NumofWhiteKeys * 5.5f)) + (size.width / m_NumofWhiteKeys) / 2.0f,
																		(size.height - size.height / 150.0f) / 1.6f),
																		10.0f, 10.0f);
					
					if (IsBlackKeySkip(i)) j += 2;
					else ++j;
				}
			}
		}
	}

	void SynthesizerWindow::DiscardGraphicsResources() // If device is lost.
	{
		SafeRelease(&pRenderTarget);
		SafeRelease(&p_GradiantBrush);
	}

	void SynthesizerWindow::OnLButtonDown(int pixelX, int pixelY)
	{
		for (unsigned int i = 0; i < m_PianoKeys.size(); ++i)
		{		
			if (!IsKeyWhite(i)) // Black Keys
			{
				if (HitTest(pixelX, pixelY, m_PianoKeys[i]) == 1)
				{
					m_nLastKeyClick = i;
					PianoKeyPress(i);
					break;
				}
			}
			if ((i + 1) == m_PianoKeys.size())
			{
				for (unsigned int j = 0; j < m_PianoKeys.size(); ++j)
				{
					if (IsKeyWhite(j)) // White Keys
					{
						if (HitTest(pixelX, pixelY, m_PianoKeys[j]) == 1)
						{
							m_nLastKeyClick = j;
							PianoKeyPress(j);
							break;
						}
					}
				}
			}
		}

	}

	void SynthesizerWindow::OnLButtonUp()
	{
		m_AudioSynthesizer.setWaveAmplitude(0.0);
		m_bIsKeyPressed[m_nLastKeyClick] = false;
		OnPaint();
	}

	void SynthesizerWindow::KeyReleasedUp(int key)
	{
		m_AudioSynthesizer.setWaveAmplitude(0.0);
		m_bIsKeyPressed[key] = false;
		OnPaint();
	}

	bool SynthesizerWindow::HitTest(int x, int y, D2D1_ROUNDED_RECT key)
	{		
		if ((x > key.rect.left) && (x < key.rect.right) && (y > key.rect.top) && (y < key.rect.bottom))
			return true;
		else
			return false;
	}

	bool SynthesizerWindow::IsKeyWhite(int key)
	{
		key %= 12;
		if (key == 0 || key == 2 || key == 4 || key == 5 || key == 7 || key == 9 || key == 11)
			return true;
		else
			return false;
	}

	bool SynthesizerWindow::IsBlackKeySkip(int key)
	{
		key %= 12;
		if (key == 3 || key == 10)
			return true;
		else
			return false;
	}

	void SynthesizerWindow::PianoKeyPress(int key)
	{		
		m_bIsKeyPressed[key] = true;
		OnPaint();
		m_AudioSynthesizer.setWaveAmplitude(1.0);		
		m_AudioSynthesizer.setWaveFrequency((int)(261.63 * pow(pow(2.0, 1.0 /12.0), key)));
	}
}