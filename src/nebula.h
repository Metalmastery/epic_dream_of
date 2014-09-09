#pragma once
#include "ofMain.h"

class nebula
{
public:
	ofFbo frame;
	ofImage img;
	ofTexture tex;

	int w;
	int h;

	void generate();

	nebula(void);
	~nebula(void);
};

