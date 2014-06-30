#ifndef AUDIOOBJ_H
#define AUDIOOBJ_H

#include <stdexcept>
#include "location.h"
#include "velocity.h"

using namespace std;

template <class T, class V>
class AudioObj {
	
	Location<T> location;
    Velocity<V> velocity;
    bool active;
    float volume;

public:

	//Creates a new audio object at the world's origin, {0,0,0}.
	AudioObj() : active(false), volume(1) {}

	//Creates a new audio object at the location specified by the parameter.
	AudioObj(const Location<T>& loc, const Velocity<V> vel) : location(loc), velocity(vel), active(false), volume(1) {}
	
	//Returns the array of the object's location.
	Location<T> getLocation() const;
    
    //Changes the object's location to that which is specifies in the parameter.
	void setLocation(const Location<T>& loc);
	void setLocation(T x, T y, T z);
    
    Velocity<V> getVelocity() const;
    
    void setVelocity(const Velocity<V>& vel);
    void setVelocity(V dx, V dy, V dz);
    
    //Returns the volume of the audio object.
	//This will be a value from 0 to 1.
	float getVolume() const;
    
    //Sets the volume of the audio object. This will only accept values from 0 to 1.
	void setVolume(float vol);

	//Returns whether or not the object is active
	bool isActive() const;

	//Changes whether or not the object is active
	void setActive(bool active);
};

template <class T, class V>
Location<T> AudioObj<T,V>::getLocation () const {
    return this->location;
}

template <class T, class V>
void AudioObj<T,V>::setLocation(const Location<T>& loc) {
    this->location = loc;
}

template <class T, class V>
void AudioObj<T,V>::setLocation(T x, T y, T z) {
    this->location = Location<T>(x,y,z);
}

template <class T, class V>
Velocity<V> AudioObj<T,V>::getVelocity () const {
    return this->velocity;
}

template <class T, class V>
void AudioObj<T,V>::setVelocity(const Velocity<V>& vel) {
    this->velocity = vel;
}

template <class T, class V>
void AudioObj<T,V>::setVelocity (V dx, V dy, V dz) {
    this->velocity = Velocity<V>(dx, dy, dz);
}

template <class T, class V>
float AudioObj<T,V>::getVolume() const {
    return this->volume;
}

template <class T, class V>
void AudioObj<T,V>::setVolume(float vol) {
    if (vol > 1 || vol < 0){
        throw invalid_argument ("volume out of range(0-1)");
    }
    this->volume = vol;
}

template <class T, class V>
bool AudioObj<T,V>::isActive() const {
    return this->active;
}

template <class T, class V>
void AudioObj<T,V>::setActive(bool active){
    this->active = active;
}

#endif