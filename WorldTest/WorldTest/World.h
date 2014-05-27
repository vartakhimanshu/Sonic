#ifndef WORLD_H
#define WORLD_H

#include "stdafx.h"
#include <vector>
#include "AudioObj.h"
#include "Player.h"

class World {

	Player player;
	std::vector<AudioObj> objList;
	int numObj;

  public:

	//This default contrustor creates a player at
	// the world's origin, {0,0,0}.
	World::World();

	//This constructor creates a player at the
	// location specified by the parameter.
	World::World(float loc[]);

	//Returns a reference to the player.
	Player * getPlayer();

	//Returns the array of the player's location.
	float* getPlayerLocation();

	//Adds an audio object to the world. Returns the
	// index of the created object. Sets the location
	// of the created object at the world's origin, {0,0,0}.
	int addAudioObj();

	//Adds an audio object to the world. Returns the
	// index of the created object. Sets the location
	// of the created object at the location specified 
	// by the parameter.
	int addAudioObj(float loc[]);

	//Returns a reference to the audio object at the
	// specified index.
	AudioObj& getAudioObj(int index);
};

#endif