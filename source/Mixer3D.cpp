#include <algorithm>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

#include "../include/Mixer3D.h"
#include "../include/World.h"
#include "../include/fft.h"
#include "../include/wav.h"
#include "../include/mit_hrtf_lib.h"
using namespace std;


struct wavFileData
{
	long n;
	int sampleRate;
	int bitDepth;
	int channels;
};


Mixer3D::Mixer3D(int bufSize, int smpRate, int bitD, World *w):Azimuth(-60), myWorld(w), bufferSize(bufSize), sampleRate(smpRate), bitDepth(bitD)
{
	
	//dataSize = 65536;
	
	//this is just used for testing
	nObj = 1;
	//this is just used for testing

	//input = new complex*[World::MAX_OBJ];
	//inputTemp = new complex*[World::MAX_OBJ];
	outputLeft = new complex*[World::MAX_OBJ];
	outputRight = new complex*[World::MAX_OBJ];
	overlapLeft = new complex*[World::MAX_OBJ];
	overlapRight = new complex*[World::MAX_OBJ];
	
	//This is the variable used to store the data gotten from the world
	inputTempTemp1 = new complex[2*bufferSize];

	for (int i = 0; i < World::MAX_OBJ; i++)
	{
		overlapLeft[i] = new complex[bufferSize];
		overlapRight[i] = new complex[bufferSize];
		//input[i] = new complex[dataSize*16];
		//inputTemp[i] = new complex[dataSize*16];
		outputLeft[i] = new complex[2*bufferSize];
		outputRight[i] = new complex[2*bufferSize];
	}

	//This is for testing
	overlapInput = new complex[2 * bufferSize];
	
	//cbResult = new long[2*dataSize*16];
	
	//Used to store the small chunk of output for every iteration
	//cbResultSmall = new long[2 * bufferSize];
	
	//These are for filter fetch
	lFil = new short[2 * bufferSize];
	rFil = new short[2 * bufferSize];

	//These are for storing filters for processing
	clFil = new complex[2 * bufferSize];
	crFil = new complex[2 * bufferSize];
    
    clFilPast = new complex[bufferSize];//This is used to store the filter data from the last iteration
    
    azimuthFlag=0;//0 means the azimuth value is positive
    filterFlag=0;//0 means the filters of two consecutive filters are the same
    
}

int Mixer3D::HRTFLoading(int* pAzimuth, int* pElevation, unsigned int samplerate, unsigned int diffused, complex *&leftFilter, complex *&rightFilter)
{
	int size = mit_hrtf_get(pAzimuth, pElevation, samplerate, diffused, lFil, rFil);


	for (int i = 0; i < size; i++)
	{
		leftFilter[i] = (double)(lFil[i]);
		rightFilter[i] = (double)(rFil[i]);
	}
    
    //Perform FFT and store in 2*bufferSize
    
	return size;
}

template <typename T>
void Mixer3D::write(std::ofstream& stream, const T& t)
{
	stream.write((const char*)&t, sizeof(T));
}

template <typename SampleType>
void Mixer3D::writeWAVData(const char* outFile, SampleType* buf, size_t bufSize, int sampleRate, short channels)
{
	std::ofstream stream(outFile, std::ios::binary);                // Open file stream at "outFile" location

	/* Header */
	stream.write("RIFF", 4);                                        // sGroupID (RIFF = Resource Interchange File Format)
	write<int>(stream, 36 + bufSize);                               // dwFileLength
	stream.write("WAVE", 4);                                        // sRiffType

	/* Format Chunk */
	stream.write("fmt ", 4);                                        // sGroupID (fmt = format)
	write<int>(stream, 16);                                         // Chunk size (of Format Chunk)
	write<short>(stream, 1);                                        // Format (1 = PCM)
	write<short>(stream, channels);                                 // Channels
	write<int>(stream, sampleRate);                                 // Sample Rate
	write<int>(stream, sampleRate * channels * sizeof(SampleType)); // Byterate
	write<short>(stream, channels * sizeof(SampleType));            // Frame size aka Block align
	write<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample

	/* Data Chunk */
	stream.write("data", 4);                                        // sGroupID (data)
	stream.write((const char*)&bufSize, 4);                         // Chunk size (of Data, and thus of dataSize)
	stream.write((const char*)buf, bufSize);                        // The samples DATA!!!
}
complex *Mixer3D::getLeftFilter()
{
	return clFil;

}
void Mixer3D::convolution(complex *input, complex *filter,complex *output, long nSig, long nFil, long nFFT)
{
	//Check for invalid inputs.
	if (input == NULL || filter == NULL)
	{
		cout << "Could not perform convolution on empty arrays!" << endl;
		return;
	}

	bool NFFTChanged = false;
	//If NFFT not a power of 2, or it is smaller than signal or filter, prompt for new.
	
	while (log2(nFFT) / log2(2) != (int)(log2(nFFT) / log2(2)) || nFFT < nSig || nFFT < nFil)
	{
		cout << "Please input a valid NFFT, which is >= nSig(" << nSig << ") and >= NFIL(" << nFil << ") : ";
		cin >> nFFT;
		NFFTChanged = true;
	}

	
	complex *fInput=input, *fFilter=filter;
	
	//Perform FFT on both input and filter.
    
	CFFT::Forward(fInput, nFFT);
    CFFT::Forward(fFilter, nFFT);

	for (int i = 0; i < nFFT; i++)
		output[i] = fInput[i] * fFilter[i];
	
	CFFT::Inverse(output, nFFT);
	CFFT::Inverse(fInput, nFFT);
	CFFT::Inverse(fFilter, nFFT);
}

void Mixer3D::stereoConvolution(complex *input, complex *leftFilter, complex *rightFilter, complex *leftOutput, complex *rightOutput, long nSIG, long nFIL, long nFFT)
{
	convolution(input, leftFilter, leftOutput, nSIG, nFIL, nFFT);
	convolution(input, rightFilter, rightOutput, nSIG, nFIL, nFFT);
}


void Mixer3D::overlapConvolution(int elevation, short *ioDataLeft,short *ioDataRight)
{
    //std::cout << "Entered overlapConvoltuion" << endl;
    azimuthFlag = 0;
    filterFlag = 0;
	
    if (Azimuth < 0)
        azimuthFlag = 1;
    else
        azimuthFlag = 0;
    
    myWorld->getAudioObj(0)->fillAudioData(inputTempTemp1, bufferSize);

    for (int i = bufferSize; i < 2 * bufferSize; i++)
    {
        inputTempTemp1[i] = 0;
    }
    
    //fetch the filter
    nTaps = HRTFLoading(&Azimuth, &elevation, sampleRate, 1, clFil, crFil);
    
    for(int i = 0; i < nTaps; i++)
    {
        double EPSILON = .001;
        if(clFil[i].norm() - clFilPast[i].norm() > EPSILON)
        {
            filterFlag = 1;
            break;
        }
    }

    if(filterFlag)
    {
        for (int i = nTaps; i < 2 * bufferSize; i++)
        {
            clFil[i] = 0;
            crFil[i] = 0;
        }
    
        if (azimuthFlag)
            Azimuth = -Azimuth;
        
        stereoConvolution(overlapInput, clFil, crFil, outputLeft[0], outputRight[0], bufferSize, nTaps, 2 * bufferSize);
       
        //updating the overlap part for the next iteration
        for (int i = 0; i < bufferSize; i++)
        {
            overlapLeft[0][i] = outputLeft[0][i + bufferSize];
            overlapRight[0][i] = outputRight[0][i + bufferSize];
        }
    }
    
    stereoConvolution(inputTempTemp1, clFil, crFil, outputLeft[0], outputRight[0], bufferSize, nTaps, 2 * bufferSize);
    
    for (int i = 0; i < bufferSize; i++)
    {
       
        ioDataLeft[i] =  (outputLeft[0][i].re())/2 + (overlapLeft[0][i].re()/2);//overlapLeft[0][i].re();//
        ioDataRight[i] = (outputRight[0][i].re())/2 + (overlapRight[0][i].re()/2);//overlapRight[0]
    }
    
    //cout << "filled audio buffer" << endl;
    //updating the overlap part for the next iteration
    for (int i = 0; i < bufferSize; i++)
    {
        overlapInput[i] = inputTempTemp1[i];
    }
    for (int i = bufferSize; i < 2 * bufferSize; i++)
    {
        overlapInput[i] = 0;
    }
    //cout.flush();
    
    //Storing the filter data for the next iteration usage
    for(int i = 0; i < nTaps ; i++)
    {
        clFilPast[i]=clFil[i];
    }
    
    //Storing the overlap data in the case of using the same filter
    for(int i = 0; i < bufferSize ; i++)
    {
        overlapLeft[0][i] = outputLeft[0][i+bufferSize];
        overlapRight[0][i] = outputLeft[0][i+bufferSize];
    }
}


template void Mixer3D::write< short >(std::ofstream& stream, const short& t);
template void Mixer3D::write< int >(std::ofstream& stream, const int& t);
template void Mixer3D::writeWAVData<short>(const char* outFile, short* buf, size_t bufSize, int sampleRate, short channels);