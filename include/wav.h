#ifndef WAV_H
#define WAV_H

#include <string>
#include "complex.h"
#include <math.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


	namespace utility {

		// Structs for components of a WAVE file
		//typedef struct RIFF_Header;
		//typedef struct WAVE_Format;
		//typedef struct WAVE_Data;

        struct RIFF_Header;
        struct WAVE_Format;
		struct WAVE_Data;

        
		// Load WAVE file function
		complex *loadCmpWavData(const std::string fname, long *size, int *smpFreq, int *bitDepth, int *channels);
	}
#if defined(__cplusplus)
}  /* extern "C" */
#endif

#endif /* AL_S_H */