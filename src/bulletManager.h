#pragma once

//#include "gameObject.h"
#include "test_ship.h"
#include "ofMain.h"

struct Bullet 
{
	b2Body* body;
	float lifetime;
};

class bulletManager
{
public:
	bulletManager(void);
	~bulletManager(void);
	
	float bulletSpeed;
	float bulletLifetime;

	ofVec2f bulletSpeedVector;

	deque <Bullet> bullets;

	void setup();
	void update(float delta);
	void fire(const test_ship& shooter);
};

