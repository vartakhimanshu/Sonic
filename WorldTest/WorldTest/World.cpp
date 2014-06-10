#include "stdafx.h"
#include <vector>
#include "AudioObj.h"
#include "World.h"
#include "Player.h"

World::World() {
	player = Player();
	numObj = 0;
	threshold = .05;
}

World::World(float loc[]) {
	player = Player(loc);
	float initLoc[] = {loc[0],loc[1],loc[2]};
	numObj = 0;
	player.setLocation(initLoc);
	threshold = .05;
}

World::World(float loc[], float bear) {
	player = Player(loc);
	float initLoc[] = {loc[0],loc[1],loc[2]};
	numObj = 0;
	player.setLocation(initLoc);
	player.setBearing(bear);
	threshold = .05;
}

Player * World::getPlayer() {
	return &player;
}

float * World::getPlayerLocation() {
	return player.getLocation();
}

int World::addAudioObj() {
	AudioObj obj;
	objList.push_back(new AudioObj());
	numObj++;
	return numObj-1;
}

int World::addAudioObj(float loc[]) {
	AudioObj obj(loc);
	objList.push_back(new AudioObj(loc));
	numObj++;
	return numObj-1;
}

AudioObj * World::getAudioObj(int index) {
	AudioObj *atObj = objList.at(index);
	return atObj;
}

void World::updateActiveObjects() {
	for (int i = 0; i < numObj; i++) {
		if (getPlayer()->getRelativeVolume(getAudioObj(i)) <= threshold)
			getAudioObj(i)->setActive(false);
		else
			getAudioObj(i)->setActive(true);
	}
}