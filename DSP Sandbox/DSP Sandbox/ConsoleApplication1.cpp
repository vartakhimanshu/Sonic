// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include <algorithm>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>

#include "../../include/Mixer3D.h"
#include "../../include/World.h"
#include "../../include/fft.h"
#include "../../include/wav.h"
#include "../../include/mit_hrtf_lib.h"
#include <iostream>
#include <fstream>

#include <string>

using namespace std;

struct wavFileData
{
	long n;
	int sampleRate;
	int bitDepth;
	int channels;
};

template <typename T>
void write(std::ofstream& stream, const T& t)
{
	stream.write((const char*)&t, sizeof(T));
}

template <typename SampleType>
void writeWAVData(const char* outFile, SampleType* buf, size_t bufSize, int sampleRate, short channels)
{
	std::ofstream stream(outFile, std::ios::binary);                // Open file stream at "outFile" location

	//header
	stream.write("RIFF", 4);                                        // sGroupID (RIFF = Resource Interchange File Format)
	write<int>(stream, 36 + bufSize);                               // dwFileLength
	stream.write("WAVE", 4);                                        // sRiffType

	// Format Chunk 
	stream.write("fmt ", 4);                                        // sGroupID (fmt = format)
	write<int>(stream, 16);                                         // Chunk size (of Format Chunk)
	write<short>(stream, 1);                                        // Format (1 = PCM)
	write<short>(stream, channels);                                 // Channels
	write<int>(stream, sampleRate);                                 // Sample Rate
	write<int>(stream, sampleRate * channels * sizeof(SampleType)); // Byterate
	write<short>(stream, channels * sizeof(SampleType));            // Frame size aka Block align
	write<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample

	// Data Chunk
	stream.write("data", 4);                                        // sGroupID (data)
	stream.write((const char*)&bufSize, 4);                         // Chunk size (of Data, and thus of bufferSize)
	stream.write((const char*)buf, bufSize);                        // The samples DATA!!!
}

int main(int argc, const char * argv[])
{
	const int size = 1889474;
	float *left=new float[size];
	float *right=new float[size];

	int i = 0;
	ifstream file;
	file.open("360stereo.txt");
	
	if (!file){
		cout << "Error: unable to open file." << endl;
	}
	else{
		while (i<size){
			
			file >> left[i];
			file >> right[i];
			//cout << op << endl;
			i++;
			
		}
	}
		
	file.close();
	string s = "testing.wav";
	
	short *result = new short[2 * size];

	for (int i = 0; i < size; i++)
	{
		result[2 * i] = (int)(pow(2,15)*right[i]);
		result[2 * i + 1] = (int)(pow(2, 15)*left[i]);

	}
	
	
	cout << result[10000];
	writeWAVData(s.c_str(), result, 2*size, 44100, 2);
	
	return 0;
}

