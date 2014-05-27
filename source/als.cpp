#include "als.h"
#include <iostream>

namespace utility {
	/*
		Struct that holds RIFF data of Wave File.
		RIFF data is meta data info that holds ID, size,
		and format of WAVE file.
	*/
	struct RIFF_Header {
		char chunkID[4];
		long chuckSize;
		char format[4];
	};

	/*
	Struct that holds format subchunk data for WAVE file.
	*/
	struct WAVE_Format {
		char subChunkID[4];
		long subChunkSize;
		short audioFormat;
		short numChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;
	};

	/*
	Struct that holds data of WAVE file.
	*/
	struct WAVE_Data {
		char subChunkID[4];
		long subChunk2Size;
	};

	/*
	Loads wave file into a buffer
	*/
	bool loadWAVFile(const std::string fname, ALuint* buffer,
		ALsizei* size, ALsizei* frequency, ALenum* format) {

		// Local var declarations
		FILE* soundFile = NULL;
		WAVE_Format wave_format;
		RIFF_Header riff_header;
		WAVE_Data wave_data;
		unsigned char* data;

		try {
			soundFile = fopen(fname.c_str(), "rb");
			if (!soundFile)
				throw(fname);

			// Read in the first chunk into the struct
			fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

			// Read in first chunk to RIFF_Header
			if ((riff_header.chunkID[0] != 'R' ||
				riff_header.chunkID[1] != 'I' ||
				riff_header.chunkID[2] != 'F' ||
				riff_header.chunkID[3] != 'F') ||
				(riff_header.format[0] != 'W' ||
				riff_header.format[1] != 'A' ||
				riff_header.format[2] != 'V' ||
				riff_header.format[3] != 'E'))
				throw ("Invalid RIFF or WAVE Header");

			// Read in second chunk to WAVE_Format
			fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
			// Check for format tag in memory
			if (wave_format.subChunkID[0] != 'f' ||
				wave_format.subChunkID[1] != 'm' ||
				wave_format.subChunkID[2] != 't' ||
				wave_format.subChunkID[3] != ' ')
				throw ("Invalid Wave Format");

			// Check for extra parameters
			if (wave_format.subChunkSize > 16) {
				int extraSize = wave_format.subChunkSize - 16;
				fseek(soundFile, sizeof(char)*extraSize, SEEK_CUR);
			}

			// Read last byte of data before sound data
			fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
			// Check for data tag in memory
			if (wave_data.subChunkID[0] != 'd' ||
				wave_data.subChunkID[1] != 'a' ||
				wave_data.subChunkID[2] != 't' ||
				wave_data.subChunkID[3] != 'a')
				throw ("Invalid data header");
			// Allocate memory for wave data
			data = new unsigned char[wave_data.subChunk2Size];

			// Read in sound data to soundData var
			if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
				throw ("error loading WAVE data into struct");

			// Set variables passed in
			*size = wave_data.subChunk2Size;
			*frequency = wave_format.sampleRate;

			// Set format data - num of channels and bits per sample
			if (wave_format.numChannels == 1) {
				if (wave_format.bitsPerSample == 8)
					*format = AL_FORMAT_MONO8;
				else if (wave_format.bitsPerSample == 16)
					*format = AL_FORMAT_MONO16;
			}
			else if (wave_format.numChannels == 2) {
				if (wave_format.bitsPerSample == 8)
					*format = AL_FORMAT_STEREO8;
				else if (wave_format.bitsPerSample == 16)
					*format = AL_FORMAT_STEREO16;
			}

			// Create OpenAL buffer
			alGenBuffers(1, buffer);
			// Check error
			// Fill OpenAL buffer
			alBufferData(*buffer, *format, (void*)data,
				*size, *frequency);
			// Check error

			// Clean up and return true if successful
			fclose(soundFile);
			return true;
		}
		catch (std::string error) {
			// Caught a bad file name
			std::cerr << error << " : trying to load "
				<< fname << std::endl;
			// Clean up memory if wave loading fails
			if (soundFile != NULL)
				fclose(soundFile);
			return false;
		}
	}
}