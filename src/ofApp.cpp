#include "ofApp.h"
#include <stdio.h>

#include "coreUtils.h"


//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
	ofBackground(0);

	ofEnableAlphaBlending();
	ofDisableArbTex();

	world = getB2DWorld();

	engine = engineParticles();

	int amount = 3;
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
	parameters.add(ships[0]->parameters);

	gui.setup(parameters);

	//gui.loadFromFile("settings.xml");

	font.loadFont( OF_TTF_SANS,9,true,true);

	listener = shipContactListener();

	world->SetContactListener((b2ContactListener*)new shipContactListener());

	debugDraw* debug = new debugDraw();

	world->SetDebugDraw(debug);
	
	debug->SetFlags(b2Draw::e_shapeBit);
	

}

//--------------------------------------------------------------
void ofApp::update(){
	
		world->Step(0.016f, 6, 2);
		//world->ClearForces();
		getBulletManager()->update(0.016f);

		for(int i = 0; i < ships.size(); i++){
			if (!ships[i]->isAlive){
				delete ships[i];
				ships.erase(ships.begin() + i);
			} else {
				ships[i]->update();
			}
		}

		//for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
		//{
		//	b2Vec2 pos = b->GetPosition();
		//	engine.emit(ofVec3f(pos.x, pos.y, 0), 0);
		//}
		//engine.emit(ship->position, ship->position);
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		ofScale(scale.x, scale.y, scale.z);

		world->DrawDebugData();

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
	if (button == 0){
		return;
	}
	getBulletManager()->fire(*ships[0]);
}
/////////-p02123w
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button != 0){
		return;
	}
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
