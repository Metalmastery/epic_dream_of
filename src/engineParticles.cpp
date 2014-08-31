#include "engineParticles.h"


engineParticles::engineParticles(void)
{
	ofSeedRandom();

	this->vbo = ofVbo();
	this->lifetime = 2;
	this->pN = lifetime * 50;
	this->pMax = 5000;
	this->currentP = 0;
	this->minSpeed = 0.1;
	this->maxSpeed = 1;
	this->color = ofColor();
	this->position.resize(pN);
	this->velocity.resize(pN);

	
	color.setHsb(ofRandom(255), 100 + ofRandom(150), 100 + ofRandom(50));
	//color.setSaturation(200);
	//color.setBrightness(200);
	
	//mesh.setMode(OF_PRIMITIVE_POINTS);
	float currentElapsedTime = ofGetElapsedTimef();
	for(int i = 0; i < pN; i++) {
		position.push_back(ofVec3f(0.0, 0.0, currentElapsedTime));
		velocity.push_back(ofVec3f(0.0, 0.0, 0.0));
	}
	vbo.setVertexData(&position[0], pN, GL_STATIC_DRAW);
	vbo.setNormalData(&velocity[0], pN, GL_STATIC_DRAW);

	shader.load("shaders/engine/vert.glsl", "shaders/engine/frag.glsl");
	ofDisableArbTex();
	img.loadImage("img/spark_1.png");
}

engineParticles::~engineParticles(void)
{

}

void engineParticles::setup()
{

}

void engineParticles::emitRelativeVelocity(ofPoint pos, ofPoint v, float angle)
{
	float speed = ofRandom(minSpeed, maxSpeed);
	ofVec3f p = position[currentP];
	p.x = pos.x;
	p.y = pos.y;
	p.z = ofGetElapsedTimef();
	position[currentP] = p;
	
	ofVec3f thrust = ofVec3f(5.0, 0.0, 0.0);
	thrust.rotate(0, 0, angle);
	velocity[currentP] = -thrust + v;
	
	currentP++;
	if (currentP >= pN){
		currentP = 0;
	}	
}

void engineParticles::emit(ofPoint pos, float angle)
{
	this->emitRelativeVelocity(pos, ofPoint(), angle);
	
}
void engineParticles::update()
{

}
void engineParticles::draw()
{

	vbo.setVertexData(&position[0], pN, GL_STATIC_DRAW);
	vbo.setNormalData(&velocity[0], pN, GL_STATIC_DRAW);

	//glPointSize(3);
	//glEnable( GL_POINT_SMOOTH );
	//ofSetHexColor(0x00ff00);

	//glEnable(GL_POINT_SPRITE);

	// this makes everything look glowy :)

	ofSetColor(color);

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnablePointSprites();

	shader.begin();

	//img.getTextureReference().bind();
	img.bind();
	
	shader.setUniform1f("lifetime", lifetime);
	shader.setUniform1f("currentTime", ofGetElapsedTimef());
	
	this->vbo.draw(GL_POINTS, 0, pN);
	img.unbind();
	//img.getTextureReference().unbind();
	
	ofDisableBlendMode();
	ofDisablePointSprites();
	shader.end();

}