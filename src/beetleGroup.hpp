//
//  beetleGroup.hpp
//  Eda2016FYP
//
//  Created by Yaxin  on 19/05/2017.
//
//

#ifndef beetleGroup_hpp
#define beetleGroup_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Vec.h"
#include "yxBeetle.hpp"

class beetleGroup
{
public:
    beetleGroup();
        virtual ~beetleGroup(){};
    
    void setup();
    void update();
    void draw();
    
    void randomInit();

    int bNum = 30;
    float sizeX = 35;
    float sizeY = 35;
    vector <yxBeetle> bGroup;
    
};
#endif /* beetleGroup_hpp */
