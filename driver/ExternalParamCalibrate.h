#ifndef EXTERNAL_PARAM_CALIBRATE_H__
#define EXTERNAL_PARAM_CALIBRATE_H__

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

/**
  * @brief     This class defines the functions associated with the external parameter calibration
  */ 
class ExternalParamCalibrate {
 public:
  std::vector<cv::Point2f> image_points_;
  std::vector<cv::Point3f> object_points_;
  cv::Mat camera_matrix_;
  cv::Mat dist_coeffs_;
  cv::Mat rvec_;
  cv::Mat tvec_;
  cv::Mat r_mat_;
  int32_t StartCalibrate();
  ExternalParamCalibrate() {
    rvec_ = cv::Mat(3,1,CV_32FC1,cv::Scalar::all(0));
    tvec_ = cv::Mat(3,1,CV_32FC1,cv::Scalar::all(0));
    r_mat_ = cv::Mat(3,3,CV_32FC1,cv::Scalar::all(0));
    camera_matrix_ = cv::Mat(3,3,CV_32FC1,cv::Scalar::all(0));
    dist_coeffs_ = cv::Mat(1,4,CV_32FC1,cv::Scalar::all(0));
    std::ifstream infile("./config/Rt.txt");
    if (!infile.is_open()) {
      std::cout << "open Rt.txt failed!" << std::endl;
    } else {
      int32_t count = 1;
      while (!infile.eof()) {
        if (count == 1) {
          infile >> r_mat_.at<float>(0,0);
        } else if (count == 2) {
          infile >> r_mat_.at<float>(0,1);
        } else if (count == 3) {
          infile >> r_mat_.at<float>(0,2);
        } else if (count == 4) {
          infile >> r_mat_.at<float>(1,0);
        } else if (count == 5) {
          infile >> r_mat_.at<float>(1,1);
        } else if (count == 6) {
          infile >> r_mat_.at<float>(1,2);
        } else if (count == 7) {
          infile >> r_mat_.at<float>(2,0);
        } else if (count == 8) {
          infile >> r_mat_.at<float>(2,1);
        } else if (count == 9) {
          infile >> r_mat_.at<float>(2,2);
        } else if (count == 10) {
          infile >> tvec_.at<float>(0,0);
        } else if (count == 11) {
          infile >> tvec_.at<float>(1,0);
        } else if (count == 12) {
          infile >> tvec_.at<float>(2,0);
        }
        count++;
      }
    }
    infile.close();
  }
  
}; // ExternallParamCalibrate

#endif // EXTERNAL_PARAM_CALIBRATE_H__