#include "../driver/Camera.h"
#include "../driver/Robot.h"
#include "../driver/Hand.h"
#include "GeometricalDetector.h"
#include "GrpcClient.hpp"

#define IS_GRPC 0

Camera camera;
Robot robot;
Hand hand;
GrpcClient client(grpc::CreateChannel("192.168.101.117:8020", grpc::InsecureChannelCredentials()));// 127.0.0.1:50051
modbus_t* ctx = nullptr;
GeometricalDetector detector;
NR_POSE origin_pose = {136.87f, -0.00f, 709.21f, 0.01f, 0.01f, 179.97f};

void on_mouse(int event, int x, int y, int flags, void* ustc) {
  static int is_draw = 0;
  cv::Mat img = *((cv::Mat *)ustc);
	if (event == CV_EVENT_RBUTTONDOWN) {
    cv::Point3f p_w = camera.Pixel2World(cv::Point2f(x,y));
    printf("image point x:%d,y:%d\r\n",x,y);
    printf("world point x:%f,y:%f,z:%f \r\n",p_w.x,p_w.y,p_w.z);
    std::vector<cv::Point3f> points;
    std::vector<float> angles;
    points.push_back(p_w);
    angles.push_back(0.0);
    std::vector<std::string> targets_name;
    targets_name.push_back("none");
    robot.GrabTargets(points,angles,targets_name,hand,ctx);
	} else if (event == CV_EVENT_LBUTTONDOWN) {
    detector.roi_rect = cv::Rect(x, y, 0, 0);
    is_draw = 1;
  } else if (event == CV_EVENT_MOUSEMOVE) {
    if (is_draw == 1) {
      detector.roi_rect.width = x - detector.roi_rect.x;
      detector.roi_rect.height = y - detector.roi_rect.y;
    }
  } else if (event == CV_EVENT_LBUTTONUP) {
    is_draw = 0;
    if (detector.roi_rect.width < 0) {
      detector.roi_rect.x += detector.roi_rect.width;
      detector.roi_rect.width *= -1;
    }
    if (detector.roi_rect.height < 0) {
      detector.roi_rect.y += detector.roi_rect.height;
      detector.roi_rect.height *= -1;
    }
  } else if (event == CV_EVENT_LBUTTONDBLCLK) {
    int b = img.at<cv::Vec3b>(y,x)[0];
    int g = img.at<cv::Vec3b>(y,x)[1];
    int r = img.at<cv::Vec3b>(y,x)[2];
    std::cout << "x: " << x << ",y: " << y << ",bgr: " << b << " " << g << " " << r << std::endl;
  }
}

/**
  * @brief      config all driver and init
  */ 
void ConfigAll() {
  //init robot
  robot.Start();
  if (robot.MoveJX(origin_pose) == 0) {
    std::cout << "robot home success!" << std::endl;
  } else {
    std::cout << "robot home fail!" << std::endl;
  }

  // init hand
  ctx = hand.RtuConnect(ctx,"/dev/ttyUSB0",115200,'N',8,1,MODBUS_RTU_RS485);
  if(ctx == nullptr){
    std::cout << "hand init fail!" << std::endl;
  } else {
    std::cout << "hand init success!" << std::endl;
  }
  hand.Initialization(ctx,0x0000);

  //open camera
  std::cout << "open camera..." << std::endl;
  if (camera.Open() == 0) {
    std::cout << "open camra success!" << std::endl;
  } else {
    std::cout << "open camra fail!" << std::endl;
  }
}

int main() {
  cv::Mat image;
  // ConfigAll();
  int key = 0;
  cv::namedWindow("shown",CV_WINDOW_NORMAL);
  cvSetMouseCallback("shown", on_mouse, (void *)(&image));//关键内置函数
  while (key != 27) {
    //image = camera.Grab(true);
    image = cv::imread("./image2.jpg");
    if (key == 'i') {
      if (camera.internal_param_calibrate_.FindCornerImage(image)) {
        cv::imshow("show",image);
        key = cv::waitKey(0);
      } else {
        printf("find no corners\r\n");
      }
    } else if (key == 't') {
      camera.internal_param_calibrate_.StartCalibrate();
      camera.external_param_calibrate_.StartCalibrate();
    } else if (key == 'r') {
      robot.Start();
      robot.MoveJX(origin_pose);
      hand.Initialization(ctx,0x0000);
    } else if (key == 'd') {   //detection
    #if 0
      // 1.target detect
      std::vector<std::string> class_names;
      std::vector<cv::Point2f> rbox_centers;
      std::vector<float> angles;
      std::vector<float> scores;
      client.TargetDetect(image, class_names, rbox_centers, angles, scores);

      // 2. geometrical detect
      std::vector<cv::Point2f> targets_center;
      std::vector<float> targets_angle;
      detector.GetCenter(image,true,targets_center,targets_angle);
      std::vector<cv::Point3f> targets_center_world;
      std::vector<std::string> targets_name;
      for (int i = 0; i < targets_center.size(); i++) {
        float min_distance = sqrt(powf(targets_center[i].x - rbox_centers[0].x,2) + powf(targets_center[i].y - rbox_centers[0].y,2));
        std::string name = "none";
        for (int j = 0; j < rbox_centers.size(); j++) {
          //cv::putText(image,class_names[j],rbox_centers[j],cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(0,255,255),2);
          float distance = sqrt(powf(targets_center[i].x - rbox_centers[j].x,2) + powf(targets_center[i].y - rbox_centers[j].y,2));
          if (min_distance >= distance) {
            min_distance = distance;
            name = class_names[j];
          }
        }
        targets_name.push_back(name);
        targets_center_world.push_back(camera.Pixel2World(targets_center[i]));// camera sys to robot sys
        targets_angle[i] = camera.PixelAngle2World(targets_angle[i]) - 90;
        cv::putText(image,name,targets_center[i],cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(255,0,0),2);
      }
      cv::imshow("shown",image);
      key = cv::waitKey(0);
      //robot.GrabTargets(targets_center_world,targets_angle,targets_name,hand,ctx);
      #else
      std::vector<std::string> class_names;
      std::vector<cv::Point2f> rbox_centers;
      std::vector<float> targets_angles;
      std::vector<float> targets_scores;
      std::vector<cv::Point3f> targets_center_world;

      client.TargetDetect(image, class_names, rbox_centers,targets_angles,targets_scores);
      for (int i = 0; i < rbox_centers.size(); i++) {
        if (rbox_centers[i].x < detector.roi_rect.tl().x || rbox_centers[i].x > detector.roi_rect.br().x ||
        rbox_centers[i].y < detector.roi_rect.tl().y || rbox_centers[i].y > detector.roi_rect.br().y) {
          class_names.erase(class_names.begin() + i);
          rbox_centers.erase(rbox_centers.begin() + i);
          targets_angles.erase(targets_angles.begin() + i);
          targets_scores.erase(targets_scores.begin() + i);
        }
      }
      for (int i = 0; i < rbox_centers.size(); i++) {
        cv::putText(image,class_names[i],rbox_centers[i],cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(255,0,0),2);
        targets_center_world.push_back(camera.Pixel2World(rbox_centers[i]));// camera sys to robot sys
        targets_angles[i] = camera.PixelAngle2World(targets_angles[i]) - 90;
      }
      cv::imshow("shown",image);
      key = cv::waitKey(0);
      // robot.GrabTargets(targets_center_world,targets_angles,class_names,hand,ctx);
      #endif

    } else if(key == 'b') {
      robot.MoveJX(origin_pose);
    }
    cv::rectangle(image,detector.roi_rect,cv::Scalar(255.0,.0,.0),2);
    #if IS_GRPC
    //grpc object detect
    cv::Mat objs_image;
    std::vector<std::string> class_name;
    std::vector<std::vector<cv::Point2f>> rrbox;
    objs_image = client.TargetDetect(image, class_name, rrbox);
    if (objs_image.empty()) {
      continue;
    }
    #endif
    cv::imshow("shown",image);
    key = cv::waitKey(1);
  }
  camera.Close();
  return 0;
}