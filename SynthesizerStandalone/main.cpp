#include "AudioSynthesizer.h" // Using Win SDK Version 10.0.17134.0
#include <iostream>
#include <memory>

double audioOscillator(double sampleTime) // Pass the function to the AudioSynthesizer class as a parameter to get a new sound.
{
	return sin(480 * 2 * acos(-1) * sampleTime);
}

int main() 
{
	{
		AudioSynthesizer audioSynthesizer;
		AudioSynthesizer audioSynthesizer1(audioOscillator);
		std::cin.get();
	}
	{
		std::cin.get();
		std::unique_ptr<AudioSynthesizer> audioSynthesizer = std::make_unique<AudioSynthesizer>();
		std::unique_ptr<AudioSynthesizer> audioSynthesizer1 = std::make_unique<AudioSynthesizer>(audioOscillator);
		std::cin.get();
	}
	std::cin.get();
}