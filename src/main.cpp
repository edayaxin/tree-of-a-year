#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    //1280 x 1024
    float widthToHeight = (float)1024/1280;
    int wid = 1700;
    ofSetupOpenGL(wid, (int)wid*widthToHeight, OF_WINDOW);
    //ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
