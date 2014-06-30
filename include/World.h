#ifndef WORLD_H
#define WORLD_H

#include <stdexcept>
#include <vector>

#include "Location.h"
#include "AudioObj.h"
#include "Player.h"

using namespace std;

template <class T, class N>
class World {

	Player<T, N> player;
	vector<AudioObj<T, N> *> objList;
	int numObj;
	float threshold;

  public:
	static const int MAX_OBJ = 20;
	//This default contrustor creates a player at
	// the world's origin, {0,0,0}.
	World() : numObj(0), threshold(0.05) {}

	//This constructor creates a player at the
	// location specified by the parameter.
	World(const Location<T>& loc) : player(loc), numObj(0), threshold(0.05) {}

	//This constructor creates a player at the
	// location specified by the first parameter,
	// and sets the player's bearing specified by
	// the second parameter.
	World(const Location<T>& loc, N bear) : player(loc,bear), numObj(0), threshold(0.05) {}

	//Returns a reference to the player.
	Player<T,N>* getPlayer() const;

	//Returns the array of the player's location.
	Location<T> getPlayerLocation() const;

	//Adds an audio object to the world. Returns the
	// index of the created object. Sets the location
	// of the created object at the world's origin, {0,0,0}.
	int addAudioObj();

	//Adds an audio object to the world. Returns the
	// index of the created object. Sets the location
	// of the created object at the location specified 
	// by the parameter.
	int addAudioObj(const Location<T>& loc);

	//Returns a reference to the audio object at the
	// specified index.
	AudioObj<T,N> * getAudioObj(int index) const;
};

template <class T, class N>
Player<T,N>* World<T,N>::getPlayer() const{
    return &this->player;
}

template <class T, class N>
Location<T> World<T,N>::getPlayerLocation() const{
    return this->player.getLocation();
}

template <class T, class N>
int World<T,N>::addAudioObj(){
	objList.push_back(new AudioObj<T,N>());
	numObj++;
	return numObj-1;
}

template <class T, class N>
int World<T,N>::addAudioObj(const Location<T>& loc) {
    objList.push_back(new AudioObj<T,N>(loc));
	numObj++;
	return numObj-1;
}

template <class T, class N>
AudioObj<T,N> *World<T,N>::getAudioObj(int index) const{
    return objList.at(index);
}

#endif