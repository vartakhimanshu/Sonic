#ifndef AUDIOOBJ_H
#define AUDIOOBJ_H

class AudioObj {
	
	float location [3];
	int index;
	bool active;

  public:

	//Creates a new audio object at the world's
	// origin, {0,0,0}.
	AudioObj::AudioObj();

	//Creates a new audio object at the location
	// specified by the parameter.
	AudioObj::AudioObj(float loc[]);

	//Returns the array of the object's location.
	float* getLocation();

	//Changes the object's location to that which
	// is specifies in the parameter.
	void setLocation(float loc[]);

	//Returns whether or not the object is active
	bool isActive();

	//Changes whether or not the object is active
	void setActive(bool active);
};

#endif