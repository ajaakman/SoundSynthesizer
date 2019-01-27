#include "AudioSynthesizer.h"

#include <iostream>
#include <mutex>

namespace audio
{
	std::condition_variable m_cvBlockIsAvailable; // Pauses thread and unpauses it from another thread. Can only be used with mutex.
	std::thread synthesizerThread; // The audio will be playing in the background on a new thread.

	AudioSynthesizer::AudioSynthesizer()// Class takes audio function as parameter. Sine wave playing at 440Hz is played by default.
	{
		InitSynthesizer();
		synthesizerThread = std::thread(&AudioSynthesizer::PlayAudio, this); // Starting our audio synthesis loop on a new thread. Passing audioFunction() as parameter.	
	}

	AudioSynthesizer::~AudioSynthesizer()
	{
		m_bIsAlive = false; // Stopping the PlayAudio() loop when the destructor is called.
		synthesizerThread.join(); // Wait on the main thread until the PlayAudio() thread finishes closing down the audioDevice.
	}

	void CALLBACK AudioSynthesizer::WaveOutProcInst(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2) // Callback instance function unique to each object. Must be DWORD_PTR for 64 bit to work.
	{
		if (uMsg != WOM_DONE) return; // WOM_DONE is sent when the device driver is finished with a data block sent using the waveOutWrite function.

		++m_nBlocksReady; // This signals our loop that the audio device is ready to receive another block.
		m_cvBlockIsAvailable.notify_all(); // Notifies all threads waiting on this condition.
	}

	void CALLBACK AudioSynthesizer::WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) // The WaveOutProc function is the callback function used with the waveform-audio output device. Gets called on a separate thread by the API.
	{
		((AudioSynthesizer*)dwInstance)->WaveOutProcInst(hwo, uMsg, dwParam1, dwParam2); // Local instance callback function is created.
	}

	void AudioSynthesizer::PlayAudio() // The looping function that fills and sends our audio data to the audio device.
	{
		int nCurrentBlock = 0; // Tracks the currently handled block in the PlayAudio() function.
		
		std::mutex mutex; // Creating a mutex object to give us the ability to pause this thread later.
		std::unique_lock<std::mutex> lock(mutex); // Unique lock object manages a mutex object. 		

		while (m_bIsAlive == true) // Loop that keeps the audio playing until destructor is called.
		{
			if (m_nBlocksReady == 0) // If no blocks are left to fill, pause until the callback function gives us one to fill.			
					m_cvBlockIsAvailable.wait(lock);			

			for (int i = 0; i < s_nBlockSize; ++i) // Loop through all the samples in the block and fill the audio buffer with data.
			{
				m_arrAudioBuffer[(nCurrentBlock * s_nBlockSize) + i] = (BIT_DEPTH)(ClampAudio(WaveformFunction()) * pow(2, (m_iBUFFER_TYPE_SIZE * 8) - 1)); // Iterating through each sample in the nCurrentBlock = (Volume multiplier to protect us) * (Our audio function * time) * (Scaling our function from (-1 to 1) to correct Bit Depth). WaveformFunction() gets inherited from the AudioWavefrom class.
				m_dSampleTime = m_dSampleTime + (1.0 / s_nSampleFrequency); // Incrementing our dbSampleTime by time step.
			}

			waveOutPrepareHeader(audioDevice, &waveBlockHeader[nCurrentBlock], sizeof(WAVEHDR)); // The waveOutPrepareHeader function prepares a waveform-audio data block for playback.
			waveOutWrite(audioDevice, &waveBlockHeader[nCurrentBlock], sizeof(WAVEHDR)); // The waveOutWrite function sends a data block to the given waveform-audio output device.

			--m_nBlocksReady; // Releasing the block we just processed. APi will signal us when a new block is ready to be processed.			
			++nCurrentBlock %= s_nBlockCount;
		}

		waveOutReset(audioDevice); // Before calling waveOutClose, the application must wait for all buffers to finish playing or call the waveOutReset function to terminate playback.
		waveOutClose(audioDevice); // The close operation fails if the device is still playing a waveform-audio buffer that was previously sent by calling waveOutWrite.
	}

	double AudioSynthesizer::ClampAudio(const double& dAudio)
	{		
		if (dAudio > 1.0)
			return  1.0;
		else if (dAudio < -1.0)
			return -1.0;
		else
			return dAudio;
	}

	void AudioSynthesizer::InitSynthesizer() // Sets up our audio format, links the buffer memory with the audio device and opens a new device using the supplied format.
	{
		for (int i = 0; i < s_nBlockCount; ++i) // Each waveBlockHeader needs to be linked with our buffer.
		{
			waveBlockHeader[i].lpData = (LPSTR)(s_nBlockSize * i + m_arrAudioBuffer.get()); // Pointer to the waveform buffer. Memory offset + pointer to our memory.
			waveBlockHeader[i].dwBufferLength = s_nBlockSize * m_iBUFFER_TYPE_SIZE; // Length, in bytes, of the buffer.
		}

		tWAVEFORMATEX tWaveFormatEx; // The WAVEFORMATEX structure defines the format of waveform-audio data. Filling it out and passing it to the waveOutOpen() function.
		tWaveFormatEx.wFormatTag = WAVE_FORMAT_PCM; // Format type .
		tWaveFormatEx.nSamplesPerSec = s_nSampleFrequency; // Sample rate, in samples per second.
		tWaveFormatEx.wBitsPerSample = 8 * m_iBUFFER_TYPE_SIZE; // Specifies the number of bits per sample for the format type specified by wFormatTag. If wFormatTag = WAVE_FORMAT_PCM, then wBitsPerSample should be set to either 8 or 16.
		tWaveFormatEx.nChannels = 1; // Specifies the number of channels of audio data.
		tWaveFormatEx.nBlockAlign = tWaveFormatEx.wBitsPerSample / 8 * tWaveFormatEx.nChannels; // Specifies the block alignment in bytes. The block alignment is the size of the minimum atomic unit of data for the wFormatTag format type.
		tWaveFormatEx.nAvgBytesPerSec = tWaveFormatEx.nBlockAlign * tWaveFormatEx.nSamplesPerSec; // Specifies the required average data transfer rate in bytes per second. This value is useful for estimating buffer size.
		tWaveFormatEx.cbSize = 0; // Specifies the size, in bytes, of extra format information appended to the end of the WAVEFORMATEX structure. 

		waveOutOpen(&audioDevice, 0, &tWaveFormatEx, (DWORD_PTR)WaveOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION); // The waveOutOpen function opens the given waveform-audio output device for playback. Using the first audio device the OS finds in this instance.
	}	
}
