//
//  yxKinect.hpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/23/16.
//
//

#ifndef yxKinect_hpp
#define yxKinect_hpp

#include "ofMain.h"

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <time.h>

/// [headers]
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/calib3d/calib3d.hpp"
/// [headers]

using namespace std;
using namespace cv;

class yxKinect : public ofThread{
    
public:
    yxKinect();
    ~yxKinect();
    // Kinect variables setup
    enum Processor { cpu, cl, gl, cuda};
    
    bool protonect_shutdown = true;

    int imgProcessor = cpu;
    bool enable_rgb = true;
    bool enable_depth = true;
    int deviceId = -1;
    string serial;
    
    // operation on Kinect
    bool openKinect();
    void update();
    void close();
    bool isFrameNew();
    bool withDepthValue();
    
    // operation on Kinect frames (all are undistored)
    cv::Mat getDepthMat();
    cv::Mat getRgbMat();
    cv::Mat getIrMat();
    
private:
    
    // Kinect frames setup
    bool newFrameBuffer;
    bool frameIsNew;
    bool kOpened;
    int newFrame;
    int kinectThreadCount;
    cv::Mat depthMat;
    cv::Mat rgbMat;
    
    libfreenect2::FrameMap frames;
    
    // Kinect device setup
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = 0;
    libfreenect2::PacketPipeline *pipeline = 0;
    
    libfreenect2::Registration *registration;
    libfreenect2::SyncMultiFrameListener *listener;
    libfreenect2::Frame  *undistorted = NULL;
    libfreenect2::Frame  *registered = NULL;
    
    
    // run separately once open is called *** not use thread HERE, but in detector
    void threadedFunction();

};
#endif /* yxKinect_hpp */
