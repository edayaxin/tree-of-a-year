//
//  Particle.hpp
//  ParticleSystem
//
//  Created by Yaxin  on 11/27/16.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Vec.h"

class yxParticle {
public:
    yxParticle();
    virtual ~yxParticle(){};
    
    void initParticle(float x, float y);
    
    void setup();
    void update();
    void draw();
    
    void changeColor(vec4 newColor);
    void applyForce(float x, float y);
    void shiftTo(float x, float y);
    void bounce(bool x, bool y);
    void seek(float x, float y);
    bool isDead();
    
    
    vec2 location;
    vec2 velocity;
    vec2 acceleration;
    vec2 forces;
    
    float speedMax = 20.0f;
    float forceMax = 0.05f;
    
    float lifetime;
    float mass = 2.0;
    ofColor color;
    
};
#endif /* Particle_hpp */
