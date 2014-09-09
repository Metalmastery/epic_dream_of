#include "shipContactListener.h"
#include "test_ship.h"

shipContactListener::shipContactListener(void)
{
}

shipContactListener::~shipContactListener(void)
{
}

void shipContactListener::BeginContact(b2Contact* contact)
{
	b2Body* body = contact->GetFixtureA()->GetBody();

    void* bodyUserData = body->GetUserData();
    if ( bodyUserData ) {
		static_cast<test_ship*>( bodyUserData )->startContact();
	}

	body = contact->GetFixtureB()->GetBody();
    bodyUserData = body->GetUserData();
    if ( bodyUserData ) {
        static_cast<test_ship*>( bodyUserData )->startContact();
	} 
}
	
void shipContactListener::EndContact(b2Contact* contact)
{
	//void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      //if ( bodyUserData )
        //static_cast<test_ship*>( bodyUserData )->endContact();
  
      //check if fixture B was a ball
      //bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      //if ( bodyUserData )
        //static_cast<test_ship*>( bodyUserData )->endContact();
}
