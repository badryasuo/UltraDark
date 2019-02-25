#ifndef DARK_AUDIO
#define DARK_AUDIO
#pragma comment(lib,"winmm.lib")
#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>
#define dark_wave_format_pcm				WAVE_FORMAT_PCM
#define dark_wave_format_ieee_float			WAVE_FORMAT_IEEE_FLOAT
#define dark_wave_format_drm				WAVE_FORMAT_DRM
#define dark_wave_format_extensible			WAVE_FORMAT_EXTENSIBLE
#define dark_wave_format_alaw				WAVE_FORMAT_ALAW
#define dark_wave_format_mulaw				WAVE_FORMAT_MULAW
#define dark_wave_format_adpcm				WAVE_FORMAT_ADPCM
#define dark_wave_format_mpeg				WAVE_FORMAT_MPEG
#define dark_wave_format_dolby_ac3_spdif	WAVE_FORMAT_DOLBY_AC3_SPDIF
#define dark_wave_format_wmaspdif			WAVE_FORMAT_WMASPDIF
#else
#define dark_wave_format_pcm				0
#define dark_wave_format_ieee_float			0
#define dark_wave_format_drm				0
#define dark_wave_format_extensible			0
#define dark_wave_format_alaw				0
#define dark_wave_format_mulaw				0
#define dark_wave_format_adpcm				0
#define dark_wave_format_mpeg				0
#define dark_wave_format_dolby_ac3_spdif	0
#define dark_wave_format_wmaspdif			0
#endif
// Pulse Code Modulation
#define DARK_WAVE_PCM				dark_wave_format_pcm
// 32-bit floWAVE audio					 
#define DARK_WAVE_IEEE_FLOAT		dark_wave_format_ieee_float
// Digital RiWAVEManagement				 
#define DARK_WAVE_DRM				dark_wave_format_drm
// ExtensibleWAVE-Format Descriptor		 
#define DARK_WAVE_EXTENSIBLE		dark_wave_format_extensible
#define DARK_WAVE_ALAW				dark_wave_format_alaw
#define DARK_WAVE_MULAW				dark_wave_format_mulaw
#define DARK_WAVE_ADPCM				dark_wave_format_adpcm
#define DARK_WAVE_MPEG				dark_wave_format_mpeg
#define DARK_WAVE_DOLBY_AC3_SPDIF	dark_wave_format_dolby_ac3_spdif
#define DARK_WAVE_WMASPDIF			dark_wave_format_wmaspdif

#include <fstream>
#include <iostream>
#include <sstream>
namespace dark
{
	namespace audio
	{
		class Device
		{
		protected:
		private:
#ifdef _WIN32
			WAVEFORMATEX wfx = {};
			HWAVEIN wi;
#endif
		public:
			// 
			Device(
				unsigned short format, 
				unsigned short channels, 
				unsigned long samples_per_seconds,
				unsigned short bits_per_sample
			)
			{
#ifdef _WIN32
				wfx.wFormatTag = format;
				wfx.nChannels = channels;
				wfx.nSamplesPerSec = samples_per_seconds;
				wfx.wBitsPerSample = bits_per_sample;

				wfx.nBlockAlign = (wfx.wBitsPerSample * wfx.nChannels)/8;
				wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

				waveInOpen(&wi, WAVE_MAPPER, &wfx, NULL, NULL, CALLBACK_NULL | WAVE_FORMAT_DIRECT);
#endif
			}
			unsigned long long record(std::string & SaveTo, bool * recording)
			{
				char buffers[2][44100 * 2 * 2 / 2];
				WAVEHDR headers[2] = { {},{} };           // initialize them to zeros
				for (int i = 0; i < 2; ++i)
				{
					headers[i].lpData = buffers[i];             // give it a pointer to our buffer
					headers[i].dwBufferLength = 44100 * 2 * 2 / 2;      // tell it the size of that buffer in bytes
																		// the other parts of the header we don't really care about for this example, and can be left at zero

																		// Prepare each header
					waveInPrepareHeader(wi, &headers[i], sizeof(headers[i]));

					// And add it to the queue
					//  Once we start recording, queued buffers will get filled with audio data
					waveInAddBuffer(wi, &headers[i], sizeof(headers[i]));
				}
				// Print some simple directions to the user
				std::cout << "Now recording audio.  Press Escape to stop and exit." << std::endl;

				// start recording!
				waveInStart(wi);

				// Now that we are recording, keep polling our buffers to see if they have been filled.
				//   If they have been, dump their contents to the file and re-add them to the queue so they
				//   can get filled again, and again, and again
				int len;
				while (recording)  // keep looping until the user hits escape
				{
					for (auto& h : headers)      // check each header
					{
						if (h.dwFlags & WHDR_DONE)           // is this header done?
						{
							// if yes, dump it to our variable
							len = h.dwBufferLength;
							SaveTo = h.lpData;
							// then re-add it to the queue
							h.dwFlags = 0;          // clear the 'done' flag
							h.dwBytesRecorded = 0;  // tell it no bytes have been recorded

													// re-add it  (I don't know why you need to prepare it again though...)
							waveInPrepareHeader(wi, &h, sizeof(h));
							waveInAddBuffer(wi, &h, sizeof(h));
						}
					}
				}
				return len;
			}
			int saveWAV()
			{

			}
		};
	}
}
#endif