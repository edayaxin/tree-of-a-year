#pragma once

#include "ofMain.h"
#include "yxKinect.hpp"
#include "yxDetector.hpp"
#include "yxBeetle.hpp"
#include "beetleGroup.hpp"
#include "Vec.h"
#include "ofxRipples.h"
#include "ofxBounce.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    yxDetector objDetect;
    std::vector<vec2> roiPoints;
    
    std::vector<vec3> roiPointsWithDepth;
    std::vector<vec3> roiPointsWithDepthPar;
    std::vector<vec3> fullKinectMat;
    
    std::vector<vec2> roiRegion;

    float dRange[2] = {300, 2000}; // for calibration
    float dRangePar[2] = {800, 900};
    int mainThreadCount;
    
    ofxRipples rip;
    ofxBounce bounce;
    
    bool sendSerial;
    ofSerial ardSerial;
    int ofDetect;
    
    beetleGroup bG;
    yxBeetle beetle;
};
