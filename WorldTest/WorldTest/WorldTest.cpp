#include "stdafx.h"
#include "math.h"
#include "AudioObj.h"
#include "World.h"
#include "Player.h"
#include <iostream>
#include <vector>

int main() {float playerPos1[3] = {1, 1, 1};
	World w = World(playerPos1);
	//World world(playerPos1);
	Player *player = w.getPlayer();

	float playerPos2[3] = {2, 2, 2};
	*player.setLocation(playerPos2);

	//Below is where the issue is. I'm trying to access the same information in
	// different ways. In the above line, I wanted to change the player's location
	// to (2,2,2). So I expect the following output to be (2,2,2). But the output is
	// (1,1,2). This leads me to believe that the above line of code didn't actually 
	// modify the player, but it modified a copy of the player. I don't know how to
	// fix this. I assume I'm doing something wrong with passing a pointer from the
	// getPlayer() method. Help!
	std::cout << "Player coordinates: " << (*w.getPlayer()).getLocation()[0]
		<< ',' << w.getPlayerLocation()[1] << ',' << player.getLocation()[2] << '\n';
/*
	std::cout << "Player coordinates: " << player.getLocation()[0]
		<< ',' << player.getLocation()[1] << ',' << player.getLocation()[2] << '\n';*/
	
	float bear = 90;
	player.setBearing(bear);
	std::cout << "\nPlayer bearing: " << player.getBearing() << '\n';

	float objPos[3] = {2, 1, 1};
	AudioObj obj1 = w.getAudioObj(w.addAudioObj(objPos));

	std::cout << "\nObject 1 coordinates: " << obj1.getLocation()[0] 
		<< ',' << obj1.getLocation()[1] << ',' << obj1.getLocation()[2];

	std::cout << "\n Radius:" << player.getOrientation(&obj1)[0];
	std::cout << "\n Zenith:" << player.getOrientation(&obj1)[1];
	std::cout << "\nAzimuth:" << player.getOrientation(&obj1)[2];
	std::cout << "\n L. Az.:" << player.getLeftAzimuth(&obj1);
	std::cout << "\n R. Az.:" << player.getRightAzimuth(&obj1);

	float objPos2[3] = {0, 0, 1};
	AudioObj obj2 = w.getAudioObj(w.addAudioObj(objPos2));
	std::cout << "\n\nObject 2 coordinates: " << obj2.getLocation()[0]
		<< ',' << obj2.getLocation()[1] << ',' << obj2.getLocation()[2];

	std::cout << "\n Radius:" << player.getOrientation(&obj2)[0];
	std::cout << "\n Zenith:" << player.getOrientation(&obj2)[1];
	std::cout << "\nAzimuth:" << player.getOrientation(&obj2)[2];
	std::cout << "\n L. Az.:" << player.getLeftAzimuth(&obj2);
	std::cout << "\n R. Az.:" << player.getRightAzimuth(&obj2);

	std::cin.ignore();
}