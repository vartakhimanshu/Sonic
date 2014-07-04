#ifndef AUDIOOBJ_H
#define AUDIOOBJ_H

#include <stdexcept>
#include "location.h"
#include "velocity.h"
#include "wav.h"
#include "complex.h"
#include "CircBuff.h"

using namespace std;

class AudioObj {
	
	Location location;
    Velocity velocity;
    bool active;
    float volume;
    complex* tempBufferWavFile;
    struct
    {
        long n;
        int sampleRate;
        int bitDepth;
        int channels;
    }wavFileData;
    unsigned int currentTrackerPosition;
    
    void loadWavFile (void);
    bool repeat;
    CircBuff<complex> circBuff;
    
public:

	//Creates a new audio object at the world's origin, {0,0,0}.
    AudioObj() : active(false), volume(1), repeat(true), circBuff(8192) {/*tempBufferWavFile = new complex[100000]; if(!tempBufferWavFile) throw bad_alloc ();*/ loadWavFile(); circBuff.write(tempBufferWavFile, 8192); }

	//Creates a new audio object at the location specified by the parameter.
    AudioObj(const Location& loc, const Velocity& vel) : location(loc), velocity(vel), active(false), volume(1), repeat(true), circBuff(8192) {/*tempBufferWavFile = new complex[100000]; if(!tempBufferWavFile) throw bad_alloc ();*/ loadWavFile();  circBuff.write(tempBufferWavFile, 10000);}
    
    ~AudioObj () { delete[] tempBufferWavFile;}
	
	//Returns the array of the object's location.
	Location getLocation() const;
    
    //Changes the object's location to that which is specifies in the parameter.
	void setLocation (const Location& loc);
	void setLocation (VariableForLocation x, VariableForLocation y, VariableForLocation z);
    
    Velocity getVelocity() const;
    
    void setVelocity (const Velocity& vel);
    void setVelocity (VariableForVelocity dx, VariableForVelocity dy, VariableForVelocity dz);
    
    //Returns the volume of the audio object.
	//This will be a value from 0 to 1.
	float getVolume() const;
    
    //Sets the volume of the audio object. This will only accept values from 0 to 1.
	void setVolume(float vol);

	//Returns whether or not the object is active
	bool isActive() const;

	//Changes whether or not the object is active
	void setActive(bool active);
    
    void fillAudioData(complex *, unsigned int);
    
    void writeCircBuff (void);
    
};

#endif