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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "MvCameraControl.h"

bool start_grab = false;
bool is_grab_finished = false;

/**
  * @brief      the thread for grab image
  * @param      p_user param of user,input to grab image thread
  */ 
void* GrabThread(void *p_user) {
  int n_ret = MV_OK;
  // ch:获取数据包大小 | en:Get payload size
  MVCC_INTVALUE stParam;
  memset(&stParam, 0, sizeof(MVCC_INTVALUE));
  n_ret = MV_CC_GetIntValue(((PUser*)p_user)->handle_, "PayloadSize", &stParam);
  if (MV_OK != n_ret) {
    printf("Get PayloadSize fail! n_ret [0x%x]\n", n_ret);
    return NULL;
  }

  MV_FRAME_OUT_INFO_EX stImageInfo = {0};
  memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
  unsigned char * pData = (unsigned char *)malloc(sizeof(unsigned char) * stParam.nCurValue);
  if (NULL == pData) {
    return NULL;
  }
  unsigned int nDataSize = stParam.nCurValue;
  while(true) {
    if(start_grab == false) {
      continue;
    }
    is_grab_finished = false;
    n_ret = MV_CC_GetOneFrameTimeout(((PUser*)p_user)->handle_, pData, nDataSize, &stImageInfo, 1000);
    if (n_ret == MV_OK) {
      ((PUser*)p_user)->image_ = cv::Mat(stImageInfo.nHeight,stImageInfo.nWidth,CV_8UC3,pData);
    } else {
      printf("No data[%x]\n", n_ret);
      continue;
    }
    start_grab = false;
    is_grab_finished = true;
 }
 free(pData);
 return 0;
}

/**
  * @brief      print device information
  * @param      pstMVDevInfo the pointer of pstMVDevInfo
  * @return     ture:print information success,false:the Pointer of pstMVDevInfo is NULL
  */ 
bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo) {
  if (NULL == pstMVDevInfo) {
    printf("The Pointer of pstMVDevInfo is NULL!\n");
    return false;
  }
  if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE) {
    int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
    int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
    int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
    int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

    // ch:打印当前相机ip和用户自定义名字 | en:print current ip and user defined name
    printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chModelName);
    printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
    printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
  } else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE) {
      printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chModelName);
      printf("UserDefinedName: %s\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
  } else {
      printf("Not support.\n");
  }
  return true;
}

/**
  * @brief      open the camera
  * @return     0:success,-1:fail
  */ 
int32_t Camera::Open() {
  int32_t n_ret = MV_OK;
  handle_ = NULL;
  MV_CC_DEVICE_INFO_LIST stDeviceList;
  MV_CC_DEVICE_INFO *pDeviceInfo;
  memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
  // enum device
  n_ret = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
  if (MV_OK != n_ret) {
    printf("MV_CC_EnumDevices fail! n_ret [%x]\n", n_ret);
  }
  if (stDeviceList.nDeviceNum > 0) {
    pDeviceInfo = stDeviceList.pDeviceInfo[0];
    if (NULL == pDeviceInfo) {
        return -1;
    } 
  } 

  // 选择设备并创建句柄
  // select device and create handle
  n_ret = MV_CC_CreateHandle(&handle_, pDeviceInfo);
  if (MV_OK != n_ret) {
      printf("MV_CC_CreateHandle fail! n_ret [%x]\n", n_ret);
      return -1;
  }

  // 打开设备
  // open device
  n_ret = MV_CC_OpenDevice(handle_);
  if (MV_OK != n_ret) {
      printf("MV_CC_OpenDevice fail! n_ret [%x]\n", n_ret);
  }

  // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
  if (stDeviceList.pDeviceInfo[0]->nTLayerType == MV_GIGE_DEVICE) {
      int nPacketSize = MV_CC_GetOptimalPacketSize(handle_);
      if (nPacketSize > 0) {
          n_ret = MV_CC_SetIntValue(handle_,"GevSCPSPacketSize",nPacketSize);
          if(n_ret != MV_OK) {
              printf("Warning: Set Packet Size fail n_ret [0x%x]!\n", n_ret);
          }
      } else {
          printf("Warning: Get Packet Size fail n_ret [0x%x]!\n", nPacketSize);
      }
  }

  // 设置触发模式为off
  // set trigger mode as off
  n_ret = MV_CC_SetEnumValue(handle_, "TriggerMode", 0);
  if (MV_OK != n_ret) {
      printf("MV_CC_SetTriggerMode fail! n_ret [%x]\n", n_ret);
  }

  // start grab image
  n_ret  = MV_CC_StartGrabbing(handle_);
  if (MV_OK != n_ret) {
    printf("MV_CC_StartGrabbing fail! n_ret_ [%x]\n", n_ret);
  }
  pthread_t nThreadID;
  p_user.handle_ = handle_;
  n_ret = pthread_create(&nThreadID, NULL, GrabThread, (void*)(&p_user));

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
  start_grab = true;
  while (is_grab_finished != true);
  cv::cvtColor(p_user.image_,image_,cv::COLOR_RGB2BGR);
  is_grab_finished = false;
  return image_;
}

/**
  * @brief      close the camera
  * @return     0:success,-1:fail
  */ 
int Camera::Close() {
  // 停止取流
  // end grab image
  int32_t n_ret = MV_CC_StopGrabbing(handle_);
  if (MV_OK != n_ret) {
    printf("MV_CC_StopGrabbing fail! nRet [%x]\n", n_ret);
  }

  // 关闭设备
  // close device
  n_ret = MV_CC_CloseDevice(handle_);
  if (MV_OK != n_ret) {
    printf("MV_CC_CloseDevice fail! nRet [%x]\n", n_ret);
  }

  // 销毁句柄
  // destroy handle
  n_ret = MV_CC_DestroyHandle(handle_);
  if (MV_OK != n_ret) {
    printf("MV_CC_DestroyHandle fail! nRet [%x]\n", n_ret);
  }
  return 0;
}

/**
  * @brief      transform the pixel point to camera point 
  * @param[in]  p_p pixel point
  * @return     camera point
  */ 
cv::Point3f Camera::Pixel2Camera(cv::Point2f p_p) {
  #if 1
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
    // std::cout << "camera_matrix_:" << internal_param_calibrate_.camera_matrix_ << std::endl;
    // std::cout << "in_matrix_inv:" << in_matrix_inv << std::endl;
    // std::cout << "r_mat_:" << external_param_calibrate_.r_mat_ << std::endl;
    // std::cout << "r_mat_inv:" << r_mat_inv << std::endl;
    // std::cout << "t:" << t << std::endl;
    cv::Mat right_matrix = r_mat_inv * in_matrix_inv * p_p_q;
    cv::Mat left_matrix = r_mat_inv * t;
    double depth = left_matrix.at<float>(2,0) / right_matrix.at<float>(2,0);
    cv::Point3f camera_p;
    camera_p.x = (p_p.x - cx) * depth / fx;
    camera_p.y = (p_p.y - cy) * depth / fy;
    camera_p.z = depth;
    return camera_p;
  #else
    cv::Mat k_mat = internal_param_calibrate_.camera_matrix_;
    cv::Mat r_mat = external_param_calibrate_.r_mat_;
    cv::Mat t = external_param_calibrate_.tvec_;
    cv::Mat p_uv = (cv::Mat_<float>(3,1) << p_p.x,p_p.y,1);
    cv::Mat p_c;
    std::vector<cv::Point3f> object_points;
    object_points.push_back(cv::Point3f(0.0f, 0.0f, 0.0f));  
    object_points.push_back(cv::Point3f(0.0f, 300.0f, 0.0f));  
    object_points.push_back(cv::Point3f(210.0f, 300.0f, 0.0f));  
    object_points.push_back(cv::Point3f(210.0f, 0.0f, 0.0f));  
    float sum_z = 0;
    for (unsigned int i = 0; i < object_points.size(); i++) {
      sum_z += object_points[i].x * r_mat.at<float>(2,0) + object_points[i].y * r_mat.at<float>(2,1) + object_points[i].z * r_mat.at<float>(2,2) + t.at<float>(2,0);
    }
    float zc = sum_z / object_points.size();
    std::cout << "zc:" << zc << std::endl;
    p_c = k_mat.inv() * p_uv * zc;
    cv::Point3f camera_p;
    camera_p.x = p_c.at<float>(0,0);
    camera_p.y = p_c.at<float>(1,0);
    camera_p.z = p_c.at<float>(2,0);
    std::cout << "p_c" << p_c << std::endl;
    return camera_p;
  #endif
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

/**
  * @brief      transform the pixel angle to world angle 
  * @param[in]  angle pixel angle
  * @return     angle under world coordinate system
  */ 
float Camera::PixelAngle2World(float angle) {
  angle += std::acos(external_param_calibrate_.r_mat_.at<float>(1,1));
  return angle;
}