//
//  yxBeetle.hpp
//  Eda2016FYP
//
//  Created by Yaxin  on 18/05/2017.
//
//

#ifndef yxBeetle_hpp
#define yxBeetle_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Vec.h"

class yxBeetle {
public:
    yxBeetle();
    virtual ~yxBeetle(){};
    
    void initBeetle(vec2 imgLoc, float velScale, int imgDir, vec2 imgSize);
    void setup();
    void update();
    void draw();
    void wallBack();
    bool checkCollision(yxBeetle b);
    void rotateCW90();
    
    ofImage beetle;
    int direction;
    int changeTime;
    float velocity;
    vec2 size;
    vec2 location;
};

#endif /* yxBeetle_hpp */
