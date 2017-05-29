//
//  yxBeetle.cpp
//  Eda2016FYP
//
//  Created by Yaxin  on 18/05/2017.
//
//

#include "yxBeetle.hpp"

yxBeetle::yxBeetle()
{

    initBeetle({300, 300}, 1, 2, {80,80});

}

void yxBeetle::initBeetle(vec2 imgLoc, float velScale, int imgDir, vec2 imgSize)
{
    location = imgLoc;
    velocity = velScale;
    direction = imgDir;
    size = imgSize;
    changeTime = ofGetFrameNum();
}

void yxBeetle::setup()
{
    beetle.load("beetle.png");
    if(direction != 0)
        beetle.rotate90(direction);
}

void yxBeetle::update()
{
    wallBack();
    
    if(direction == 0)
        location.add(0,-velocity);
    else if(direction == 1)
        location.add(velocity,0);
    else if(direction == 2)
        location.add(0,velocity);
    else if(direction == 3)
        location.add(-velocity,0);
}

void yxBeetle::draw()
{
    beetle.draw(location.x, location.y, size.x, size.y);
    //ofDrawBitmapString(ofToString(direction), location.x, location.y);
}

void yxBeetle::wallBack()
{
    if(location.x < 0) // direction = 3
        direction = 1;
    else if (location.x > (ofGetWindowWidth()-size.x)) // direction = 1
        direction = 3;
    else if (location.y < 0) // direction = 0
        direction  = 2;
    else if (location.y > (ofGetWindowHeight()-size.y)) // direction = 2
        direction = 0;
    else
        return;
    //initBeetle(location, velocity, direction, size);
    beetle.rotate90(2);
}

bool yxBeetle::checkCollision(yxBeetle b){
    if(fabsf(location.x - b.location.x) < 40.0 && fabsf(location.y - b.location.y) < 40.0)
    {
        if(ofGetFrameNum() - changeTime > 5)
        {
            rotateCW90();
            return true;
        }
    }
    return false;
}

void yxBeetle::rotateCW90()
{

    if(direction < 3)
        direction = direction +1;
    else
        direction = 0;
    beetle.rotate90(1);
    changeTime = ofGetFrameNum();
    //cout << "change time " << changeTime << endl;
}
