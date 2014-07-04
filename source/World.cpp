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

void * World::writeAudioObjects (void* obj) {
    cout<<"in thread write audio objects" <<endl;
    vector<AudioObj *> *objListCurrent = static_cast<vector<AudioObj *>*>(obj);
    while (1){
        usleep(10000);
        if (objListCurrent->size() != 0) {
            (*objListCurrent)[0]->writeCircBuff();
        }
    }
    return NULL;
}
