//
//  Particle.cpp
//  ParticleSystem
//
//  Created by Yaxin  on 11/27/16.
//
//

#include "Particle.hpp"
yxParticle::yxParticle(){
    initParticle(0.0f, 0.0f);
}

void yxParticle::initParticle(float x, float y){
    location = {x, y};
    velocity = {0.0f, 0.0f};
    acceleration = {0.0f, 0.0f};
    forces = {0.0f, 0.0f};
    
    lifetime = 255.0f;
    
    color = ofColor(255, 255, 255);
}

void yxParticle::setup(){
    ofSetColor(color);

}

void yxParticle::update(){
    acceleration.set(forces.x/mass, forces.y/mass);
    velocity.add(acceleration.x, acceleration.y);
    velocity.x = min(velocity.x, speedMax);
    velocity.y = min(velocity.y, speedMax);
    location.add(velocity.x, velocity.y);
    float t = (float)(2-rand()%4);
    lifetime = lifetime-t;
    acceleration.set(0.0f, 0.0f);
}

void yxParticle::draw(){
    //color = ofColor(213, 243, 221, lifetime);
    ofSetColor(color);
    ofDrawCircle(location.x, location.y, 5);
}

void yxParticle::changeColor(vec4 newColor){
    //color = newColor;
    color = ofColor(newColor.x, newColor.y, newColor.z, newColor.w);
}

bool yxParticle::isDead(){
    if(lifetime < 0.0){
        return true;
    }
    else
        return false;
}

void yxParticle::applyForce(float x, float y){
    forces.x = x;
    forces.y = y;
}

void yxParticle::shiftTo(float x, float y){
    location.set(x, y);
}

void yxParticle::bounce(bool x, bool y){
    if(x == true){
        velocity.x = -velocity.x;
        forces.x = -forces.x;
    }
    if (y == true){
        velocity.y = -velocity.y;
        forces.y = -forces.y;
    }
}

void yxParticle::seek(float x, float y){
    vec2 normalV = {x - location.x,y - location.y};
    normalV.normalize();
    vec2 steer = {(float)forceMax*normalV.x, (float)forceMax*normalV.y};
    applyForce(steer.x, steer.y);
}
