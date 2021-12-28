#ifndef ROBOT_H__
#define ROBOT_H__
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "OpenNR-IF.h"
#include "Hand.h"

/**
  * @brief     this class represents for the robot
  * @details   this class provides interfaces for robot operations such as start,stop,pause,move...
  * 
  */ 
class Robot {
 public:
  int32_t Start();
  int32_t Stop();
  int32_t Pause();
  int32_t SetSuddenlyStop(bool value);
  int32_t MoveJX(NR_POSE pose);
  int32_t MoveAX(float angelsArray[6]);
  int32_t GetSpeed(int &value);
  int32_t GetElectric(float values[6]);
  int32_t GetAxisAngel(float values[6]);
  int32_t GetAxisPos(float values[6]);
  int32_t GetIOMotorsOnLAMP(bool &value);
  bool IsMoveEnd(NR_POSE pose);
  int32_t GrabTargets(std::vector<cv::Point3f> points, std::vector<float> angles, std::vector<std::string> targets_name, Hand &hand,modbus_t* ctx);
  Robot() {
    m_enable = 1;
  }
 private:
  int nXmlOpenId;
  int m_enable;
  void delay_ms(int ms);
}; // Robot


#endif // ROBOT_H__
