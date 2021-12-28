/*************************************************************//**
 * @file        GeometricalDetector.cpp
 * @brief       this class provides interfaces for target detect by geometrical features
 * @author      Qingquan Zhou (zhouqingquan118@163.com)
 * @date        10/11/2021 (M/D/Y)
 * 
 ***************************************************************/

#include "GeometricalDetector.h"

/**
  * @brief      get target obj's center point and angle
  * @param[in]  img detect img 
  * @param[in]  is_draw true:draw the target at image,false:don't draw the target at image 
  * @param[out] targets_center targets center
  * @param[out] targets_angle targets angle
  * @return     target num
  */ 
unsigned int GeometricalDetector::GetCenter(cv::Mat &img, bool is_draw,std::vector<cv::Point2f> &targets_center,std::vector<float> &targets_angle) {
  if (img.empty()) {
    return 0;
  }
  cv::Mat roi,target_image,blur_img,canny_img;
  int canny_thres_min = 150;
  int canny_thres_max = 255;
  int area_thres_min = 10000;
  int area_thres_max = 80000;
  int contours_count = 0;
  std::vector<std::vector<cv::Point>> orign_contours,contours;
  std::vector<cv::Vec4i> orign_hierarchy,hierarchy;
  cv::RNG g_rng(12345);
  targets_center.clear();
  targets_angle.clear();
  // set roi
  img(roi_rect).copyTo(roi);

  // Background segmentation
  target_image = cv::Mat(roi.size(),CV_8UC1,cv::Scalar(0));
  std::vector<cv::Point2f> target_points;
  for (int i = 0; i < roi.rows; i++) {
    cv::Vec3b *p = roi.ptr<cv::Vec3b>(i);
    for (int j = 0; j < roi.cols; j++) {
      cv::Vec3b pix = *p++;
      int b = pix[0];
      int g = pix[1];
      int r = pix[2];
      if (b > 90 && g > 90 && r > 90) continue;
      target_points.push_back(cv::Point2f(j,i));
      target_image.at<uchar>(i,j) = 255;
    }
  }

  // filter
  //cv::medianBlur(target_image,blur_img,3);
  cv::Mat element = getStructuringElement(cv::MORPH_RECT,cv::Size(3, 3));
  if (target_image.empty()) {
    return 0;
  }
	morphologyEx(target_image, blur_img, cv::MORPH_OPEN,element);

  // find contours
  Canny(blur_img, canny_img, canny_thres_min, canny_thres_min * 2, 3);

  // cv::imshow("target_image",target_image);
  // cv::imshow("blur_img",blur_img);
  // cv::imshow("canny_img",canny_img);
  // cv::waitKey(0);

  findContours(canny_img, orign_contours, orign_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
  

  // filter contours
  for (int i = 0; i < orign_contours.size(); i++){
    double area = cv::minAreaRect(cv:: Mat(orign_contours[i])).size.area();
    std::cout << "area:" << area << std::endl;
    if (area > area_thres_min && area < area_thres_max) {
      contours.push_back(orign_contours[i]);
      hierarchy.push_back(orign_hierarchy[i]);
    }
  }

  // find centers and angle
  contours_count = contours.size();
  std::cout << "contours_count:"<<contours_count << std::endl;
  std::vector<cv::Moments> mu(contours_count);
  std::vector<cv::RotatedRect> min_rects(contours_count);
  for (int i = 0; i < contours_count; i++) {
    //计算图像矩
    mu[i] = moments(contours[i], false);
    targets_center.push_back(cv::Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00) + cv::Point2f(roi_rect.x,roi_rect.y));
    min_rects[i] = cv::minAreaRect(cv:: Mat(contours[i]));
    if (min_rects[i].size.width >= min_rects[i].size.height) {
      targets_angle.push_back(90 - min_rects[i].angle);
      //cv::putText(img(roi_rect),std::to_string(targets_angle[i] + 1.8),min_rects[i].boundingRect().tl(),cv::FONT_HERSHEY_COMPLEX,2,cv::Scalar(0,0,255),2);
    } else {
      targets_angle.push_back(180 - min_rects[i].angle);
      //cv::putText(img(roi_rect),std::to_string(targets_angle[i] + 1.8),min_rects[i].boundingRect().tl(),cv::FONT_HERSHEY_COMPLEX,2,cv::Scalar(0,255,0),2);
    }
    // draw
    if (is_draw) {
      cv::Scalar color = cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
      drawContours(img(roi_rect), contours, i, color, 3, 8, hierarchy, 0, cv::Point());
      cv::putText(img(roi_rect),std::to_string(targets_angle[i]),min_rects[i].boundingRect().tl(),cv::FONT_HERSHEY_COMPLEX,2,cv::Scalar(0,0,255),2);
      cv::Point2f rect_points[4]; 
      min_rects[i].points(rect_points);
      for( int j = 0; j < 4; j++ ){
        line(img(roi_rect), rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,255,0), 3, 8 );
      }
      circle(img(roi_rect), min_rects[i].center, 2, cv::Scalar(0,0,255), -1, 8, 0);
    }
  }
  // show
  // cv::namedWindow("target",cv::WINDOW_NORMAL);
  // cv::namedWindow("blur",cv::WINDOW_NORMAL);
  // cv::namedWindow("canny",cv::WINDOW_NORMAL);
  // cv::namedWindow("img",cv::WINDOW_NORMAL);
  // cv::imshow("target",target_image);
  // cv::imshow("blur",blur_img);
  // cv::imshow("canny",canny_img);
  // cv::imshow("img",img);
  // cv::waitKey(0);
  return contours_count;
}
