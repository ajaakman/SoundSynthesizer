#include "AudioSynthesizer.h" // Using Win SDK Version 10.0.17134.0
#include "AudioWaveform.h"

#include <iostream>

int main() 
{		
		AudioSynthesizer audioSynthesizer;
		std::cin.get();	
		audioSynthesizer.setWaveFrequency(880);
		std::cin.get();
}