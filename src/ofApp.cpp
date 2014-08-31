#include "ofApp.h"
#include <stdio.h>

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	ofBackground(0);

	ofEnableAlphaBlending();
	ofDisableArbTex();

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 0.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	ship = new test_ship(0.0f, 0.0f, world);

	engine = engineParticles();

	ships.push_back(ship);

	int amount = 0;
	for(int i = 0; i < amount; i++){
		ships.push_back(new test_ship(ofRandom(100) - 50, ofRandom(100) - 50, world));
	}

	printf("vec size %i", ships.size());
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	
	scale = ofVec3f(10.0f, 10.0f, 1.0f);

	parameters.setName("settings");
	parameters.add((*ship).parameters);

	gui.setup(parameters);

	//gui.loadFromFile("settings.xml");

	font.loadFont( OF_TTF_SANS,9,true,true);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
		world->Step(0.016f, 6, 2);
		//world->ClearForces();

		for(int i = 0; i < ships.size(); i++){
			ships[i]->update();
		}
		//engine.emit(ship->position, ship->position);
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		ofScale(scale.x, scale.y, scale.z);

		ofSetHexColor(0xff0000);
		ofCircle(mousePosition.x, mousePosition.y, 0, 1.0f);
		
		engine.draw();
		for(int i = 0; i < ships.size(); i++){
			ships[i]->draw();
		}
		
	ofPopMatrix();

	gui.draw();
	ofSetHexColor(0xffffff);
	font.drawString("fps: " + ofToString((int)ofGetFrameRate()),ofGetWidth()-150,40);
	//font.drawString("impulse: " + ofToString((float)ship->linearImpulse.get()),ofGetWidth()-150,60);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	engine.emit(ofPoint((x - ofGetWidth() / 2) / scale.x, (y - ofGetHeight() / 2) / scale.y), 90.0);	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
/////////-p02123w
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mousePosition.set((x - ofGetWidth() / 2) / scale.x, (y - ofGetHeight() / 2) / scale.y);
	for(int i = 0; i < ships.size(); i++){
		ships[i]->setMovementTarget(mousePosition);
	}
	engine.emit(mousePosition, 90.0);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
