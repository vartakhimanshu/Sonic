
#ifndef PLAYER_H
#define PLAYER_H

#include <stdexcept>
#include <math.h>

#include "AudioObj.h"
#include "location.h"

using namespace std;

//math.h works in radians; we want degrees. Multiply a radian
// value by this number (180/pi) to calculate the degree value.
#define R2D 57.2957795131

template <class T, class V>
class Player {
    
    Location<T> location;
    Velocity<V> velocity;
    float bearing;
    
public:
    
	//Creates a player at the world's origin, {0,0,0}, and
	// facing forward, at a bearing of 90.
    Player () : bearing(90) {}
    
	//Creates a player at the location specified by the
	// parameter, and facing forward, at a bearing of 90.
    Player (const Location<T>& loc, const Velocity<V>& vel, V bear) : location(loc), velocity(vel), bearing(bear) {}

	//Returns the array of the player's location.
	Location<T> getLocation() const;
	
	//Changes the player's location to that which
	// is specifies in the parameter.
	void setLocation(const Location<T>& loc);
	void setLocation(T x, T y, T z);

    Velocity<V> getVelocity() const;
	
	void setVelocity(const Velocity<V>& vel);
	void setVelocity(V dx, V dy, V dz);

	//Returns thr player's bearing in degrees
	float getBearing() const;

	//Changes the player's bearing in degrees
	void setBearing(float bear);

	//Returns the radius between the player and the
	// object specified in the parameter. The radius is
	// the distance between the player and the object.
	V getRadius(AudioObj<T,V>* obj) const;

	//Returns the zenith angle between the player and the
	// object specified in the parameter. The zenith angle is
	// the angle between the xz plane and the line between the
	// player and the object. It is the elevation angle.
	// 90 indicates the object is directly above the player.
	// -90 indicates the object is directly below the player.
	// 0 indicates the object is exactly in plane with the player.
	// DOES NOT WORK WITH HEAD TRACKING
	V getZenith(AudioObj<T,V> * obj) const;

	//Returns the azimuth angle between the player and the
	// object specified in the parameter. The azimuth angle is
	// the angle between the positive x axis and the line between 
	// the player and the object's projection onto the xz plane.
	// 0 indicates the object is directly to the player's right.
	// 90 indicates the object is directly in front of the player.
	// 180 indicates the object is directly to the player's left.
	// 270 indicates the object is directly behind the player.
	// DOES NOT WORK WITH HEAD TRACKING
	V getAzimuth(AudioObj<T,V> * obj) const;

	////Returns an array containing the radius, zenith angle, and
	//// azimuth angle in the order.
	//// DOES NOT WORK WITH HEAD TRACKING
	//V *getOrientation(AudioObj<T,V> * obj) const;

	//Returns a float between 0 and 1 that describes how loud
	// the object is in relation to the player. This is 
	// calculated using the inverse square law. Math.
	V getRelativeVolume(AudioObj<T,V> * obj) const;
};

template <class T, class V>
Location<T> Player<T,V>::getLocation() const {
    return this->location;
}

template <class T, class V>
void Player<T,V>::setLocation (const Location<T>& loc) {
    this->location = loc;
}

template <class T, class V>
void Player<T,V>::setLocation (T x, T y, T z) {
    this->location = Location<T>(x,y,z);
}

template <class T, class V>
Velocity<V> Player<T,V>::getVelocity() const {
    return this->velocity;
}

template <class T, class V>
void Player<T,V>::setVelocity (const Velocity<V>& vel) {
    this->velocity = vel;
}

template <class T, class V>
void Player<T,V>::setVelocity (V dx, V dy, V dz) {
    this->velocity = Velocity<V>(dx,dy,dz);
}

template <class T, class V>
float Player<T,V>::getBearing() const {
    return this->bearing;
}

template <class T, class V>
void Player<T,V>::setBearing(float bear) {
    this->bearing = bear;
}

template <class T, class V>
V Player<T,V>::getRadius(AudioObj<T,V>* obj) const {
    return sqrt(pow(obj->getLocation().getX() - location.getX(),2)
                + pow(obj->getLocation().getY() - location.getY(),2)
                + pow(obj->getLocation().getZ() - location.getZ(),2));
}

template <class T, class V>
V Player<T,V>::getZenith(AudioObj<T,V> *obj) const{
    if (this->getRadius(obj) == 0)
		return 0;
	else
		return (asin((obj->getLocation().getY() - location.getY()) / getRadius(obj)) * R2D);
}

template <class T, class V>
V Player<T,V>::getAzimuth(AudioObj<T,V> * obj) const {
    V dx = obj->getLocation().getX() - location.getX();
	V dz = obj->getLocation().getZ() - location.getZ();
	V angle;
	if (dx == 0) {
		if (dz > 0)
			angle = 90;
		else if (dz < 0)
			angle = 270;
		else
			angle = 0;
	} else if (dz == 0) {
		if (dx < 0)
			angle = 180;
		else
			angle = 0;
	} else {
		angle = (float)(atan(dz/dx) * R2D);
		if (dx < 0)
			angle = 180 + angle;
		else if (dz < 0 && dx > 0)
			angle = 360 + angle;
	}
	return fmod(angle - this->bearing + 450,360);
}

//template <class T, class V>
//V *Player<T,V>::getOrientation(AudioObj<T,V> * obj) const;

template <class T, class V>
V Player<T,V>::getRelativeVolume(AudioObj<T,V> * obj) const{
    return obj->getVolume() * (1.0 / pow(this->getRadius(obj), 2)) ;
}

#endif