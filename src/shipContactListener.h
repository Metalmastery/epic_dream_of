#pragma once
#include <Box2D/Box2D.h>

class shipContactListener :
	public b2ContactListener
{
public:
	shipContactListener(void);
	~shipContactListener(void);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

