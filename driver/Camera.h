#ifndef CAMERA_H__
#define CAMERA_H__

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "InternalParamCalibrate.h"
#include "ExternalParamCalibrate.h"

/**
  * @brief     this class represents for the camera
  * @details   camera feature : open / close / grab / set exposure time
  * 
  */ 
class Camera {
 public:
  int32_t Open();
  int32_t Close();
  cv::Mat Grab(bool is_online);
  int32_t SetExposureTime(double exposure_time);
  InternalParamCalibrate internal_param_calibrate_;
  ExternalParamCalibrate external_param_calibrate_;
  cv::Point3f Pixel2Camera(cv::Point2f p_p); 
  cv::Point3f Camera2World(cv::Point3f p_c);
  cv::Point3f Pixel2World(cv::Point2f p_p);
}; // Camera


#endif // CAMERA_H__
