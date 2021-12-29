#ifndef CAMERA_H__
#define CAMERA_H__

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "InternalParamCalibrate.h"
#include "ExternalParamCalibrate.h"

/**
  * @brief     param of user,input to grab image thread
  * 
  */ 
typedef struct PUser {
  cv::Mat image_;
  void *handle_;
}PUser;

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
  float PixelAngle2World(float angle);
 private:
  void *handle_;
  cv::Mat image_;
  PUser p_user_;
}; // Camera


#endif // CAMERA_H__
