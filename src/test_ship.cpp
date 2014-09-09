#include "test_ship.h"
#include <stdio.h>

test_ship::test_ship(float32 x, float32 y, b2World* world)
{
	printf("create ship \n");
	this->isAlive = true;

	this->position.set(x, y);
	this->size.set(0.3f, 0.3f);
	this->rotation = 0.0f;
	this->impulse= 0.01f;
	this->maxSpeed = 0.5f;
	
	this->movementTarget.set(this->position);
	this->movementTargetTolerance.set(0.01f, 0.01f);
	this->hasMovementTarget = false;
	this->engine = engineParticles();

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
	vertices[0].Set(1.0f, 0.0f);
	vertices[1].Set(-1.0f, 0.7f);
	vertices[2].Set(-1.0f, -0.7f);
	int32 count = 3;
	b2PolygonShape polygon;
	polygon.Set(vertices, count);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygon;

	fixtureDef.density = 1.0f;

	this->body->CreateFixture(&fixtureDef);

	// so complex just to understand how it works 
	this->shape = *(b2PolygonShape*)this->body->GetFixtureList()->GetShape();

	// params set
	parameters.setName("ship");
	parameters.add(drift.set("drift", false));
	parameters.add(parktronic.set("parktronic", false));
	parameters.add(rotationTolerance.set("angle tolerance", 10, 0, 180)); 
	parameters.add(distanceTolerance.set("distance tolerance", 50, 0, 300)); 
	parameters.add(linearImpulse.set("linear impulse", 0.1f, 0.0f, 10.0f));
	parameters.add(rotationImpulse.set("rotation impulse", 0.1f, 0.0f, 10.0f));
	parameters.add(maxLinearSpeed.set("max speed", 4.5f, 0.0f, 10.0f));
	parameters.add(maxRotationSpeed.set("max rotation speed", 1.5f, 0.0f, 90.0f));
	
}

test_ship::~test_ship(void)
{
	printf("remove ship \n");
	if (this->body != NULL) {
		//this->body->GetWorld()->DestroyBody(this->body);
	}
}

void test_ship::draw()
{
	ofPushMatrix();
	engine.draw();
	ofSetHexColor(0xffffff);

	ofTranslate(this->position.x, this->position.y, 0);
	
	ofRotate(this->rotation, 0, 0, 1);

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

	//engine.emit(this->position, this->position);
}

void test_ship::move()
{
	if (this->hasMovementTarget) {

		ofVec2f distance = (this->movementTarget - this->position);

		if (distance.length() > this->movementTargetTolerance.length()) {
			ofVec2f direction = distance.getNormalized() * this->impulse;

			//printf("direction %.5f %.5f \n", direction.x, direction.y);

			//printf("v = %.10f \n", ofVec2f().one().y);
			

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

	float32 imp = linearImpulse.get();
	
	b2Vec2 force (cos(rot) * imp, sin(rot) * imp);
	this->body->ApplyLinearImpulse(force, this->body->GetWorldCenter(), true);

	

	b2Vec2 v = this->body->GetLinearVelocity();
	float32 max = maxLinearSpeed.get();
	if (v.Length() > max) {
		this->body->SetLinearVelocity((max / v.Length()) * v);
	}
	engine.emitRelativeVelocity(this->position, ofPoint(v.x, v.y, 0), this->rotation);
}

void test_ship::rotate()
{
	
	ofVec2f direction = (this->movementTarget - this->position);

	if (drift.get()) {
		b2Vec2 linear = this->body->GetLinearVelocity();

		//direction -= ofVec2f(linear.x, linear.y).normalized() * linear.Length() / maxLinearSpeed;	

		float k = ofClamp(1 - direction.length() / distanceTolerance.get(), 0, 1);

		if (parktronic.get()){
			k += ofClamp(linear.Length() / maxLinearSpeed, 0.0, 1.0);
		}

		printf("k %.3f \n", k);

		direction.normalize();

		direction -= ofVec2f(linear.x, linear.y).normalized() * k;	

	}

	ofVec2f currentRotation = ofVec2f(1, 0).rotate(this->rotation);

	float32 a = currentRotation.angle(direction);

	float32 c0 = 0.01f / PI;

	float32 c1 = 1.0f * sqrtf(c0);

	float32 force = a * c0 - this->body->GetAngularVelocity() * c1; 

	//printf("rotation k %.30f \n", force);

	// impulse / inertia = dV

	float32 imp = rotationImpulse.get();

	if (abs(a) > 1.0f) {
		this->body->ApplyAngularImpulse(ofSign(force) * imp, true);
	}

	float32 v = this->body->GetAngularVelocity();
	float32 max = maxRotationSpeed.get();
	if (abs(v) > max) {
		this->body->SetAngularVelocity(ofSign(v) * max);
	}

	if (abs(a) < rotationTolerance.get() && this->hasMovementTarget) {
		this->accelerate();
	}

}

void test_ship::setMovementTarget(ofVec2f target, ofVec2f tolerance)
{
	this->hasMovementTarget = true;
	this->movementTarget = target;
}

void test_ship::startContact()
{
	//this->isAlive = false;
}
	
