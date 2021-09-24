/*************************************************************//**
 * @file        Camera.cpp
 * @brief       This file provides interface functions for the camera
 * @author      Qingquan Zhou (zhouqingquan118@163.com)
 * @date        09/18/2021 (M/D/Y)
 * @details     This file supplied 7 function
 *              1. Open the camera
 *              2. Close the camera
 *              3. Set the exposure time
 *              4. Grab the image
 *              5. transform the pixel point to camera point 
 *              6. transform the camera point to world point 
 *              7. transform the pixel point to world point 
 * 
 ***************************************************************/

#include "Camera.h"

/**
  * @brief      open the camera
  * @return     0:success,-1:fail
  */ 
int Camera::Open() {
  return 0;
}

/**
  * @brief      close the camera
  * @return     0:success,-1:fail
  */ 
int Camera::Close() {
  return 0;
}

/**
  * @brief      set the exposure time
  * @param[in]  exposure_time exposure time
  * @return     0:success,-1:fail
  */ 
int Camera::SetExposureTime(double exposure_time) {
  return 0;
}

/**
  * @brief      grab the image
  * @param[in]  is_online true:grab from camera,false:grab from folder
  * @return     image from camera / folder
  */ 
cv::Mat Camera::Grab(bool is_online = true) {
  cv::Mat image;
  return image;
}

/**
  * @brief      transform the pixel point to camera point 
  * @param[in]  p_p pixel point
  * @return     camera point
  */ 
cv::Point3f Camera::Pixel2Camera(cv::Point2f p_p) {
	cv::Mat p_p_q = (cv::Mat_<float>(3,1) << p_p.x,p_p.y,1);
  cv::Mat r_mat_inv;
  cv::Mat in_matrix_inv;
  cv::Mat t = external_param_calibrate_.tvec_;
  float cx = internal_param_calibrate_.camera_matrix_.at<float>(0,2);
  float cy = internal_param_calibrate_.camera_matrix_.at<float>(1,2);
  float fx = internal_param_calibrate_.camera_matrix_.at<float>(0,0);
  float fy = internal_param_calibrate_.camera_matrix_.at<float>(1,1);
  cv::invert(external_param_calibrate_.r_mat_, r_mat_inv, cv::DECOMP_SVD);
  cv::invert(internal_param_calibrate_.camera_matrix_, in_matrix_inv,cv::DECOMP_SVD);
	cv::Mat right_matrix = r_mat_inv * in_matrix_inv * p_p_q;
	cv::Mat left_matrix = r_mat_inv * t;
  double depth = left_matrix.at<float>(2,0) / right_matrix.at<float>(2,0);
  cv::Point3f camera_p;
  camera_p.x = (p_p.x - cx) * depth / fx;
  camera_p.y = (p_p.y - cy) * depth / fy;
  camera_p.z = depth;
  return camera_p;
}

/**
  * @brief      transform the camera point to world point 
  * @param[in]  p_c camera point
  * @return     world point
  */ 
cv::Point3f Camera::Camera2World(cv::Point3f p_c) {
  cv::Mat p_c_q = (cv::Mat_<float>(4,1) << p_c.x,p_c.y,p_c.z,1);
  cv::Mat r = external_param_calibrate_.r_mat_;
  cv::Mat t = external_param_calibrate_.tvec_;
  cv::Mat ex_matrix = (cv::Mat_<float>(4,4) << 
  r.at<float>(0, 0), r.at<float>(0, 1), r.at<float>(0, 2), t.at<float>(0,0),
	r.at<float>(1, 0), r.at<float>(1, 1), r.at<float>(1, 2), t.at<float>(1,0),
	r.at<float>(2, 0), r.at<float>(2, 1), r.at<float>(2, 2), t.at<float>(2,0),
	0, 0, 0, 1);
  cv::Mat ex_matrix_inv;
  cv::invert(ex_matrix,ex_matrix_inv,cv::DECOMP_SVD);
	cv::Mat p_w_q = ex_matrix_inv * p_c_q;
  cv::Point3f world_p;
  world_p.x = p_w_q.at<float>(0,0);
  world_p.y = p_w_q.at<float>(1,0);
  world_p.z = p_w_q.at<float>(2,0);
  return world_p;
}

/**
  * @brief      transform the pixel point to world point 
  * @param[in]  p_p pixel point
  * @return     world point
  */ 
cv::Point3f Camera::Pixel2World(cv::Point2f p_p) {
  return Camera2World(Pixel2Camera(p_p));
}