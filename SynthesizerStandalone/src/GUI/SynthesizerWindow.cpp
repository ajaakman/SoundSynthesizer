#include "SynthesizerWindow.h"
#include <iostream>
// Recalculate drawing layout when the size of the window changes.

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
		std::cout << "Mouse X: "<< GET_X_LPARAM(lParam) << " Mouse Y: " << GET_Y_LPARAM(lParam) << std::endl;
		break;
		//return 0;
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
			hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &pBrush); // Circle color.

			if (SUCCEEDED(hr))
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

		pRenderTarget->BeginDraw(); // Signals start of drawing.

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::LightGray)); // Fills entire render target with a solid color.
		pRenderTarget->FillEllipse(ellipse, pBrush); // Draws a filled ellipse.
		//pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(20, D2D1::Point2F(100, 100)));

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
		CalculateLayout(); // Recalcules ellipse.
		InvalidateRect(m_hwnd, NULL, FALSE); // Forces Repainting.
	}
}

void SynthesizerWindow::CalculateLayout() // Creates ellipse based on render targets size.
{
	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize(); // Returns size of render target in DPIs.
		const float x = size.width / 2;
		const float y = size.height / 2;
		const float radius = min(x, y);
		ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	}
}

void SynthesizerWindow::DiscardGraphicsResources() // If device is lost.
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}