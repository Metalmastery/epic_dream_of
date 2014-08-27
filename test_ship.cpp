#include "test_ship.h"
#include <stdio.h>


test_ship::test_ship(float32 x, float32 y, b2World* world)
{
	this->position.set(x, y);
	this->size.set(0.3f, 0.3f);
	this->rotation = 0.0f;
	this->impulse= 0.01f;
	this->maxSpeed = 0.5f;
	this->movementTarget.set(this->position);
	this->movementTargetTolerance.set(0.01f, 0.01f);
	this->hasMovementTarget = false;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(this->position.x, this->position.y);
	//bodyDef.linearDamping = 0.0f;
	//bodyDef.angularDamping = 0.5f;
	bodyDef.userData = this;
 
	this->body = world->CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(this->size.x / 2, this->size.y / 2);

	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, 0.0f);
	vertices[1].Set(-2.0f, 0.7f);
	vertices[2].Set(-2.0f, -0.7f);
	int32 count = 3;
	b2PolygonShape polygon;
	polygon.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygon;

	fixtureDef.density = 1.0f;

	this->body->CreateFixture(&fixtureDef);

	// so complex just to understand how it works 
	this->shape = *(b2PolygonShape*)this->body->GetFixtureList()->GetShape();
	
}

test_ship::~test_ship(void)
{
	this->body->GetWorld()->DestroyBody(this->body);
}

void test_ship::draw()
{
	
	ofPushMatrix();

	ofTranslate(this->position.x, this->position.y, 0);
	ofRotate(this->rotation, 0, 0, 1);

	// TODO: test with rotation
	//ofTranslate(-this->shape.m_centroid.x, -this->shape.m_centroid.y);

	ofPoint vertices[3];

	for (int i = 0; i < this->shape.GetVertexCount(); i++){
		b2Vec2 b = this->shape.GetVertex(i);
		vertices[i].set(b.x, b.y);
	}

	ofTriangle(vertices[0], vertices[1], vertices[2]);

	ofPopMatrix();
}

void test_ship::update()
{
	//this->move();

	this->rotate();

	b2Vec2 pos = this->body->GetPosition();

	this->position.set(pos.x, pos.y);
	this->rotation = ofRadToDeg(this->body->GetAngle());
	
}

void test_ship::move()
{
	if (this->hasMovementTarget) {

		ofVec2f distance = (this->movementTarget - this->position);

		if (distance.length() > this->movementTargetTolerance.length()) {
			ofVec2f direction = distance.getNormalized() * this->impulse;

			//printf("direction %.5f %.5f \n", direction.x, direction.y);

			printf("v = %.10f \n", ofVec2f().one().y);
			

			b2Vec2 force (direction.x, direction.y);
			this->body->ApplyLinearImpulse(force, this->body->GetWorldCenter(), true);

			if (this->body->GetLinearVelocity().Length() > this->maxSpeed) {
				this->body->SetLinearDamping(1.0f);
			} else {
				this->body->SetLinearDamping(0.0f);
			}

		} else {
			this->hasMovementTarget = false;
		}
	}
}

void test_ship::accelerate()
{
	float32 rot = this->body->GetAngle();
	
	b2Vec2 force (cos(rot) * 0.0005f, sin(rot) * 0.0005f);
	this->body->ApplyLinearImpulse(force, this->body->GetWorldCenter(), true);

	b2Vec2 v = this->body->GetLinearVelocity();
	float32 max = 0.6;
	if (v.Length() > max) {
		this->body->SetLinearVelocity((max / v.Length()) * v);
	}

}

void test_ship::rotate()
{
	
	ofVec2f direction = (this->movementTarget - this->position);

	ofVec2f currentRotation = ofVec2f(1, 0).rotate(this->rotation);

	float32 a = currentRotation.angle(direction);

	float32 c0 = 0.001f / PI;

	float32 c1 = 1.5f * sqrtf(c0);

	float32 force = a * c0 - this->body->GetAngularVelocity() * c1; 

	printf("angle %.30f \n", this->body->GetAngularVelocity());

	// impulse / inertia = dV

	if (abs(a) > 1.0f) {
		this->body->ApplyAngularImpulse(ofSign(force) * 0.001, true);
	}

	if (a < 10.0f && this->hasMovementTarget) {
		this->accelerate();
	}

}

void test_ship::setMovementTarget(ofVec2f target, ofVec2f tolerance)
{
	this->hasMovementTarget = true;
	this->movementTarget = target;
}
	
