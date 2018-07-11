#include "AudioSynthesizer.h" // Using Win SDK Version 10.0.17134.0
#include <iostream>

double audioOscillator(double sampleTime) // Pass the function to the AudioSynthesizer class as a parameter to get a new sound.
{
	return sin(480 * 2 * acos(-1) * sampleTime);
}

int main() 
{
	{
		AudioSynthesizer audioSynthesizer(audioOscillator);
		AudioSynthesizer audioSynthesizer1;
		std::cin.get();
	}
	std::cin.get();
	AudioSynthesizer* audioSynthesizer = new AudioSynthesizer(audioOscillator);
	AudioSynthesizer* audioSynthesizer1 = new AudioSynthesizer;
	std::cin.get();
	delete audioSynthesizer;
	delete audioSynthesizer1;
	std::cin.get();
}