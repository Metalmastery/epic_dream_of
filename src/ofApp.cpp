#include "ofApp.h"
#include <stdio.h>

//--------------------------------------------------------------
void ofApp::setup(){
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 0.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	// //Define the ground body.
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, 150.0f);

	// //Call the body factory which allocates memory for the ground body
	// //from a pool and creates the ground box shape (also from a pool).
	// //The body is also added to the world.
	//b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// //Define the ground box shape.
	//b2PolygonShape groundBox;

	// //The extents are the half-widths of the box.
	//groundBox.SetAsBox(50.0f, 10.0f);
	//
	// //Add the ground fixture to the ground body.
	//groundBody->CreateFixture(&groundBox, 0.0f);

	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 0.0f);
	////bodyDef.linearVelocity.Set(0.5f, 0.0f);

	//boxOne = world->CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(10.0f, 10.0f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;

	//fixtureDef.density = 1.0f;

	//fixtureDef.friction = 0.3f;

	//boxOne->CreateFixture(&fixtureDef);

	//b2BodyDef bodyDef2;
	//bodyDef2.type = b2_dynamicBody;
	//bodyDef2.position.Set(300.0f, 119.0f);

	//boxTwo = world->CreateBody(&bodyDef2);

	//b2PolygonShape dynamicBox2;
	//dynamicBox2.SetAsBox(10.0f, 10.0f);

	//b2FixtureDef fixtureDef2;
	//fixtureDef2.shape = &dynamicBox2;

	//fixtureDef2.density = 1.0f;

	//fixtureDef2.friction = 0.3f;

	//boxTwo->CreateFixture(&fixtureDef2);

	ship = new test_ship(0.0f, 0.0f, world);

	ships.push_back(ship);

	//ships.push_back(new test_ship(0.0f, 0.0f, world));

	printf("vec size %i", ships.size());
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	
	scale = ofVec3f(10.0f, 10.0f, 1.0f);

}

//--------------------------------------------------------------
void ofApp::update(){
	
		world->Step(0.016f, 6, 2);
		//world->ClearForces();
		for(int i = 0; i < ships.size(); i++){
			ships[i]->update();
		}
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		ofScale(scale.x, scale.y, scale.z);

		for(int i = 0; i < ships.size(); i++){
			ships[i]->draw();
		}
	ofPopMatrix();
	
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
