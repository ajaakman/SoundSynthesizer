#ifndef UNICODE 
#define UNICODE
#endif 

#define ENABLE_CONSOLE 1

#include "SynthesizerWindow.h" // Using Win SDK Version 10.0.17134.0

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
#if ENABLE_CONSOLE
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
#endif

	gui::SynthesizerWindow window;

	if (!window.Create(L"Audio Synthesizer by Artur Jaakman. Use Q2W3ER... Keys to Play!", WS_OVERLAPPEDWINDOW)) // Create window with name "Synthesizer" and style Overlapped.
		return 0; // Exit if couldn't create window.

	ShowWindow(window.Window(), nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) // Run the message loop.
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

