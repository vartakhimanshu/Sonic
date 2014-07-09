#ifndef WORLD_H
#define WORLD_H

#include <stdexcept>
#include <vector>
#include <pthread.h>
#include <unistd.h>

#include "location.h"
#include "velocity.h"
#include "AudioObj.h"
#include "Player.h"

using namespace std;

class World {

	Player player;
    vector<AudioObj *> objList;
	int numObj;
	float threshold;
    pthread_t writeThread;
    bool isWriteThreadCreated;
    
    static void *writeAudioObjects (void *);

  public:
	static const int MAX_OBJ = 20;
	//This default contrustor creates a player at
	// the world's origin, {0,0,0}.
    World() : numObj(0), threshold(0.05), isWriteThreadCreated(false) {}

	//This constructor creates a player at the
	// location specified by the first parameter,
	// and sets the player's bearing specified by
	// the second parameter.
	World(const Location& loc, const Velocity& vel, float bear) : player(loc,vel,bear), numObj(0), threshold(0.05), isWriteThreadCreated(false) {}

	//Returns a reference to the player.
	Player* getPlayer() ;

	//Returns the array of the player's location.
	Location getPlayerLocation() const;

	//Adds an audio object to the world. Returns the
	// index of the created object. Sets the location
	// of the created object at the world's origin, {0,0,0}.
    int addAudioObj(const std::string);

	//Adds an audio object to the world. Returns the
	// index of the created object. Sets the location
	// of the created object at the location specified 
	// by the parameter.
    int addAudioObj(const Location& loc, const Velocity& vel, const std::string);

	//Returns a reference to the audio object at the
	// specified index.
	AudioObj* getAudioObj(int index) const;
    
    void createWriteThread (void) {
        if (!isWriteThreadCreated){
            pthread_create(&writeThread, nullptr, writeAudioObjects, &objList);
            isWriteThreadCreated = true;
        }
    };
};


#endif