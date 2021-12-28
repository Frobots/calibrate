/*************************************************************//**
 * @file        ExternalParamCalibrate.cpp
 * @brief       This file defines the functions associated with the external parameter calibration
 * @author      Qingquan Zhou (zhouqingquan118@163.com)
 * @date        09/22/2021 (M/D/Y)
 * @details     This file only supplied 1 function
 *              1. Start external calibrate
 * 
 ***************************************************************/

#include <fstream> 
#include <iostream> 
#include "ExternalParamCalibrate.h"

/**
  * @brief      Start external calibrate
  * @return     0:success,-1:fail
  */ 
int32_t ExternalParamCalibrate::StartCalibrate() {
  //read internal param from file
  std::ifstream infile("./config/CameraMatrix.txt");
  if (!infile.is_open()) {
    std::cout << "open CameraMatrix.txt failed!" << std::endl; 
    return -1;
  } else {
    int32_t count = 1;
    while (!infile.eof()) {
      if (count == 1) {
        infile >> camera_matrix_.at<float>(0,0);
      } else if (count == 2) {
        infile >> camera_matrix_.at<float>(0,1);
      } else if (count == 3) {
        infile >> camera_matrix_.at<float>(0,2);
      } else if (count == 4) {
        infile >> camera_matrix_.at<float>(1,0);
      } else if (count == 5) {
        infile >> camera_matrix_.at<float>(1,1);
      } else if (count == 6) {
        infile >> camera_matrix_.at<float>(1,2);
      } else if (count == 7) {
        infile >> camera_matrix_.at<float>(2,0);
      } else if (count == 8) {
        infile >> camera_matrix_.at<float>(2,1);
      } else if (count == 9) {
        infile >> camera_matrix_.at<float>(2,2);
      }
      count++;
    }
  }
  infile.close();
  std::ifstream infile2("./config/DistCoeffs.txt");
  if (!infile2.is_open()) {
    std::cout << "open DistCoeffs.txt failed!" << std::endl; 
    return -1;
  } else {
    int32_t count = 1;
    while (!infile2.eof()) {
      float temp = 0;
      infile2 >> temp;
      if (count == 1) {
        dist_coeffs_.at<float>(0,0) = temp;
      } else if (count == 2) {
        dist_coeffs_.at<float>(0,1) = temp;
      } else if (count == 3) {
        dist_coeffs_.at<float>(0,2) = temp;
      } else if (count == 4) {
        dist_coeffs_.at<float>(0,3) = temp;
      } 
      count++;
    }
  }
  infile2.close();
  std::cout << "camera_matrix_:" << camera_matrix_ << std::endl;
  std::cout << "dist_coeffs_:" << dist_coeffs_ << std::endl;
  // input four points
  image_points_.push_back(cv::Point2f(1555.0f, 1476.0f));
  image_points_.push_back(cv::Point2f(1500.0f, 298.0f));
  image_points_.push_back(cv::Point2f(678.0f, 341.0f));
  image_points_.push_back(cv::Point2f(733.0f, 1512.0f));
  object_points_.push_back(cv::Point3f(344.84f, 95.29f, 0.f));  
  object_points_.push_back(cv::Point3f(349.94f, -204.35f, 0.f));  
  object_points_.push_back(cv::Point3f(559.46f, -201.56f, 0.f));  
  object_points_.push_back(cv::Point3f(555.02f, 98.00f, 0.f));  
  // Calculate camera pose
  cv::solvePnP(object_points_, image_points_, camera_matrix_, dist_coeffs_, rvec_, tvec_);
  cv::Rodrigues(rvec_, r_mat_);
  std::cout << "r_mat_:" << r_mat_ << std::endl;
  std::cout << "tvec_:" << tvec_ << std::endl;
  std::ofstream outfile("./config/Rt.txt", std::ios::out); 
  if (!outfile.is_open()) { 
      std::cout << "open Rt.txt failed!" << std::endl; 
  } 
  int i,j;
  for (i = 0; i < r_mat_.rows; i++) {
    for (j = 0; j < r_mat_.cols; j++) {
      outfile << r_mat_.at<float>(i,j) << std::endl;
    }
  }
  for (i = 0; i < tvec_.rows; i++) {
    outfile << tvec_.at<float>(i,0);
    if (i != tvec_.rows - 1) {
      outfile << std::endl;
    }
  }
  outfile.close();
  return 0;
}