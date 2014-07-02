#include "../include/AudioObj.h"

Location AudioObj::getLocation () const {
    return this->location;
}

void AudioObj::setLocation (const Location& loc) {
    this->location = loc;
}

void AudioObj::setLocation (VariableForLocation x, VariableForLocation y, VariableForLocation z) {
    this->location = Location(x,y,z);
}

Velocity AudioObj::getVelocity () const {
    return this->velocity;
}

void AudioObj::setVelocity (const Velocity& vel) {
    this->velocity = vel;
}

void AudioObj::setVelocity (VariableForVelocity dx, VariableForVelocity dy, VariableForVelocity dz) {
    this->velocity = Velocity(dx,dy,dz);
}

float AudioObj::getVolume() const {
    return this->volume;
}

void AudioObj::setVolume(float vol) {
    if (vol > 1 || vol < 0){
        throw invalid_argument ("volume out of range(0-1)");
    }
    this->volume = vol;
}

bool AudioObj::isActive() const {
    return this->active;
}

void AudioObj::setActive(bool active){
    this->active = active;
}
