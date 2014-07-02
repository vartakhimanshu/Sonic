#ifndef MIXER3D_H
#define MIXER3D_H

#include "complex.h"
//#include "AudioObj.h"

#include "World.h"
#include "mit_hrtf_lib.h"

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

	void convolution(complex *input, complex *filter, complex *output, long nSIG, long NFIL, long &NFFT);
	void stereoConvolution(complex *input, complex *leftFilter, complex *rightFilter, complex *leftOutput, complex *rightOutput, long nSIG, long NFIL, long &NFFT);
	void mixDown();
	void convoluionAll(); 
	complex *getLeftFilter();
	short *getTemp()
	{
		return cbResultLeft;
	}

private:
    World* myWorld;
	complex **input,**inputTemp, **outputLeft,**outputRight,*result, *clFil, *crFil;
	AudioObj **AOList;
	short *lFil, *rFil, *cbResult,*cbResultLeft,*cbResultRight;

	long bufferSize, sampleRate, bitDepth,nTaps,*begin,*end;//nTaps represents the size of the filter data, *begin and *end are the arrays which store the beginning and ending point of the data which is read in every time. 
	int nObj;
	void reassignWorld(World* w);
};

#endif