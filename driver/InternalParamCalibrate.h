#ifndef INTERNAL_PARAM_CALIBRATE_H__
#define INTERNAL_PARAM_CALIBRATE_H__

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

/**
  * @brief     This class defines the functions associated with the internal parameter calibration
  */ 
class InternalParamCalibrate {
 public:
  int32_t image_count_;
  cv::Size image_size_;
  cv::Size board_size_;
  cv::Size square_size_;
  cv::Mat camera_matrix_;
  cv::Mat dist_coeffs_;
  std::vector<cv::Mat> rvecs_mat_;
  std::vector<cv::Mat> tvecs_mat_;
  double repeat_err_;
  int32_t StartCalibrate();
  InternalParamCalibrate() {
    image_count_ = 12;
    board_size_ = cv::Size(8,6);
    square_size_ = cv::Size(10,10);
    camera_matrix_ = cv::Mat(3,3,CV_32FC1,cv::Scalar::all(0));
    std::ifstream infile("./config/CameraMatrix.txt");
    if (!infile.is_open()) {
      std::cout << "open CameraMatrix.txt failed!" << std::endl;
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
    dist_coeffs_ = cv::Mat(1,5,CV_32FC1,cv::Scalar::all(0));
    std::ifstream infile2("./config/DistCoeffs.txt");
    if (!infile2.is_open()) {
      std::cout << "open DistCoeffs.txt failed!" << std::endl; 
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
        } else if (count == 5) {
          dist_coeffs_.at<float>(0,4) = temp;
        } 
        count++;
      }
    }
    infile2.close();
    repeat_err_ = 0;
  }
 private:
  std::vector<std::vector<cv::Point2f>> image_points_seq_;
  std::vector<std::vector<cv::Point3f>> object_points_seq_;
  int32_t CollectImagePoints();
  int32_t CollectObjectPoints();

}; // InternalParamCalibrate

#endif // INTERNAL_PARAM_CALIBRATE_H__