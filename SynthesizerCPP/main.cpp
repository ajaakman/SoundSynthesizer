#ifndef UNICODE 
#define UNICODE
#endif 

#define SINE_WAVE 0
#define SQUARE_WAVE 1
#define SAW_WAVE 2
#define TRIANGLE_WAVE 3
#define ANALOG_SAW 4
#define NOISE 5

#include "TestWindow.h"
#include <iostream>

int main()
{	
	clr::TestWindow window;	
	std::cout << "Hello" << std::endl;
	std::cin.get();
	window.SetMasterVolume(0.1);
	window.SetAttackTime(0.0);
	window.SetDecayTime(0.0);
	window.SetReleaseTime(1.0);
	window.SetStartAmplitude(1.0);
	window.SetSusatainAmplitude(1.0);

	window.SetWaveAmplitude(0.3, 1);
	window.SetWaveAmplitude(0.4, 2);
	window.SetWaveAmplitude(0.5, 3);
	
	window.SetWaveType(SAW_WAVE, 0, 1);
	window.SetWaveType(SQUARE_WAVE, 0, 2);
	window.SetWaveType(TRIANGLE_WAVE, 0, 3);

	window.SetTune(-12, 1);
	window.SetTune(0, 2);
	window.SetTune(12, 3);

	window.SetFineTune(0.0, 1);
	window.SetFineTune(-0.1, 2);
	window.SetFineTune(0.1, 3);

	window.SetTremoloAmplitude(0.003, 1);
	window.SetTremoloFrequency(5.0, 1);
	window.SetTremoloAmplitude(0.003, 2);
	window.SetTremoloFrequency(5.0, 2);
	window.SetTremoloAmplitude(0.003, 3);
	window.SetTremoloFrequency(5.0, 3);

	window.SetVibratoAmplitude(0.003, 1);
	window.SetVibratoFrequency(5.0, 1);
	window.SetVibratoAmplitude(0.003, 2);
	window.SetVibratoFrequency(5.0, 2);
	window.SetVibratoAmplitude(0.003, 3);
	window.SetVibratoFrequency(5.0, 3);

	std::cin.get();
	window.SetMasterVolume(0.1);
	std::cin.get();
	std::cin.get();
	std::cin.get();

	return 0;
}

