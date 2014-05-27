#include "stdafx.h"
#include "AudioObj.h"

AudioObj::AudioObj() {
	location[0] = 0;
	location[1] = 0;
	location[2] = 0;
	active = false;
}

AudioObj::AudioObj(float loc[]) {
	location[0] = loc[0];
	location[1] = loc[1];
	location[2] = loc[2];
	active = false;
}

float* AudioObj::getLocation() {
	return location;
}

void AudioObj::setLocation(float loc[]) {
	location[0] = loc[0];
	location[1] = loc[1];
	location[2] = loc[2];
}

bool AudioObj::isActive() {
	return active;
}

void AudioObj::setActive(bool activeBool) {
	if (activeBool)
		active = true;
	else
		active = false;
}