#include <stdlib.h>
//#include <Box2D/Box2D.h>

PBox2D box2d;

void setup() {
    box2d = new PBox2D(this);
    Initializes a Box2D world with default settings
    box2d.createWorld();
    box2d.setGravity(0, -10);
    
    Vec2 gravity = new Vec2(0, -10);
    Vec2 mouseWorld = box2d.coordPixelsToWorld(mouseX,mouseY);
    
    Vec2 worldPos = new Vec2(-10,25);
    Vec2 pixelPos = box2d.coordWorldToPixels(worldPos);
    ellipse(pixelPos.x, pixelPos.y,16,16);
    
}


