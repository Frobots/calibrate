/*************************************************************//**
 * @file        InternalParamCalibrate.cpp
 * @brief       This file defines the functions associated with the internal parameter calibration
 * @author      Qingquan Zhou (zhouqingquan118@163.com)
 * @date        09/22/2021 (M/D/Y)
 * @details     This file supplied 3 function
 *              1. Collect the image points(corners)
 *              2. Collect the object points(corners)
 *              3. Start internal calibrate
 * 
 ***************************************************************/

#include <fstream> 
#include <iostream> 
#include "InternalParamCalibrate.h"

/**
  * @brief      Collect the image points(corners)
  * @return     0:success,-1:fail
  */ 
int32_t InternalParamCalibrate::CollectImagePoints() {
  int32_t count = 1;
  while(count <= image_count_) {
    std::string file_name = "./images/Image";
    file_name.append(std::to_string(count).append(".jpg"));
    std::cout << file_name << std::endl;
    cv::Mat image = cv::imread(file_name);
    cv::Mat gray_image;
    if (count == 1) {
      image_size_.width = image.cols;
      image_size_.height = image.rows;
      std::cout << "image width:" << image_size_.width << std::endl;
      std::cout << "image height:" << image_size_.height << std::endl;
    }
    cv::cvtColor(image,gray_image,CV_RGB2GRAY);
    std::vector<cv::Point2f> image_points_buf;
    if (!cv::findChessboardCorners(gray_image,board_size_,image_points_buf)) {
      std::cout << "fail to find the chess board corners" << std::endl;
      count++;
      continue;
    } else {
      cv::find4QuadCornerSubpix(gray_image,image_points_buf,cv::Size(5,5));
      cv::drawChessboardCorners(image,board_size_,image_points_buf,true);
    }
    image_points_seq_.push_back(image_points_buf);
    cv::namedWindow("image",cv::WINDOW_NORMAL);
    cv::imshow("image",image);
    cv::waitKey(500);
    count++;
  }
  return 0;
}

/**
  * @brief      Collect the object points(corners)
  * @return     0:success,-1:fail
  */ 
int32_t InternalParamCalibrate::CollectObjectPoints() {
  int32_t i,j,k;
  for (i = 0; i < image_count_; i++) {
    std::vector<cv::Point3f> real_points_buf;
    for (j = 0; j < board_size_.width; j++) {
      for (k = 0; k < board_size_.height; k++) {
        cv::Point3f real_point;
        real_point.x = j * square_size_.width;
        real_point.y = k * square_size_.height;
        real_point.z = 0;
        real_points_buf.push_back(real_point);
      }
    }
    object_points_seq_.push_back(real_points_buf);
  }
  return 0;
}

/**
 * @brief      Start internal calibrate
 * @return     0:success,-1:fail
 */ 
int32_t InternalParamCalibrate::StartCalibrate() {
  CollectImagePoints();
  CollectObjectPoints();
  repeat_err_ = cv::calibrateCamera(object_points_seq_,image_points_seq_,image_size_,camera_matrix_,dist_coeffs_,rvecs_mat_,tvecs_mat_);
  std::cout << "camera_matrix_:" << camera_matrix_ << std::endl;
  std::cout << "dist_coeffs_:" << dist_coeffs_ << std::endl;
  std::cout << "repeat_err_:" << repeat_err_ << std::endl;
  std::ofstream outfile("./config/CameraMatrix.txt", std::ios::out); 
  if (!outfile.is_open()) { 
      std::cout << "open CameraMatrix.txt failed!" << std::endl; 
  } 
  int i,j;
  for (i = 0; i < camera_matrix_.rows; i++) {
    for (j = 0; j < camera_matrix_.cols; j++) {
      outfile << camera_matrix_.at<double>(i,j);
      if (i == camera_matrix_.rows - 1 && j == camera_matrix_.cols - 1) {
        break;
      }
      outfile << std::endl;
    }
  }
  outfile.close();
  std::ofstream outfile2("./config/DistCoeffs.txt", std::ios::out); 
  if (!outfile2.is_open()) { 
    std::cout << "open DistCoeffs.txt failed!" << std::endl; 
  } 
  for (i = 0; i < dist_coeffs_.rows; i++) {
    for (j = 0; j < dist_coeffs_.cols; j++) {
      outfile2 << dist_coeffs_.at<double>(i,j);
      if (i == dist_coeffs_.rows - 1 && j == dist_coeffs_.cols - 1) {
        break;
      }
      outfile2 << std::endl;
    }
  }
  outfile2.close();
  return 0;
}