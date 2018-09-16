#include "stdafx.h"

#include "SynthCLI.h"

SynthCLI::CLISynth::CLISynth()
{
	pCLISynth = new clr::TestWindow();
}

SynthCLI::CLISynth::~CLISynth()
{
	delete pCLISynth;
}

void SynthCLI::CLISynth::SetMasterVolume(double const dNewVollume)
{
	pCLISynth->SetMasterVolume(dNewVollume);
}
