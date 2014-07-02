#ifndef AUDIOOBJ_H
#define AUDIOOBJ_H

#include <stdexcept>
#include "location.h"
#include "velocity.h"

using namespace std;

class AudioObj {
	
	Location location;
    Velocity velocity;
    bool active;
    float volume;

public:

	//Creates a new audio object at the world's origin, {0,0,0}.
	AudioObj() : active(false), volume(1) {}

	//Creates a new audio object at the location specified by the parameter.
	AudioObj(const Location& loc, const Velocity& vel) : location(loc), velocity(vel), active(false), volume(1) {}
	
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
};

#endif