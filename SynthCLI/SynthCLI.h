#pragma once

#include "../SynthesizerStandalone/src/TestWindow.h"

using namespace System;

namespace SynthCLI {
	public ref class CLISynth
	{
	public:
		CLISynth();
		~CLISynth();

		void SetMasterVolume(double const dNewVollume);
	private:
		clr::TestWindow * pCLISynth;
	};
}
