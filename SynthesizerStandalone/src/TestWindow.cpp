#include "TestWindow.h"

#include "SynthesizerWindow.h"

TestWindow::TestWindow()
{
	gui::SynthesizerWindow window;

	window.Create(L"Audio Synthesizer by Artur Jaakman. Use Q2W3ER... Keys to Play!", WS_OVERLAPPEDWINDOW); // Create window with name "Synthesizer" and style Overlapped.
		

	ShowWindow(window.Window(), 1);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) // Run the message loop.
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


TestWindow::~TestWindow()
{
}
