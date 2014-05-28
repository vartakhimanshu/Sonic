#include "stdafx.h"
#include "math.h"
#include "AudioObj.h"
#include "World.h"
#include "Player.h"
#include <iostream>
#include <vector>

int main() {
	//Here we create a world which has a player at {1,1,1}. The World class
	// has a constructor that allows us to specify where the player will
	// initially be. We can then reference the Player object using the method
	// getPlayer().
	float playerPos1[3] = {1, 1, 1};
	World world = World(playerPos1);
	Player *player = world.getPlayer();

	//We can change te player's location using the player's setLocation()
	// method. Here we change the player's position to {0,0,0}. I know it
	// seems stupid, but this is just a demonstration, okay?
	float playerPos2[3] = {0, 0, 0};
	player->setLocation(playerPos2);

	//The player's getLocation() method returns an array of three floats that
	// specify its location on the x, y, and z axes.
	std::cout << "Player coordinates: " << player->getLocation()[0]
		<< ',' << player->getLocation()[1] << ',' << player->getLocation()[2] << '\n';
	

	//In addition to a location, the player also has a bearing. The bearing is
	// what direction the player is facing. We'll set the player's bearing to
	// 90. A bearing of 90 means the player is facing forward, or towards the
	// positive z axis. If you payed attention in precalc, you'd already know
	// that.
	float bear = 90;
	player->setBearing(bear);
	std::cout << "\nPlayer bearing: " << player->getBearing() << '\n';

	//Now we can start putting audio objects in the world. To do that, use the
	// world'd addAudioObject() method. In the case of no arguments, the object
	// will be places at {0,0,0}. But in this case, we give the method a set of
	// coordinates at which to place the object. The method returns an int, 
	// which is the index of the audio object. If you want a reference to the
	// audio object, use the world's getAudioObj(int index) method. Below, we do
	// all of this in one line of code. I hope it's not too confusing.
	float objPos[3] = {1, 0, 0};
	AudioObj *obj1 = world.getAudioObj(world.addAudioObj(objPos));

	//Let's print the object's coordinates!
	std::cout << "\nObject 1 coordinates: " << obj1->getLocation()[0] 
		<< ',' << obj1->getLocation()[1] << ',' << obj1->getLocation()[2];

	//Now that we have a player and an audio object, we can calculate information
	// about an object's position in relation to the player. The 
	// getOrientation(AudioObj obj) method will give us three important pieces of
	// information. It will return a float array containing the radius, zenith, and
	// azimuth values. If that made no sense to you, refer to the methods' 
	// documentation in "player.h".  In addition, we can access the object's
	// left and right azimuth values.
	std::cout << "\n Radius:" << player->getOrientation(obj1)[0];
	std::cout << "\n Zenith:" << player->getOrientation(obj1)[1];
	std::cout << "\nAzimuth:" << player->getOrientation(obj1)[2];
	std::cout << "\n L. Az.:" << player->getLeftAzimuth(obj1);
	std::cout << "\n R. Az.:" << player->getRightAzimuth(obj1);

	//Here we do all of that again with a second object.
	float objPos2[3] = {2, 3, 4};
	AudioObj *obj2 = world.getAudioObj(world.addAudioObj(objPos2));
	std::cout << "\n\nObject 2 coordinates: " << obj2->getLocation()[0]
		<< ',' << obj2->getLocation()[1] << ',' << obj2->getLocation()[2];

	std::cout << "\n Radius:" << player->getOrientation(obj2)[0];
	std::cout << "\n Zenith:" << player->getOrientation(obj2)[1];
	std::cout << "\nAzimuth:" << player->getOrientation(obj2)[2];
	std::cout << "\n L. Az.:" << player->getLeftAzimuth(obj2);
	std::cout << "\n R. Az.:" << player->getRightAzimuth(obj2);

	//This makes the program not terminate until a keystroke.
	std::cin.ignore();
}