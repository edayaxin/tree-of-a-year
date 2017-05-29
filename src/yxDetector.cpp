 //
//  yxDetector.cpp
//  Eda2016FYP
//
//  Created by Yaxin  on 11/23/16.
//
//

#include "yxDetector.hpp"

yxDetector::yxDetector(){
    detectorCount=0;
    
}
yxDetector::~yxDetector(){

}
void yxDetector::setup(){
    kinect.openKinect();
    cout <<"kinect to screen ratio: " << kToScreen << endl;
}
void yxDetector::update(){
    
}

void yxDetector::stopDetector(){
    kinect.close();
}
cv::Mat yxDetector::setBackground(cv::Mat background){
    backImg = background;
}

cv::Point yxDetector::getSquareCorner(){
    
}

std::vector<vec2> yxDetector::findByDepth(float depthRange[]){
    std::vector<vec2> marker;
    
    if (kinect.isFrameNew()){
        
        vec2 poi = {(float)rROI, (float)cROI};
        cv::Mat depthMat = kinect.getDepthMat();
        int row = (int)depthMat.rows;
        int col = (int)depthMat.cols;
            
        /*------ find region of interest to draw ------*/
        int xMax = 0, yMax = 0, xMin = 0, yMin = 0;
        float depMax = 0;
        float depMin = 1000;

        for (int i = rROI; i < rROI+squareWidth; i++ )
        {
            for (int j = cROI; j < cROI+squareWidth; j++)
            {
                // depth value grows as distance increases
                float depthValue = depthMat.at<float>(i,j);
                if (depMax < depthValue) {
                    depMax = depthValue;
                    xMax = i;
                    yMax = j;
                }
                if (depMin > depthValue)
                {
                    depMin = depthValue;
                    xMin = i;
                    yMin = j;
                }
                if (depthValue < depthRange[1] && depthValue > depthRange[0])
                {
                    poi.set(j, i);
                    marker.push_back(poi);
                }
            }
        }
        /*------ mapping from Kinect to Screen ------*/
        for (int i = 0; i < marker.size(); i=i+1)
        {
            marker[i].x = fabs((marker[i].x-rROI + xMove)*kToScreen);
            marker[i].y = fabs((marker[i].y-cROI + yMove)*kToScreen);
            
            //marker[i].x = ofGetWindowWidth() - marker[i].x;
            marker[i].y = ofGetWindowHeight() - marker[i].y;
        }

        depthMat.release();
    }
    return marker;
}

std::vector<vec3> yxDetector::depthList(float depthRange[]){
    
    std::vector<vec3> marker;
    
    if (kinect.isFrameNew()){
        
        vec3 poi = {(float)rROI, (float)cROI, 0};
        cv::Mat depthMat = kinect.getDepthMat();
        int row = (int)depthMat.rows;
        int col = (int)depthMat.cols;
        
        /*------ find region of interest to draw ------*/
        int xMax = 0, yMax = 0, xMin = 0, yMin = 0;
        float depMax = 0;
        float depMin = 1000;
        
        for (int i = rROI; i < rROI+squareWidth; i++ )
        {
            for (int j = cROI; j < cROI+squareWidth; j++)
            {
                // depth value grows as distance increases
                float depthValue = depthMat.at<float>(i,j);
                if (depMax < depthValue) {
                    depMax = depthValue;
                    xMax = i;
                    yMax = j;
                }
                if (depMin > depthValue)
                {
                    depMin = depthValue;
                    xMin = i;
                    yMin = j;
                }
                if (depthValue < depthRange[1] && depthValue > depthRange[0])
                {
                    poi.set(j, i, depthValue);
                    marker.push_back(poi);
                }
            }
        }
        
        /*------ mapping from Kinect to Screen ------*/
        for (int i = 0; i < marker.size(); i=i+1)
        {
            marker[i].x = fabs((marker[i].x-rROI + xMove)*kToScreen);
            marker[i].y = fabs((marker[i].y-cROI + yMove)*kToScreen);
            
            //marker[i].x = ofGetWindowWidth() - marker[i].x;
            marker[i].y = ofGetWindowHeight() - marker[i].y;
        }
        
        depthMat.release();
        
        detectorCount++;
        /*
         if (detectorCount%500==0)
         {
         cout << "This is detector, I'm updating " << detectorCount << " times" << endl;
         
         time_t t = time(0);   // get time now
         struct tm * now = localtime( & t );
         cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << ' '
         << now->tm_hour << ':'
         << now->tm_min << ':'
         << now->tm_sec << ';'
         <<endl;
         
         cout << "maxDepth(" << xMax <<" , " << yMax << ") = " << depMax << endl;
         cout << "minDepth(" << xMin <<" , " << yMin << ") = " << depMin << endl;
         }
         */
    }
    return marker;
}

/* ----- for testing ------- */
std::vector<vec3> yxDetector::fullMat(float depthRange[]){

    std::vector<vec3> marker;
    
    if(kinect.isFrameNew()){
        
        cv::Mat depthMat = kinect.getDepthMat();
        int row = (int)depthMat.rows;
        int col = (int)depthMat.cols;
        cout << "kinect mat row: "<< row << "; col: " << col << endl;
        
        vec3 poi = {0, 0, 0};
    
        for(int i=0; i<row; i++)
        {
            for (int j=0; j<col;j++)
            {
                float depthValue = depthMat.at<float>(i,j);
                if (depthValue>depthRange[0] && depthValue<depthRange[1])
                {
                    poi.set(j, row-i, depthValue); // anti-clockwise rotate for 90 degree; flip by x axis
                    marker.push_back(poi);
                }
            }
        }
        
        kToScreen = 1;
        
        for(int i=0; i < marker.size(); i++)
        {
            marker[i].x = marker[i].x * kToScreen;
            marker[i].y = marker[i].y * kToScreen;
        }
        
        depthMat.release();
        return marker;
    }
}

/* ----- for use ------- */
std::vector<vec3> yxDetector::squareMat(float depthRange[])
{
    std::vector<vec3> marker;
    
    if(kinect.isFrameNew()){
        
        cv::Mat depthMat = kinect.getDepthMat();
        int row = (int)depthMat.rows;
        int col = (int)depthMat.cols;
        //cout << "kinect mat row: "<< row << "; col: " << col << endl;
        
        vec3 poi = {0, 0, 0};
        for (int i = rROI; i < rROI+squareWidth; i = i+30 )
        {
            for (int j = cROI; j < cROI+squareWidth; j = j+30)
            {
                float depthValue = depthMat.at<float>(i,j);
                if (depthValue>depthRange[0] && depthValue<depthRange[1])
                {
                    poi.set(j-cROI, squareWidth-i+rROI, depthValue); // anti-clockwise rotate for 90 degree; flip by x axis
                    marker.push_back(poi);
                }
            }
        }
        
        //kToScreen = 4;
        //cout << "win height" << ofGetWindowHeight() << endl;
        kToScreen = (float)ofGetWindowHeight()/squareWidth;
        
        for(int i=0; i < marker.size(); i++)
        {
            marker[i].x = marker[i].x * kToScreen+350;
            marker[i].y = marker[i].y * kToScreen;
        }
        
        depthMat.release();
        return marker;
    }
}
