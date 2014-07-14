//
//  WavObject.h
//  Demo
//
//  Created by Philadelphia Game Lab on 7/7/14.
//  Copyright (c) 2014 Philadelphia Game Lab. All rights reserved.
//

#ifndef WAVOBJECT_H
#define WAVOBJECT_H

#include <string>
#include "complex.h"
#include <math.h>
#include <iostream>

class WavObject {
    
    FILE* soundFile;
    struct
    {
        long n;
        int sampleRate;
        int bitDepth;
        int channels;
    }wavFileData;
    long startOfWavData;
    
public:
    
    //Struct that holds RIFF data of Wave File.
    //RIFF data is meta data info that holds ID, size and format of WAVE file.
    struct RIFF_Header {
        char chunkID[4];
        long chuckSize;
        char format[4];
    };
    
    //Struct that holds format subchunk data for WAVE file.
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
    
    //Struct that holds data of WAVE file.
    struct WAVE_Data {
        char subChunkID[4];
        long subChunk2Size;
    };
    
    
    WAVE_Format wave_format;
    RIFF_Header riff_header;
    WAVE_Data wave_data;
    
    short *shortTempData;
    complex *complexTempData;
    
    
    WavObject (unsigned int size,const std::string wavFileName) : shortTempData(new short[size]), complexTempData(new complex[size]) {
        extractWavHeader(wavFileName);
    }
    
    complex *loadCmpWavData(const std::string fname, long *size, int *smpFreq, int *bitDepth, int *channels);
    void extractWavHeader (const std::string fname);
    void loadMoreData (unsigned int, bool);
    
    ~WavObject () {
        delete[] shortTempData;
        delete[] complexTempData;
        if (soundFile)
            fclose(soundFile);
    }
    
};

#endif