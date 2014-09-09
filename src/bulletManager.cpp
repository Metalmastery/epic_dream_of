#include "bulletManager.h"
#include <Box2D\Box2D.h>
#include "coreUtils.h"

bulletManager::bulletManager(void)
{
	this->setup();
}

bulletManager::~bulletManager(void)
{
}

void bulletManager::setup()
{
	this->bulletSpeed = 20;
	this->bulletSpeedVector = ofVec2f(1, 0) * this->bulletSpeed;
	this->bulletLifetime = 1;
}

void bulletManager::update(float delta)
{
	for (deque<Bullet>::iterator i = bullets.begin(); i != bullets.end();) {
		(*i).lifetime -= delta;
		if ((*i).lifetime < 0) {
			printf("bullet removed");
			getB2DWorld()->DestroyBody((*i).body);
			i = bullets.erase(i); 
		} else {
			++i;
		}
	}
}

void bulletManager::fire(const test_ship& shooter)
{
	float32 shooterAngle = shooter.rotation;
	ofVec2f shooterPosition = shooter.position + ofVec2f(2,0).rotate(shooterAngle);
	ofVec2f bulletDirection = ofVec2f(this->bulletSpeedVector).rotate(shooterAngle);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(shooterPosition.x, shooterPosition.y);
	bodyDef.linearVelocity.Set(bulletDirection.x, bulletDirection.y);
	bodyDef.bullet = true;
	
	//bodyDef.userData = &shooter;
 
	b2Body* body = getB2DWorld()->CreateBody(&bodyDef);

	Bullet b;
	b.body = body;
	b.lifetime = bulletLifetime;

	bullets.push_back(b);
	
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(this->size.x / 2, this->size.y / 2);

	b2CircleShape circle;
	circle.m_radius = 0.1;
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;

	fixtureDef.density = 5.0f;
	
	body->CreateFixture(&fixtureDef);
	body->ResetMassData();
}