/*************************************************************//**
 * @file        Robot.cpp
 * @brief       This class provides interfaces for robot operations such as start,stop,pause,move...
 * @author      Qingquan Zhou (zhouqingquan118@163.com)
 * @date        10/22/2021 (M/D/Y)
 * 
 ***************************************************************/

#include "Robot.h"
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctime>

#define EXT_AXIS 0
#define IP_ADDRESS "192.168.100.210"
#define TARGET_POSITION {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}
#define X_OFFSET 2
#define Y_OFFSET 0
#define Z_OFFSET 0

/**
  * @brief      start the robot
  * @return     0:success,-1:fail
  */ 
int32_t Robot::Start() {
  NACHI_COMMIF_INFO Info;
  Info.lRetry = 0;
  Info.lPortNo = 0;
  Info.lCommSide = 0;
  Info.lSendTimeOut = 0;
  Info.pcAddrs = IP_ADDRESS;
  Info.lKind   = NR_DATA_XML;
  Info.lMode   = NR_MODE_COMM_CLIENT;
  nXmlOpenId = NR_Open(&Info);
  if(0 < nXmlOpenId) {
    std::cout << "robot start success!" << std::endl;
    return 0;
  } else {
    std::cout << "robot start fail!" << std::endl;
    return -1;
  }
}

/**
  * @brief      stop the robot 
  * @return     0:success,-1:fail
  */ 
int32_t Robot::Stop() {
  int nErr = NR_Close(nXmlOpenId);
  if(NR_E_NORMAL == nErr) {
    std::cout << "robot stop success!" << std::endl;
    nXmlOpenId = -1;
    return 0;
  } else {
    std::cout << "robot stop fail!" << std::endl;
    return -1;
  }
}

/**
  * @brief      pause the robot
  * @return     0:success,-1:fail
  */ 
int32_t Robot::Pause() {
  m_enable = NR_CtrlMotor(nXmlOpenId,0);
  if(m_enable == NR_E_NORMAL) {
    std::cout << "move has been paused!" << std::endl;
    return 0;
  } else {
    std::cout << "pause fail!" << std::endl;
    return -1;
  }
}

/**
  * @brief      stop the robot suddenly
  * @param[in]  value 1 pause suddenly,0 remove pause suddenly
  * @return     0:success,-1:fail
  */ 
int32_t Robot::SetSuddenlyStop(bool value) {
  int nErr = NR_AcsGeneralOutputSignal(nXmlOpenId, &value, true, 2, 1);
  if(NR_E_NORMAL == nErr) {
    if (value) {
      std::cout << "stop suddenly success!" << std::endl;
    } else {
      std::cout << "remove stop suddenly success!" << std::endl;
    }
    return 0;
  } else {
    std::cout << "get failed:" << nErr << std::endl;
    return -1;
  }
}

/**
  * @brief      move by x y z roll pitch yaw
  * @param[in]  
  * @return     0:success,-1:fail
  */ 
int32_t Robot::MoveJX(NR_POSE pose) {
  if(m_enable) {
    m_enable = NR_CtrlMotor(nXmlOpenId,1);
    sleep(3);
  }
  int speed = 30;
  NR_AcsRecordSpeed(nXmlOpenId,&speed,true);
  float fExtPos[1];
  memset(fExtPos,0,sizeof(fExtPos));
  int32_t nErr = -1;
  if(m_enable == NR_E_NORMAL) {
    nErr = NR_CtrlMoveX(nXmlOpenId, &pose, 1, 1, 0, fExtPos, EXT_AXIS);
  }
  int value = 1;
  NR_AcsInterpolationKind(nXmlOpenId,&value,true);
  NR_AcsInterpolationKind(nXmlOpenId,&value,false);
  return nErr;
}

/**
  * @brief      
  * @param[in]  
  * @return     0:success,-1:fail
  */ 
int32_t Robot::MoveAX(float angelsArray[6]) {
  if(m_enable) {
    m_enable = NR_CtrlMotor(nXmlOpenId,1);
    sleep(5);
  }
  int nErr = NR_CtrlMoveJ(nXmlOpenId,angelsArray,6,2);
  if(NR_E_NORMAL == nErr) {
    std::cout << "change angel success!" << std::endl;
    return 0;
  } else {
    std::cout << "change angel fail!" << std::endl;
    return -1;
  }
}

/**
  * @brief      get robot speed 
  * @param[out] value speed  
  * @return     0:success,-1:fail
  */ 
int32_t Robot::GetSpeed(int &value) {
  int nErr = NR_AcsManualSpeed(nXmlOpenId,&value,false);
  if(NR_E_NORMAL == nErr) {
    std::cout << "robot speed:" << value << std::endl;
    return 0;
  } else {
    std::cout << "get failed:" << nErr << std::endl;
    return -1;
  }
}

/**
  * @brief      get 6 axis electric
  * @param[out] values 6 axis electric
  * @return     0:success,-1:fail
  */ 
int32_t Robot::GetElectric(float values[6]) {
  int nErr = NR_AcsAxisAmpValue(nXmlOpenId,values,1,6);
  if(NR_E_NORMAL == nErr) {
    std::cout << "robot electric:" << values[0] << "," << values[1] << ","<< values[2] << ","<< values[3] << ","<< values[4] << ","<< values[5] << std::endl;
    return 0;
  } else { 
    std::cout << "get failed:" << nErr << std::endl;
    return -1;
  }
}

/**
  * @brief      get 6 axis angel
  * @param[out] values 6 axis angel  
  * @return     0:success,-1:fail
  */ 
int32_t Robot::GetAxisAngel(float values[6]) {
  int nErr = NR_AcsAxisTheta(nXmlOpenId,values,1,6);
  if(NR_E_NORMAL == nErr) {
    std::cout << "robot angel:" << values[0] << "," << values[1] << ","<< values[2] << ","<< values[3] << ","<< values[4] << ","<< values[5] << std::endl;
    return 0;
  } else { 
    std::cout << "get failed:" << nErr << std::endl;
    return -1;
  }
}

/**
  * @brief      get robot pose
  * @param[out] values robot pose
  * @return     0:success,-1:fail
  */ 
int32_t Robot::GetAxisPos(float values[6]) {
  int nErr = NR_AcsToolTipPos(nXmlOpenId,values,1,6);
  if(NR_E_NORMAL == nErr) {
    //std::cout << "robot pose:" << values[0] << "," << values[1] << ","<< values[2] << ","<< values[3] << ","<< values[4] << ","<< values[5] << std::endl;
    return 0;
  } else { 
    //std::cout << "get failed:" << nErr << std::endl;
    return -1;
  }
}

/**
  * @brief      get motors io state
  * @param[out] value true:on false:off
  * @return     0:success,-1:fail
  */ 
int32_t Robot::GetIOMotorsOnLAMP(bool &value) {
  int nErr = NR_AcsFixedIOMotorsOnLAMP(nXmlOpenId, &value);
  if(NR_E_NORMAL == nErr) {
    std::cout << "motors IO state:" << value << std::endl;
    return 0;
  } else {
    std::cout << "get failed:" << nErr << std::endl;
    return -1;
  }
}

/**
  * @brief      Check whether the target point have reached
  * @param[in]  pose target pose
  * @return     true:reached false:not reached
  */ 
bool Robot::IsMoveEnd(NR_POSE pose) {
  clock_t start_time,end_time,timer;
  start_time = clock();
  while (true) {
    float curr_pose[6];
    GetAxisPos(curr_pose);
    end_time = clock();
    timer = std::abs((double)(end_time - start_time)) / 1000;
    if (std::abs(curr_pose[0] - pose.fX) <= 1 && std::abs(curr_pose[1] - pose.fY) <= 1 && std::abs(curr_pose[2] - pose.fZ) <= 1 &&
        std::abs(curr_pose[3] - pose.fRoll) <= 1 && std::abs(curr_pose[4] - pose.fPitch) <= 1 && std::abs(curr_pose[5] - pose.fYaw) <= 1) {
      std::cout << "timer:" << timer << "ms" << std::endl;
      return true;
    } else if (timer >= 8000) {
      return false;
    }
    // std::cout << "timer:" << timer << std::endl;
    // std::cout << "X:" << curr_pose[0] << std::endl;
    // std::cout << "Y:" << curr_pose[1] << std::endl;
    // std::cout << "Z:" << curr_pose[2] << std::endl;
  }
}

/**
  * @brief      move robot to grab every target
  * @param[in]  points target points
  * @param[in]  angles target angles,with the x-axis
  * @param[in]  ctx    modbus handle
  * @return     target count
  */ 

int32_t Robot::GrabTargets(std::vector<cv::Point3f> points, std::vector<float> angles, std::vector<std::string> targets_name, Hand &hand,modbus_t* ctx) {
  NR_POSE pose = {136.87f, -0.00f, 709.21f, 0.00f, 0.00f, 180.0f};
  NR_POSE temp_pose = {330.00f, 200.00, 630.00f, 0.00f, 0.00f, 180.0f};
  NR_POSE origin_pose = {136.87f, -0.00f, 709.21f, 0.00f, 0.00f, 180.0f};
  NR_POSE put_pose[6];
  unsigned long long int counts[6] = {0,0,0,0,0,0};
  put_pose[0] = {550.00f,222.0f,460.0f,90.0f,0.00f,180.0f};
  put_pose[1] = {470.00f,222.0f,460.0f,90.0f,0.00f,180.0f};
  put_pose[2] = {390.00f,222.0f,460.0f,90.0f,0.00f,180.0f};
  put_pose[3] = {310.00f,222.0f,460.0f,90.0f,0.00f,180.0f};
  put_pose[4] = {230.00f,222.0f,460.0f,90.0f,0.00f,180.0f};
  put_pose[5] = {150.00f,222.0f,460.0f,90.0f,0.00f,180.0f};
  for (int i = 0; i < points.size(); i++) {
    pose.fX = points[i].x + X_OFFSET;
    pose.fY = points[i].y + Y_OFFSET;
    pose.fZ = 460;
    pose.fRoll = angles[i];

    // move and close the hand
    MoveJX(pose);
    if (IsMoveEnd(pose)) {
      int ret = hand.Write(ctx,0x0002,0);
      if(ret<0){
        printf("write hand failed!\r\n");
      }
    }
    delay_ms(600);

    // move to temp pose
    MoveJX(temp_pose);
    IsMoveEnd(temp_pose);

    // move to put pose
    int index = 5;
    std::cout << "class name: " << targets_name[i] << std::endl;
    if (targets_name[i] == "red-rect") {
      index = 0;
    } else if (targets_name[i] == "blue_cube") {
      index = 1;
    } else if (targets_name[i] == "yellow-tri") {
      index = 2;
    } else if (targets_name[i] == "green") {
      index = 3;
    } else if (targets_name[i] == "red_circle") {
      index = 4;
    } else if (targets_name[i] == "none") {
      index = 5;
    }
    put_pose[index].fZ = 460.0 + 9 * counts[index];
    counts[index]++;
    MoveJX(put_pose[index]);
    if (IsMoveEnd(put_pose[index])) {
      hand.Initialization(ctx,0x0000);
      sleep(1);
      MoveJX(temp_pose);
      IsMoveEnd(temp_pose);
      if (i == points.size() - 1) {
        MoveJX(origin_pose);
        IsMoveEnd(origin_pose);
      }
    }
  }
}

/**
  * @brief      delay
  * @param[in]  ms
  */ 
 void Robot::delay_ms(int ms) {
   clock_t start = clock();
   while ((double)(clock() - start) / 1000  < ms);
 }