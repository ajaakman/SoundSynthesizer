#pragma comment(lib, "winmm.lib") // Linking winmm library to get access to the waveOut API.

#include <Windows.h> // Using this to get audio devices. Includes waveOut API.

#include <iostream>
#include <atomic> // Protects the data that can be accessed by multiple threads at the same time.
#include <mutex>

const float volumeMultiplier = 0.1f; // Set volume multiplier to low value so you don't blow out your speakers.
const int sampleRate = 44100; // Used with sampleTime to determine the frequency of sampling our audio function.
const int blockCount = 16; // number of blocks in the audioBuffer.
const int blockSize = 512; // size of blocks in the audioBuffer.

short audioBuffer[blockCount * blockSize]; // Setting type to short which is 2 bytes will give us (2 * 8 = 16) bit audio, int for 32 bit audio. Can also do char for 8 bit... DON'T.
const int bufferTypeSize = sizeof(audioBuffer[0]); // This needs to match the type size of the audioBuffer[] array forthe right Bit Depth.

std::condition_variable blockIsAvailable; // Pauses thread and unpauses it from another thread. Can only be used with mutex.
std::atomic<int> blocksReady = blockCount; // The number of blocks that need to be filled with audio data in the PlayAudio() function. Decrements when we fill it. Increments when the API signals us that a new block is ready to use through the WaveOutProc() callback function. Atomic since the callback thread can access it.

HWAVEOUT audioDevice; // Passed into the waveOutOpen() function to set our audio device.
WAVEHDR waveBlockHeader[blockCount]; // The WAVEHDR structure defines the header used to identify a waveform-audio buffer.	

class AudioSynthesizer
{
public:	

	AudioSynthesizer()
	{
		setupAudioSynthesizer();

		std::thread synthesizerThread(&AudioSynthesizer::playAudio); // Starting our audio synthesis loop on a new thread.
		synthesizerThread.detach(); // Detaching the thread will keep it running in teh background until the application is closed.		
	}	

private:

	static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) // The waveOutProc function is the callback function used with the waveform-audio output device. Gets called on a separate thread by the API.
	{
		if (uMsg != WOM_DONE) return; // WOM_DONE is sent when the device driver is finished with a data block sent using the waveOutWrite function.

		blockIsAvailable.notify_all(); // Notifies all threads waiting on this condition.
		++blocksReady; // This signals our loop that the audio device is ready to receive another block.
	}

	static void playAudio() // The looping function that fills and sends our audio data to the audio device.
	{
		int currentBlock = 0; // Tracks the currently handled block in the playAudio() function.
		double sampleTime = 0.0; // Based on sample frequency. When filling a block this is used with our supplied audio function.

		std::mutex mutex; // Creating a mutex object to give us the ability to pause this thread later.
		std::unique_lock<std::mutex> lock(mutex); // Unique lock object manages a mutex object. 

		while (true) // Infinate loop to keep the audio playing.
		{
			if (blocksReady == 0) // If no blocks are left to fill, pause until the callback function gives us one to fill.
				blockIsAvailable.wait(lock);

			for (int i = 0; i < blockSize; ++i) // Loop through all the samples in the block and fill the audio buffer with data.
			{
				audioBuffer[(currentBlock * blockSize) + i] = volumeMultiplier * (sin(440 * 2 * acos(-1) * sampleTime)) * pow(2, (bufferTypeSize * 8) - 1); // Iterating through each sample in the currentBlock = (Volume multiplier to protect us) * (Our audio function * time) * (Scaling our function from (-1 to 1) to correct Bit Depth)
				sampleTime += (1.0 / sampleRate); // Incrementing our sampleTime by time step.
			}

			waveOutPrepareHeader(audioDevice, &waveBlockHeader[currentBlock], sizeof(WAVEHDR)); // The waveOutPrepareHeader function prepares a waveform-audio data block for playback.
			waveOutWrite(audioDevice, &waveBlockHeader[currentBlock], sizeof(WAVEHDR)); // The waveOutWrite function sends a data block to the given waveform-audio output device.

			--blocksReady; // Releasing the block we just processed. APi will signal us when a new block is ready to be processed.			
			++currentBlock %= blockCount;
		}
	}

	static void setupAudioSynthesizer() // Sets up our audio format, links the buffer memory with the audio device and opens a new device using the supplied format.
	{
		for (int i = 0; i < blockCount; ++i) // Each waveBlockHeader needs to be linked with our buffer.
		{
			waveBlockHeader[i].lpData = (LPSTR)(blockSize * i + audioBuffer); // Pointer to the waveform buffer. Pointer to our audioBuffer + the offset.
			waveBlockHeader[i].dwBufferLength = blockSize * bufferTypeSize; // Length, in bytes, of the buffer.
		}

		tWAVEFORMATEX tWaveFormatEx; // The WAVEFORMATEX structure defines the format of waveform-audio data. Filling it out and passing it to the waveOutOpen() function.
		tWaveFormatEx.wFormatTag = WAVE_FORMAT_PCM; // Format type .
		tWaveFormatEx.nSamplesPerSec = sampleRate; // Sample rate, in samples per second.
		tWaveFormatEx.wBitsPerSample = 8 * bufferTypeSize; // Specifies the number of bits per sample for the format type specified by wFormatTag. If wFormatTag = WAVE_FORMAT_PCM, then wBitsPerSample should be set to either 8 or 16.
		tWaveFormatEx.nChannels = 1; // Specifies the number of channels of audio data.
		tWaveFormatEx.nBlockAlign = tWaveFormatEx.wBitsPerSample / 8 * tWaveFormatEx.nChannels; // Specifies the block alignment in bytes. The block alignment is the size of the minimum atomic unit of data for the wFormatTag format type.
		tWaveFormatEx.nAvgBytesPerSec = tWaveFormatEx.nBlockAlign * tWaveFormatEx.nSamplesPerSec; // Specifies the required average data transfer rate in bytes per second. This value is useful for estimating buffer size.
		tWaveFormatEx.cbSize = 0; // Specifies the size, in bytes, of extra format information appended to the end of the WAVEFORMATEX structure. 

		waveOutOpen(&audioDevice, 0, &tWaveFormatEx, (DWORD_PTR)waveOutProc, (DWORD_PTR)nullptr, CALLBACK_FUNCTION); // The waveOutOpen function opens the given waveform-audio output device for playback. Using the first audio device the OS finds in this instance.
	}
};

int main() 
{
	AudioSynthesizer audioSynthesizer;
	std::cin.get();
}