#pragma once

#include "ofMain.h"

class engineParticles
{
public:

	ofVbo vbo;
	int pN;
	int pMax;
	int currentP;
	float minSpeed;
	float maxSpeed;
	int lifetime;

	ofImage img;
	ofShader shader;
	ofColor color;

	vector<ofVec3f> position;  
	vector<ofVec3f> velocity;  

	void setup();
	void emit(ofPoint pos, float angle);
	void emitRelativeVelocity(ofPoint pos, ofPoint v, float angle);
	void update();
	void draw();

	engineParticles(void);
	~engineParticles(void);
};

