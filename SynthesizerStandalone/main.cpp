#include <iostream>
#include "AudioSynthesizer.h"

double audioOscillator(double sampleTime) // Pass the function to the AudioSynthesizer class as a parameter to get a new sound.
{
	return sin(480 * 2 * acos(-1) * sampleTime);
}

int main() 
{
	{
		AudioSynthesizer audioSynthesizer(audioOscillator);
		std::cin.get();
	}
	std::cin.get();
	AudioSynthesizer* audioSynthesizer = new AudioSynthesizer(audioOscillator);
	std::cin.get();
	delete audioSynthesizer;
	std::cin.get();
}