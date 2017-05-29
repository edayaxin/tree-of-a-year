//
//  yxKinect.cpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/23/16.
//
//

#include "yxKinect.hpp"


yxKinect::yxKinect(){
    frameIsNew = false;
    kOpened = false;
    newFrame = -1;
    kinectThreadCount = 0;
    startThread(true);
}

yxKinect::~yxKinect(){
    close();
}

// ? not working when yxKinect not in oF main class

void yxKinect::threadedFunction(){
    
    while(isThreadRunning()){
        update();
        kinectThreadCount++;
    }
}

// oepration on Kinect
bool yxKinect::openKinect()
{
    close();
    kOpened = false;
    
    if (imgProcessor == Processor::cpu)
    {
        if (!pipeline)
            pipeline = new libfreenect2::CpuPacketPipeline();
    }
    else if (imgProcessor == Processor::cl)
    {
#ifdef LIBFREENECT2_WITH_OPENCL_SUPPORT
        if (!pipeline)
            pipeline = new libfreenect2::OpenCLPacketPipeline(deviceId);
#else
        std::cout << "OpenCL pipeline is not supported!" << std::endl;
#endif
    }
    else if (imgProcessor == Processor::gl)
    {
#ifdef LIBFREENECT2_WITH_OPENGL_SUPPORT
        if (!pipeline)
            pipeline = new libfreenect2::OpenGLPacketPipeline();
#else
        std::cout << "OpenCL pipeline is not supported!" << std::endl;
#endif
    }
    else if (imgProcessor == Processor::cuda)
    {
#ifdef LIBFREENECT2_WITH_CUDA_SUPPORT
        if (!pipeline)
            pipeline = new libfreenect2::CudaPacketPipeline(deviceId);
#else
        std::cout << "CUDA pipeline is not supported!" << std::endl;
#endif
    }
    
    // [discovery]
    if(freenect2.enumerateDevices() == 0)
    {
        std::cout << "no device connected!" << std::endl;
        return -1;
    }
    
    serial = freenect2.getDefaultDeviceSerialNumber();
    // [discovery]
    
    if(pipeline)
    {
        // [open]
        dev = freenect2.openDevice(serial, pipeline);
        // [open]
    }
    else
    {
        dev = freenect2.openDevice(serial);
    }
    
    if(dev == 0)
    {
        std::cout << "failure opening device!" << std::endl;
        return -1;
    }
    
    protonect_shutdown = false;
    
    // [listeners]
    int types = 0;
    if (enable_rgb)
        types |= libfreenect2::Frame::Color;
    if (enable_depth)
        types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
    listener = new libfreenect2::SyncMultiFrameListener(types);

    dev->setColorFrameListener(listener);
    dev->setIrAndDepthFrameListener(listener);
    // [listeners]
    
    // [start]
    if (enable_rgb && enable_depth)
    {
        if (!dev->start())
            return -1;
    }
    else
    {
        if (!dev->startStreams(enable_rgb, enable_depth))
            return -1;
    }
    
    std::cout << "device serial: " << dev->getSerialNumber() << std::endl;
    std::cout << "device firmware: " << dev->getFirmwareVersion() << std::endl;
    
    // [registration setup]
    registration = new libfreenect2::Registration(dev->getIrCameraParams(), dev->getColorCameraParams());
    undistorted = new libfreenect2::Frame(512, 424, 4);
    registered  = new libfreenect2::Frame(512, 424, 4);
    // [registration setup]
    
    kOpened = true;
    return true;
}
void yxKinect::update(){
  
    if (ofGetFrameNum() > kinectThreadCount)
    {
        cout << "in kinect update(), ofgetframe" << ofGetFrameNum() << " is smaller than kinect thread count " << kinectThreadCount << endl;
        newFrame = ofGetFrameNum();
        frameIsNew = false;
    }
    if (kOpened)
    {
        lock();
        
        if (!listener->waitForNewFrame(frames, 10*1000)) // 10 sconds
        {
            std::cout << "timeout!" << std::endl;
            return -1;
        }
        
        libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
        libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
        libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
        
        if (enable_rgb && enable_depth)
        {
            registration->apply(rgb, depth, undistorted, registered);
        }
        
        int rowD = undistorted->height;
        int colD = undistorted->width;
        cv::Mat(rowD, colD, CV_32FC1, undistorted->data).copyTo(depthMat);
        int rowRgb = registered->height;
        int colRgb = registered->width;
        cv::Mat(rowRgb, colRgb, CV_8UC4, registered->data).copyTo(rgbMat);
        
        frameIsNew = true;
        
        listener->release(frames);
        if(kinectThreadCount%100 == 0){
            cout << "This is Kinect update(), I'm updating " << kinectThreadCount << " times" << endl;
        }
        unlock();
    }
    
}

void yxKinect::close(){
    if (kOpened)
    {
        // wait for 10s to finish thread
        waitForThread(true, 10000);
        
        // release frames and close the device
        listener->release(frames);
    
        dev->stop();
        dev->close();
        
        delete listener;
        listener = NULL;
        
        delete undistorted;
        undistorted = NULL;
        
        delete registered;
        registered = NULL;
        
        delete registration;
        
        kOpened = false;
    }
    return 0;
}

cv::Mat yxKinect::getDepthMat(){
    return depthMat;
}

cv::Mat yxKinect::getRgbMat(){
    return rgbMat;
}

bool yxKinect::isFrameNew(){
    return frameIsNew;
}
