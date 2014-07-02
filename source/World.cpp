#include "../include/World.h"

Player* World::getPlayer() {
    return &(this->player);
}

Location World::getPlayerLocation() const{
    return this->player.getLocation();
}

int World::addAudioObj(){
	objList.push_back(new AudioObj());
	numObj++;
	return numObj-1;
}

int World::addAudioObj(const Location& loc, const Velocity& vel) {
    objList.push_back(new AudioObj(loc,vel));
	numObj++;
	return numObj-1;
}

AudioObj* World::getAudioObj (int index) const{
    return objList.at(index);
}
