//
//  Vec.h
//  Eda2016FYP
//
//  Created by Yaxin  on 11/27/16.
//
//

#ifndef Vec_h
#define Vec_h

#include <math.h>

struct vec2{
    float x;
    float y;
    
    void add(float m, float n){
        x = x+m;
        y = y+n;
    }
    void sub(float m, float n){
        x = x - m;
        y = y - n;
    }
    void set(float m, float n){
        x = m;
        y = n;
    }
    void normalize()
    {
        float dis = sqrt(x*x+y*y);
        x = (float) x / dis;
        y = (float) y / dis;
    }
    void multi(float m, float n){
        x = x*m;
        y = y*m;
    }
};

struct vec3{
    float x;
    float y;
    float z;
    
    void add(float m, float n, float k){
        x = x+m;
        y = y+n;
        z = z+k;
    }
    void sub(float m, float n, float k){
        x = x - m;
        y = y - n;
        z = z - k;
    }
    void set(float m, float n, float k){
        x = m;
        y = n;
        z = k;
    }
    void normalize()
    {
        float dis = sqrt(x*x+y*y+z*z);
        x = (float) x / dis;
        y = (float) y / dis;
        z = (float) z / dis;
    }
    void multi(float m, float n, float k){
        x = x*m;
        y = y*m;
        z = z*k;
    }
};

struct vec4{
    float x;
    float y;
    float z;
    float w;
};

#endif /* Vec_h */
