#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60); 
    ofToggleFullscreen();
    ofBackground(0);
    ofSetBackgroundAuto(true);

    /*------ 0417 added ------*/
    ofEnableAlphaBlending();
    ofSetWindowShape(1024*1700/1280, 1024);
    
    
    /* ----------- set up Kinect detection -----------*/
    objDetect.setup();
    
    mainThreadCount = 0;
    
    cout << "window Hight, width" << ofGetWindowHeight()<< " " << ofGetWindowWidth() << endl;
    
    beetle.setup();
    bG.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    /* ----------- Detector and Kinect update -----------------------*/
//    roiPoints = objDetect.findByDepth(dRange);
//    if ((int)roiPoints.size() == 0){
//        objDetect.update();
//    }

    /* ----------- Detector and Kinect update 0424 update-----------*/
    roiPointsWithDepth = objDetect.depthList(dRange);
    roiPointsWithDepthPar = objDetect.depthList(dRangePar);
    
    if ((int)roiPointsWithDepth.size() == 0){
        objDetect.update();
    }
    
    /* ----------- Detector and Kinect update 0518 update-----------*/
    fullKinectMat = objDetect.squareMat(dRange);
    
    if ((int)fullKinectMat.size() == 0){
        objDetect.update();
    }
    
    /* ----------- thread update -----------------------*/
    mainThreadCount++;
    
    if (mainThreadCount%1000==0){
        cout << "ROI points size " << roiPointsWithDepth.size() << endl;
    }
    beetle.update();
    bG.update();
};

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofSetColor(255.0, 255.0, 255.0, 255.0);
    //beetle.draw();
    bG.draw();

    for (int i = 0; i < fullKinectMat.size(); i=i+1)
    {
        //cout<<"detected and draw"<<endl;
        
        /*---- color mapping ----*/
        vec4 newColor;
        //float alphaValue = fmod(fullKinectMat[i].z,20.0);
        //alphaValue = alphaValue-100;
        float alphaValue = 10.0;
        if(alphaValue == 0){alphaValue = 50;}
        
        if (fullKinectMat[i].z < 900)
        {
            newColor = {255, 230, 153, alphaValue}; // yellow
        }
        else if(fullKinectMat[i].z < 950)
        {
            newColor = {204, 255, 255,alphaValue}; // blue
        }
        else if(fullKinectMat[i].z < 1000)
        {
            newColor = {255, 230, 255,alphaValue}; // purple
        }
        else if(fullKinectMat[i].z < 1100)
        {
            newColor = {230, 255, 238,alphaValue}; // green
        }
        else
        {
            newColor = {50,100, 100,alphaValue};
        }
        ofSetColor(newColor.x, newColor.y, newColor.z, newColor.w);
        
        /*---- draw circles -----*/
        int m = fullKinectMat[i].x;
        int n = fullKinectMat[i].y;
        
        ofDrawCircle(m, n, 100);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f')
        ofToggleFullscreen();
    if (key == 'k')
        objDetect.stopDetector();
    if (key == 'q'){
         objDetect.stopDetector();
         ofExit();
    }
    
    if (key == OF_KEY_UP){
        rip.damping += 0.01;
    } else if ( key == OF_KEY_DOWN){
        rip.damping -= 0.01;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    rip.damping = ofMap(y, 0, ofGetHeight(), 0.9, 1.0, true);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
