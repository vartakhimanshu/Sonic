#include<iostream>

using namespace std;

#include "fft.h"
#include "complex.h"
#include "AudioObj.h"
#include "World.h"
#include "mit_hrtf_lib.h"

#ifndef MIXER3D_H
#define MIXER3D_H


//Run the Test.cpp for tesing
//Also, remove the convolutionBox before running the Test.cpp

class Mixer3D
{
public:
	Mixer3D(int bufSize, int smpRate, int bitD, World *w);

	void mix(short *ioDataLeft, short *ioDataRight);//doing everything but now just used for every progress.
	int HRTFLoading(int* pAzimuth, int* pElevation, unsigned int samplerate, unsigned int diffused, complex *&leftFilter, complex *&rightFilter);//loading filters according to the azimuth and elevation values
	
	
	template <typename T>
	void write(std::ofstream& stream, const T& t);
	template <typename SampleType>
	void writeWAVData(const char* outFile, SampleType* buf, size_t bufSize, int sampleRate, short channels);

	void convolution(complex *input, complex *filter, complex *output, long nSig, long nFil, long nFFT);
	void stereoConvolution(complex *input, complex *leftFilter, complex *rightFilter, complex *leftOutput, complex *rightOutput, long nSig, long nFil, long nFFT);
	void mixDown();//scaling down the totaly volume according the number of objects
	void overlapConvolution(complex * input, int Azimuth, int elevation);
	void stereoTest();

	complex *getLeftFilter();
	long *getTemp()//used to achieve whatever field
	{
		return cbResult;
	}
	void test()
	{
		for (int i = 0; i < bufferSize; i++)
		{
			inputTemp[0][i] = input[0][begin[0] + i];
		}
		CFFT::Forward(inputTemp[0],  bufferSize);
		CFFT::Inverse(inputTemp[0],  bufferSize);
		cout << endl;
	}

private:
	//It is named 
	World *myWorld;
	
	//clFil stands for complex type left filter, left and right means the left and right channel
	complex **input, **outputLeft, **outputRight, *result, *clFil, *crFil;
	
	complex **inputTemp;//store the data which is being processed currently
	complex	*inputTempTemp;//just define it temporarily to store a small chunk of the input for processing
	
	//overlap stores the data chunk which needs to add up with the next chunk of data
	//to fix the glitch problem
	complex **overlapLeft,**overlapRight;

	AudioObj **AOList;
	short *lFil, *rFil;//left and right filter
	long *cbResult, *cbResultLeft, *cbResultRight, *testOutput;

	//store the output for small bufferSize
	long *cbResultSmall;

	//nTaps represents the size of the filter data, *begin and *end are the arrays 
	//which store the beginning and ending point of the data which is read in every time. 
	long bufferSize, sampleRate, bitDepth,nTaps,*begin,*end,dataSize;
	
	int nObj;
	void reassignWorld(World* w);
};

#endif