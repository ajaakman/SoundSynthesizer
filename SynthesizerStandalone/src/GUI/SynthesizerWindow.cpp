#include "SynthesizerWindow.h"
#include <iostream>

namespace gui {

	SynthesizerWindow::SynthesizerWindow()
		: m_pFactory(NULL), m_pRenderTarget(NULL), m_pGradiantBrush(NULL)
	{
		for (unsigned int i = 0; i < m_PianoKeys.size(); ++i)
		{
			if (IsKeyWhite(i)) m_fNumofWhiteKeys += 1.0f;
		}

		m_AudioSynthesizer.OSC1.SetWaveType(SAW_WAVE);
		m_AudioSynthesizer.OSC1.SetWaveAmplitude(0.0);
		m_AudioSynthesizer.OSC1.SetVibratoAmplitude(0.003);
		m_AudioSynthesizer.OSC1.SetVibratoFrequency(5.0);

		m_AudioSynthesizer.OSC2.SetWaveType(SINE_WAVE);
		m_AudioSynthesizer.OSC2.SetWaveAmplitude(0.8);
		m_AudioSynthesizer.OSC2.SetVibratoAmplitude(0.003);
		m_AudioSynthesizer.OSC2.SetVibratoFrequency(5.0);

		m_AudioSynthesizer.OSC3.SetWaveType(SAW_WAVE);
		m_AudioSynthesizer.OSC3.SetWaveAmplitude(0.0);
		m_AudioSynthesizer.OSC3.SetVibratoAmplitude(0.003);
		m_AudioSynthesizer.OSC3.SetVibratoFrequency(5.0);
	}

	SynthesizerWindow::~SynthesizerWindow()
	{
		SafeRelease(&m_pRenderTarget);
		SafeRelease(&m_pGradiantBrush);
	}

	LRESULT SynthesizerWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) // Respond to window messages.
	{
		switch (uMsg)
		{
		case WM_CREATE: // Try to create Direct 2Dfactory on window creation.
			if (FAILED(D2D1CreateFactory(
				D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory)))
			{
				return -1;  // Fail CreateWindowEx.
			}
			return 0;

		case WM_DESTROY: // Runs after close but not before destroy.
			DiscardGraphicsResources();
			SafeRelease(&m_pFactory);
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
			for (unsigned int i = 0; i < m_nKeyCodes.size(); ++i)
			{
				if (m_nKeyCodes[i] == wParam)
					PianoKeyPress(i);
			}			
			return 0;

		case WM_KEYUP:
			for (unsigned int i = 0; i < m_nKeyCodes.size(); ++i)
			{
				if (m_nKeyCodes[i] == wParam)
					KeyReleasedUp(i);					
			}
			return 0;
		}
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam); // Default action.
	}

	HRESULT SynthesizerWindow::CreateGraphicsResources() // Create render target and brush.
	{
		HRESULT hr = S_OK; // Return S_OK if render target already exists.
		if (m_pRenderTarget == NULL)
		{
			RECT rc;
			GetClientRect(m_hwnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			hr = m_pFactory->CreateHwndRenderTarget( // Create render target.
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(m_hwnd, size), // Window handle and size in pixels.
				&m_pRenderTarget);

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

			m_pRenderTarget->BeginDraw(); // Signals start of drawing.

			m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black)); // Fills entire render target with a solid color.

			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i) // White Key Outline.
			{			
				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::LightGray, 1);
				if (IsKeyWhite(i))
				{	
					m_pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);
					m_pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom)), m_pGradientStops, &m_pGradiantBrush);
					m_pRenderTarget->DrawRoundedRectangle(m_PianoKeys[i], m_pGradiantBrush, 2.0f);
					SafeRelease(&m_pGradientStops);
					SafeRelease(&m_pGradiantBrush);
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

					m_pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);
					m_pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom* 2.5f)), m_pGradientStops, &m_pGradiantBrush);
					m_pRenderTarget->FillRoundedRectangle(m_PianoKeys[i], m_pGradiantBrush);
					SafeRelease(&m_pGradientStops);
					SafeRelease(&m_pGradiantBrush);					
				}
			}
			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i) // Black Key Outline.
			{
				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Gray, 1);
				if (!IsKeyWhite(i))
				{						
					m_pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);
					m_pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom)), m_pGradientStops, &m_pGradiantBrush);
					m_pRenderTarget->DrawRoundedRectangle(m_PianoKeys[i], m_pGradiantBrush, 2.0f);
					SafeRelease(&m_pGradientStops);
					SafeRelease(&m_pGradiantBrush);
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
					m_pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);
					m_pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_PianoKeys[i].rect.left, m_PianoKeys[i].rect.top), D2D1::Point2F(m_PianoKeys[i].rect.right, m_PianoKeys[i].rect.bottom* 3.5f)), m_pGradientStops, &m_pGradiantBrush);
					m_pRenderTarget->FillRoundedRectangle(m_PianoKeys[i], m_pGradiantBrush);
					SafeRelease(&m_pGradientStops);
					SafeRelease(&m_pGradiantBrush);
				}
			}

			hr = m_pRenderTarget->EndDraw(); // Signals end of drawing.
			if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
			{
				DiscardGraphicsResources();
			}
			EndPaint(m_hwnd, &ps);
		}
	}

	void SynthesizerWindow::Resize()
	{
		if (m_pRenderTarget != NULL)
		{
			RECT rc;
			GetClientRect(m_hwnd, &rc); // Gets new size of client area.

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			m_pRenderTarget->Resize(size);
			CalculateLayout(); 
			InvalidateRect(m_hwnd, NULL, FALSE); // Forces Repainting.
		}
	}

	void SynthesizerWindow::CalculateLayout()
	{
		if (m_pRenderTarget != NULL)
		{
			D2D1_SIZE_F size = m_pRenderTarget->GetSize(); // Returns size of render target in DPIs.
				
			int j = 0;
			for (unsigned int i = 0; i < m_PianoKeys.size(); ++i)
			{
				if (IsKeyWhite(i)) // White Keys
				{
					m_PianoKeys[i] = D2D1::RoundedRect(D2D1::RectF( size.width / m_fNumofWhiteKeys * j + size.width / 400.0f,
																	size.height / 150.0f, 
																	size.width / m_fNumofWhiteKeys * (j + 1) - size.width / 400.0f,
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
					m_PianoKeys[i] = D2D1::RoundedRect(D2D1::RectF((	size.width / m_fNumofWhiteKeys * j + size.width / (m_fNumofWhiteKeys * 5.5f)) + (size.width / m_fNumofWhiteKeys) / 2.0f,
																		size.height / 200.0f,
																		(size.width / m_fNumofWhiteKeys * (j + 1) - size.width / (m_fNumofWhiteKeys * 5.5f)) + (size.width / m_fNumofWhiteKeys) / 2.0f,
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
		SafeRelease(&m_pRenderTarget);
		SafeRelease(&m_pGradiantBrush);
	}

	void SynthesizerWindow::OnLButtonDown(const int& nPixelX, const int& nPixelY)
	{
		for (unsigned int i = 0; i < m_PianoKeys.size(); ++i)
		{		
			if (!IsKeyWhite(i)) // Black Keys
			{
				if (HitTest(nPixelX, nPixelY, m_PianoKeys[i]) == 1)
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
						if (HitTest(nPixelX, nPixelY, m_PianoKeys[j]) == 1)
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

	bool SynthesizerWindow::HitTest(const int& nX, const int& nY, const D2D1_ROUNDED_RECT& key)
	{		
		if ((nX > key.rect.left) && (nX < key.rect.right) && (nY > key.rect.top) && (nY < key.rect.bottom))
			return true;
		else
			return false;
	}

	bool SynthesizerWindow::IsKeyWhite(int nKey)
	{
		nKey %= 12;
		if (nKey == 0 || nKey == 2 || nKey == 4 || nKey == 5 || nKey == 7 || nKey == 9 || nKey == 11)
			return true;
		else
			return false;
	}

	bool SynthesizerWindow::IsBlackKeySkip(int nKey)
	{
		nKey %= 12;
		if (nKey == 3 || nKey == 10)
			return true;
		else
			return false;
	}

	void SynthesizerWindow::OnLButtonUp()
	{
		m_bIsKeyPressed[m_nLastKeyClick] = false;
		PianoKeyRelease(m_nLastKeyClick);
	}

	void SynthesizerWindow::KeyReleasedUp(const int& nKey)
	{
		m_bIsKeyPressed[nKey] = false;
		PianoKeyRelease(nKey);
	}

	void SynthesizerWindow::SetMasterVolume(const double & dNewVolume)
	{
		m_AudioSynthesizer.SetMasterVolume(dNewVolume);
	}

	void SynthesizerWindow::PianoKeyPress(const int& nKey)
	{		
		if (!m_bIsKeyPressed[nKey])
		{
			m_bIsKeyPressed[nKey] = true;
			m_AudioSynthesizer.NoteTriggered(nKey);
			OnPaint();
		}
	}

	void SynthesizerWindow::PianoKeyRelease(const int& nKey)
	{		
		m_AudioSynthesizer.NoteReleased(nKey);
		OnPaint();
	}
}