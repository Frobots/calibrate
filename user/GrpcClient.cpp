/*************************************************************//**
 * @file        GrpcClient.cpp
 * @brief       This file provides interface functions for the Grpc Client
 * @author      Qingquan Zhou (zhouqingquan118@163.com)
 * @date        11/02/2021 (M/D/Y)
 * 
 ***************************************************************/

#include "GrpcClient.hpp"

cv::Mat GrpcClient::TargetDetect(cv::Mat img, std::vector<std::string> &class_name, std::vector<cv::Point2f> &rbox_centers, std::vector<float> &angles, std::vector<float> &scores) {
  Request *request = new Request();
  //记录当前时间
  std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
  // cv::imshow("test",img);
  // cv::waitKey(0);
  //编码的前必须的data格式，用一个uchar类型的vector
  std::vector<uchar> data_encode;
  //直接编码
  cv::imencode(".jpg", img, data_encode);
  //放到string里面
  std::string str_encode(data_encode.begin(), data_encode.end());
  request->set_allocated_encoded_image(&str_encode);
  request->set_width(img.cols);
  request->set_height(img.rows);
  ClientContext context;
  //定义一个用来存储返回信息的变量
  Response response;
  //获得远程API（俗称远程方法）的指针
  Status status = stu_->DoFormat(&context,*request,&response);

  //再次记录当前时间
  std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();
  auto sec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  if (status.ok()) {
    // std::cout << "数据传输完成\n";
    // std::cout << "传输时间为：" << sec.count() << std::endl;
    google::protobuf::RepeatedPtrField<Object> objs = response.objects();
    for (auto& single : objs) {
      float x = single.rbox().x();
      float y = single.rbox().y();
      float h = single.rbox().h();
      float w = single.rbox().w();
      float theta = single.rbox().theta();
      std::string name = single.class_name();
      float score = single.score();
      cv::Point p(x,y - 10);
      // cv::putText(img,name,p,cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(0,255,255),2);
      cv::Point2f rect_points[4]; 
      cv::RotatedRect(cv::Point2f(x,y),cv::Size(w,h),theta).points(rect_points);
      class_name.push_back(name);
      rbox_centers.push_back(cv::Point2f(x,y));
      if (theta < 90) {
        theta = 90 - theta;
      } else {
        theta = 180 - (theta - 90);
      }
      angles.push_back(theta);
      scores.push_back(score);
      // for( int j = 0; j < 4; j++ ) {
      //   line(img, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,255,255), 3, 8 );
      // }
      // cv::putText(img,std::to_string(theta),rect_points[0],cv::FONT_HERSHEY_COMPLEX,2,cv::Scalar(0,0,255),2);
    }
  } else {
    std::cout << "数据传输失败\n";
  }
  return img;
}