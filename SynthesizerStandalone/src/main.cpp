#ifndef UNICODE 
#define UNICODE
#endif 

#define CONSOLE 1

#include "SynthesizerWindow.h" // Using Win SDK Version 10.0.17134.0

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
#if CONSOLE
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
#endif

	SynthesizerWindow win;

	if (!win.Create(L"Audio Synthesizer", WS_OVERLAPPEDWINDOW)) // Create window with name "Synthesizer" and style Overlapped.
		return 0; // Exit if couldn't create window.

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) // Run the message loop.
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

