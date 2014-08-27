#pragma once

#include "ofMain.h"
#include <Box2D/Box2D.h>

#include "test_ship.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		b2Body* boxOne;
		b2Body* boxTwo;

		test_ship* ship;

		b2World* world;
		ofVec2f mousePosition;

		ofVec3f scale;

		vector<test_ship*> ships;
};
