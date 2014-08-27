#pragma once

#include "ofMain.h"
#include <Box2D/Box2D.h>

class test_ship
{
public:

	ofVec2f position;
	float32 impulse;
	float32 maxSpeed;
	float32 rotation;

	ofVec2f movementTarget;
	ofVec2f movementTargetTolerance;
	bool hasMovementTarget;

	ofVec2f size;

	b2Body* body;
	b2PolygonShape shape;

	void draw();
	void update();
	void rotate();
	void accelerate();
	void move();

	void setMovementTarget(ofVec2f target, ofVec2f tolerance = ofVec2f(1,1));

	test_ship(float32 x, float32 y, b2World* world);
	~test_ship(void);
};

