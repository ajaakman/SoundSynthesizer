#pragma once

#pragma comment(lib, "winmm.lib") // Linking winmm library to get access to the waveOut API.

#include <Windows.h> // Using this to get audio devices. Includes waveOut API.

#include <atomic> // Protects the data that can be accessed by multiple threads at the same time.
#include <memory>

#include "AudioWaveform.h"

#define SAMPLE_RATE 44100
#define BLOCK_SIZE 512
#define BLOCK_COUNT 8

#define BIT_DEPTH_8 char
#define BIT_DEPTH_16 short
#define BIT_DEPTH_32 int

#define BIT_DEPTH BIT_DEPTH_16

namespace audio 
{
	class AudioSynthesizer : public AudioWaveform // Inheriting the audio functions that will allow us to change the generated sound wave at runtime.
	{
	public:

		AudioSynthesizer(); // Class takes audio function as parameter. Sine wave playing at 440Hz is played by default.

		~AudioSynthesizer();

	private:

		void CALLBACK WaveOutProcInst(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2); // Callback instance function unique to each object.

		static void CALLBACK WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2); // The WaveOutProc function is the callback function used with the waveform-audio output device. Gets called on a separate thread by the API.

		void PlayAudio(); // The looping function that fills and sends our audio data to the audio device.	

		void InitSynthesizer() ; // Sets up our audio format, links the buffer memory with the audio device and opens a new device using the supplied format.
		
		double ClampAudio(const double& dAudio);

	private:

		static const int s_nSampleFrequency = SAMPLE_RATE; // Used with dbSampleTime to determine the frequency of sampling our audio function.
		static const int s_nBlockSize = BLOCK_SIZE; // size of blocks in the m_arrAudioBuffer.
		static const int s_nBlockCount = BLOCK_COUNT; // number of blocks in the m_arrAudioBuffer.

		std::atomic<int> m_nBlocksReady = s_nBlockCount; // The number of blocks that need to be filled with audio data in the PlayAudio() function. Decrements when we fill it. Increments when the API signals us that a new block is ready to use through the WaveOutProc() callback function. Atomic since the callback thread can access it.

		std::atomic<bool> m_bIsAlive = true; // This will stop our infinate loop when the object is destroyed.
		// Using a unique_ptr ensures that the memory is released when the object is destoryed.
		std::unique_ptr<BIT_DEPTH[]> m_arrAudioBuffer = std::make_unique<BIT_DEPTH[]>(s_nBlockCount * s_nBlockSize); // Setting type to short which is 2 bytes will give us (2 * 8 = 16) bit audio, int for 32 bit audio. Can also do char for 8 bit... DON'T.
		const int m_iBUFFER_TYPE_SIZE = sizeof(m_arrAudioBuffer[0]); // This needs to match the type size of the m_arrAudioBuffer[] array forthe right Bit Depth.

		double m_dSampleTime = 0.0; // Based on sample frequency. When filling a block this is used with our supplied audio function.
				
		HWAVEOUT audioDevice; // Passed into the waveOutOpen() function to set our audio device.
		WAVEHDR waveBlockHeader[s_nBlockCount]; // The WAVEHDR structure defines the header used to identify a waveform-audio buffer.

		inline const double& GetSampleTime() const override { return m_dSampleTime; }
	};
}