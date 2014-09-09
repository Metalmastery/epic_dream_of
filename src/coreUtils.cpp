#include "coreUtils.h"

b2World* getB2DWorld()
{
	static b2World * world = new b2World(b2Vec2(0.0f, 0.0f));

	return world;
}

bulletManager* getBulletManager()
{
	static bulletManager * bm = new bulletManager();	
	return bm;
}