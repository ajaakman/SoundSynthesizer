#ifndef UNICODE 
#define UNICODE
#endif 

#include "AudioSynthesizer.h" // Using Win SDK Version 10.0.17134.0
#include "SynthesizerWindow.h"

#include <iostream>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	SynthesizerWindow win;

	if (!win.Create(L"Synthesizer", WS_OVERLAPPEDWINDOW)) // Create window with name "Synthesizer" and style Overlapped.
		return 0; // Exit if couldn't create window.

	ShowWindow(win.Window(), nCmdShow);

	audio::AudioSynthesizer audioSynthesizer;
	audioSynthesizer.setWaveAmplitude(1.0);
	audioSynthesizer.setWaveFrequency(440);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) // Run the message loop.
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

