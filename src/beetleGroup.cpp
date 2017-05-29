//
//  beetleGroup.cpp
//  Eda2016FYP
//
//  Created by Yaxin  on 19/05/2017.
//
//

#include "beetleGroup.hpp"

beetleGroup::beetleGroup(){}

void beetleGroup::setup()
{
    for (int i = 0; i < bNum; i++)
    {
        yxBeetle beetle;
        
        float vel = rand()%30;
        int dir = (int)rand()%4;
        
        float xInit = rand()%(ofGetWindowWidth() - (int)sizeX);
        float yInit = rand()%(ofGetWindowHeight() - (int)sizeY);
        
        beetle.initBeetle({xInit, yInit}, vel, dir, {sizeX, sizeY});
        
        beetle.setup();
        bGroup.push_back(beetle);
    }
}

void beetleGroup::update()
{
    for (int i = 0; i < bNum; i++)
    {
        for (int x = i+1; x < bNum; x++)
        {
            if(bGroup[i].checkCollision(bGroup[x]))
            {
                break;
            }
        }
 
        bGroup[i].update();
    }
}

void beetleGroup::draw()
{
    for (int i = 0; i < bNum; i++)
    {
        bGroup[i].draw();
    }
}

void beetleGroup::randomInit()
{
    
}
