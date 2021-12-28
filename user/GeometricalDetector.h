#ifndef GEOMETRICAL_H__
#define GEOMETRICAL_H__

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>

/**
  * @brief     this class provides interfaces for target detect by geometrical features
  * 
  */ 
class GeometricalDetector{
 public:
  unsigned  GetCenter(cv::Mat &img, bool is_draw,std::vector<cv::Point2f> &targets_center,std::vector<float> &targets_angle);
  cv::Rect roi_rect;
  GeometricalDetector() {
    roi_rect = cv::Rect(660,400,1000,1200);
  }
}; // GeometricalDetector
    
#endif  //GEOMETRICAL_H__