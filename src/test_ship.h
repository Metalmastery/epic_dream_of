#pragma once

#include "ofMain.h"
#include <Box2D/Box2D.h>

#include "engineParticles.h"


class test_ship
{
public:

	bool isAlive;

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
	engineParticles engine;

	// gui staff
	ofParameterGroup parameters;
	ofParameter<float> linearImpulse;
	ofParameter<float> rotationImpulse;
	ofParameter<float> maxLinearSpeed;
	ofParameter<float> maxRotationSpeed;
	ofParameter<bool> drift;
	ofParameter<bool> parktronic;
	ofParameter<int> rotationTolerance;
	ofParameter<int> distanceTolerance;
	// gui staff

	void draw();
	void update();
	void rotate();
	void accelerate();
	void move();
	void startContact();

	void setMovementTarget(ofVec2f target, ofVec2f tolerance = ofVec2f(1,1));

	test_ship(float32 x, float32 y, b2World* world);
	~test_ship(void);
};

