#pragma once

#include <WindowsX.h>

template <class DERIVED_TYPE>
class BaseWindow // The BaseWindow class is an abstract base class, from which specific window classes are derived. For example, here is the declaration of a simple class derived from BaseWindow.
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // Defines the behavour of the window.
	{
		DERIVED_TYPE *pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam); // Default action.
		}
	}

	BaseWindow() : m_hwnd(NULL) { }

	BOOL Create(
		PCWSTR lpWindowName, // Window text. Used for title bar in this instance.
		DWORD dwStyle, // Window style. Set of flags that define look and feel of window. In this case standard window.
		DWORD dwExStyle = 0, // Optional window styles. 0 for Default. Other for i.e. for transparency.
		int x = CW_USEDEFAULT, // Size and position. Using default values here.
		int y = CW_USEDEFAULT, // Size and position. Using default values here.
		int nWidth = CW_USEDEFAULT, // Size and position. Using default values here.
		int nHeight = CW_USEDEFAULT, // Size and position. Using default values here.
		HWND hWndParent = 0, // Parent window. Null if top-level window. Set parent window name here.
		HMENU hMenu = 0 // Menu. Null in this instance.
	)
	{
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = DERIVED_TYPE::WindowProc; // Pointer to an application defined WindowProc Function.
		wc.hInstance = GetModuleHandle(NULL); // Handle of the application instance. Parameter of wWinMain.
		wc.lpszClassName = ClassName(); // String that identifies class name. Needs to be unique within the process.

		RegisterClass(&wc); // Passing in the wc structure to the RegisterClass() windows function.

		m_hwnd = CreateWindowEx( // Create the window. Handle that uniquely identifies the window. Sends a few messages such as WM_NCCREATE and WM_CREATE.
			dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
		);

		return (m_hwnd ? TRUE : FALSE); // If window creation fails exit application.
	}

	HWND Window() const { return m_hwnd; }

protected:

	virtual PCWSTR  ClassName() const = 0; // Register the window class. // Window class. Defines the type of windos we're creating.
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
};

