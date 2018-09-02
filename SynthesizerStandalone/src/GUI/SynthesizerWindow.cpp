#include "SynthesizerWindow.h"
#include <iostream>

namespace gui {

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

	void SynthesizerWindow::OnPaint() // Draws the circle.
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

			for (int i = 0; i < m_WhiteKeys.size(); ++i)
			{			
				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DarkGray, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Gainsboro, 1);
				pRenderTarget->CreateGradientStopCollection( m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
				pRenderTarget->CreateLinearGradientBrush( D2D1::LinearGradientBrushProperties( D2D1::Point2F(m_WhiteKeys[i].rect.left, m_WhiteKeys[i].rect.top), D2D1::Point2F(m_WhiteKeys[i].rect.right, m_WhiteKeys[i].rect.bottom* 2.5f)), p_GradientStops, &p_GradiantBrush);
				pRenderTarget->FillRoundedRectangle(m_WhiteKeys[i], p_GradiantBrush); 
				SafeRelease(&p_GradientStops);
				SafeRelease(&p_GradiantBrush);
				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::LightGray, 1);
				pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
				pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_WhiteKeys[i].rect.left, m_WhiteKeys[i].rect.top), D2D1::Point2F(m_WhiteKeys[i].rect.right, m_WhiteKeys[i].rect.bottom)), p_GradientStops, &p_GradiantBrush);
				pRenderTarget->DrawRoundedRectangle(m_WhiteKeys[i], p_GradiantBrush, 2.0f);
				SafeRelease(&p_GradientStops);
				SafeRelease(&p_GradiantBrush);				
			}

			for (int i = 0; i < m_BlackKeys.size(); ++i)
			{
				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Black, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
				pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
				pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_BlackKeys[i].rect.left, m_BlackKeys[i].rect.top), D2D1::Point2F(m_BlackKeys[i].rect.right, m_BlackKeys[i].rect.bottom* 3.5f)), p_GradientStops, &p_GradiantBrush);
				pRenderTarget->FillRoundedRectangle(m_BlackKeys[i], p_GradiantBrush);
				SafeRelease(&p_GradientStops);
				SafeRelease(&p_GradiantBrush);

				m_GradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
				m_GradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Gray, 1);
				pRenderTarget->CreateGradientStopCollection(m_GradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &p_GradientStops);
				pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(m_BlackKeys[i].rect.left, m_BlackKeys[i].rect.top), D2D1::Point2F(m_BlackKeys[i].rect.right, m_BlackKeys[i].rect.bottom)), p_GradientStops, &p_GradiantBrush);
				pRenderTarget->DrawRoundedRectangle(m_BlackKeys[i], p_GradiantBrush, 2.0f);
				SafeRelease(&p_GradientStops);
				SafeRelease(&p_GradiantBrush);
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

			for (int i = 0; i < m_WhiteKeys.size(); ++i)
			{
			m_WhiteKeys[i] = D2D1::RoundedRect(D2D1::RectF( size.width / 8.0f * i + size.width / 400.0f,
															size.height / 150.0f, 
															size.width / 8.0f * (i + 1) - size.width / 400.0f,
															size.height - size.height / 150.0f), 
															4.0f, 4.0f);
			}
			int j = 0;
			for (int i = 0; i < m_BlackKeys.size(); ++i)
			{
				if (i == 2) j += 2;
				else if (i == 5) j += 2;
				else ++j;
				m_BlackKeys[i] = D2D1::RoundedRect(D2D1::RectF( (size.width / 8.0f * j + size.width / 50.0f) - (size.width / 8.0f)/2,
																size.height / 200.0f,
																(size.width / 8.0f * (j + 1) - size.width / 50.0f) - (size.width / 8.0f)/2,
																(size.height - size.height / 150.0f)/1.6),
																10.0f, 10.0f);
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
		std::cout << "Mouse X: " << pixelX << " Mouse Y: " << pixelY << std::endl;
		m_AudioSynthesizer.setWaveAmplitude(1.0);
		if (pixelX > 200)
			m_AudioSynthesizer.setWaveFrequency(440);
		else
			m_AudioSynthesizer.setWaveFrequency(480);
	}

	void SynthesizerWindow::OnLButtonUp()
	{
		m_AudioSynthesizer.setWaveAmplitude(0.0);
	}
}