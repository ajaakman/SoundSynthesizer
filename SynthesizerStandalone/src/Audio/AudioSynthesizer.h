#pragma once

#pragma comment(lib, "winmm.lib") // Linking winmm library to get access to the waveOut API.

#include <Windows.h> // Using this to get audio devices. Includes waveOut API.

#include <atomic> // Protects the data that can be accessed by multiple threads at the same time.
#include <mutex>
#include <memory>

#include "AudioWaveform.h"

namespace audio 
{
	class AudioSynthesizer : public AudioWaveform // Inheriting the audio functions that will allow us to change the generated sound wave at runtime.
	{
	public:

		AudioSynthesizer(); // Class takes audio function as parameter. Sine wave playing at 440Hz is played by default.

		~AudioSynthesizer();

	private:

		void CALLBACK waveOutProcInst(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2); // Callback instance function unique to each object.

		static void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2); // The waveOutProc function is the callback function used with the waveform-audio output device. Gets called on a separate thread by the API.

		void playAudio(); // The looping function that fills and sends our audio data to the audio device.	

		void setupAudioSynthesizer(); // Sets up our audio format, links the buffer memory with the audio device and opens a new device using the supplied format.

	private:

		const double m_dbVOLUME_MULTIPLIER = 0.1f; // Set volume multiplier to low value so you don't blow out your speakers.
		static const int s_iSAMPLE_FREQUENCY = 44100; // Used with dbSampleTime to determine the frequency of sampling our audio function.
		static const int s_iBLOCK_SIZE = 512; // size of blocks in the m_arrAudioBuffer.
		static const int s_iBLOCK_COUNT = 8; // number of blocks in the m_arrAudioBuffer.

		std::atomic<int> m_iBlocksReady = s_iBLOCK_COUNT; // The number of blocks that need to be filled with audio data in the playAudio() function. Decrements when we fill it. Increments when the API signals us that a new block is ready to use through the waveOutProc() callback function. Atomic since the callback thread can access it.

		std::atomic<bool> m_bIsAlive = true; // This will stop our infinate loop when the object is destroyed.
		// Using a unique_ptr ensures that the memory is released when the object is destoryed.
		std::unique_ptr<short[]> m_arrAudioBuffer = std::make_unique<short[]>(s_iBLOCK_COUNT * s_iBLOCK_SIZE); // Setting type to short which is 2 bytes will give us (2 * 8 = 16) bit audio, int for 32 bit audio. Can also do char for 8 bit... DON'T.
		const int m_iBUFFER_TYPE_SIZE = sizeof(m_arrAudioBuffer[0]); // This needs to match the type size of the m_arrAudioBuffer[] array forthe right Bit Depth.

		std::condition_variable m_cvBlockIsAvailable; // Pauses thread and unpauses it from another thread. Can only be used with mutex.	

		std::thread synthesizerThread; // The audio will be playing in the background on a new thread.

		HWAVEOUT audioDevice; // Passed into the waveOutOpen() function to set our audio device.
		WAVEHDR waveBlockHeader[s_iBLOCK_COUNT]; // The WAVEHDR structure defines the header used to identify a waveform-audio buffer.

	};
}