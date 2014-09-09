#include "debugDraw.h"


debugDraw::debugDraw(void)
{
}


debugDraw::~debugDraw(void)
{
}

/// Draw a closed polygon provided in CCW order.
void debugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	
	ofSetColor(ofColor(255, 255, 255));
	ofNoFill();
	ofPolyline path;
	for (int i = 0; i < vertexCount; i++) {
		b2Vec2 vec = vertices[i];
		path.addVertex(vec.x, vec.y);
	}
	printf(" \n ");
	path.close();
	path.draw();
}

/// Draw a solid closed polygon provided in CCW order.
void debugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	ofSetColor(ofColor(255, 255, 255));
	ofFill();
	ofPolyline path;
	for (int i = 0; i < vertexCount; i++) {
		path.addVertex(vertices[i].x, vertices[i].y);
	}
	path.close();
	path.draw();
}

/// Draw a circle.
void debugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	ofNoFill();
	ofPoint c;
	c.set(center.x, center.y, 0);

	ofSetColor(ofColor(255, 255, 255));

	ofCircle(c, radius);
}
	
/// Draw a solid circle.
void debugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	ofFill();
	ofPoint c;
	c.set(center.x, center.y, 0);

	ofPoint a;
	a.set(axis.x, axis.y, 0);

	ofSetColor(ofColor(255, 255, 255));

	ofCircle(c, radius);
	//ofLine(c, a);
}
	
/// Draw a line segment.
void debugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	ofSetColor(ofColor(255, 255, 255));
	ofLine(ofPoint(p1.x, p1.y, 0), ofPoint(p2.x, p2.y, 0));
}

void debugDraw::DrawTransform(const b2Transform& xf)
{
	
}