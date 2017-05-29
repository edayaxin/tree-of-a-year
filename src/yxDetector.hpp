//
//  yxDetector.hpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/23/16.
//
//

#ifndef yxDetector_hpp
#define yxDetector_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Vec.h"
#include "yxKinect.hpp"

class yxDetector {
    
public:
    // find square starting point
    yxDetector();
    ~yxDetector();
    
    void setup();
    void update();
    //void threadedFunction();     // track simutaneously with drawing, oF builtin function
    void stopDetector();
    void backCali();
    
    cv::Mat setBackground(cv::Mat background);
    cv::Point getSquareCorner();
    std::vector<vec2> findByDepth(float depthRange[]);
    
    /*----- 0424 update ------*/
    std::vector<vec3> depthList(float depthRange[]);
    
    /*----- 0518 update calibration ------*/
    std::vector<vec3> fullMat(float depthRange[]);
    std::vector<vec3> squareMat(float depthRange[]);
    
    yxKinect kinect;
    
    cv::Mat backImg;
    float fROI = 4.6;
    int rROI = 150; // 88, 18
    int cROI = 100; // 125, 185
    int kernel_size = 50;
    int detectorCount;
    
    // define square width
    int squareWidth = 220; // 245
    
    // mapping;
    float kToScreen = (float)ofGetWindowHeight()/squareWidth;

    float xMove = 60; // 0
    float yMove = -65; //65
    
    // installation height = 78cm, obj height = 8cm
    cv::Point startP = cv::Point(rROI, cROI);
    
    // detection setting
    clock_t total = 0;
};

#endif /* yxDetector_hpp */
