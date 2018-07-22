#include "AudioSynthesizer.h" // Using Win SDK Version 10.0.17134.0

#include <iostream>

int main() 
{		
		AudioSynthesizer audioSynthesizer;
		audioSynthesizer.setWaveAmplitude(1.0);
		audioSynthesizer.setWaveFrequency(440);
		std::cin.get();	
		audioSynthesizer.setWaveAmplitude(0.2);
		audioSynthesizer.setWaveFrequency(880);
		std::cin.get();
}