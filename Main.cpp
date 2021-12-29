#include "Camera.h"

Camera camera;

void on_mouse(int event, int x, int y, int flags, void* ustc) {
	if (event == CV_EVENT_LBUTTONDOWN) {
    cv::Point3f p_w = camera.Pixel2World(cv::Point2f(x,y));
    printf("image point x:%d,y:%d\r\n",x,y);
    printf("world point x:%f,y:%f,z:%f \r\n",p_w.x,p_w.y,p_w.z);
	}
}

int main() {
  //open camera
  std::cout << "Tip: insure your camera is connected success!" << std::endl;
  if (camera.Open() == 0) {
    std::cout << "open camra success!" << std::endl;
  } else {
    std::cout << "open camra fail!" << std::endl;
    return -1;
  }
  int key = 0;
  cv::namedWindow("show",CV_WINDOW_NORMAL);
  cvSetMouseCallback("show", on_mouse, 0);//关键内置函数
  std::cout << "click image firstly and enter cmds:" << std::endl;
  std::cout << "i: find corner image and save it in ./images,insure have 12 imgs is saved in ./images for calibrate internal param" << std::endl;
  std::cout << "s: save an image (named RT.jpg)" << std::endl;
  std::cout << "1: calibrate internal param" << std::endl;
  std::cout << "2: calibrate external param" << std::endl;
  std::cout << "ESC: quit" << std::endl;
  while (key != 27) {
    cv::Mat image = camera.Grab(true);
    cv::imshow("show",image);
    if (key == 'i') {
      if (camera.internal_param_calibrate_.FindCornerImage(image)) {
        cv::imshow("show",image);
        std::cout << "Enter any key(but cmds) to continue" << std::endl;
        key = cv::waitKey(0);
      } else {
        printf("find no corners\r\n");
      }
    } else if (key == 's') {
      cv::imwrite("./images/RT.jpg",image);
    } else if (key == '1') {
      camera.internal_param_calibrate_.StartCalibrate();
      std::cout << "internal param is calibrated success,saved in ./config/CameraMatrix.txt & DistCoeffs.txt" << std::endl;
    } else if (key == '2') {
      camera.external_param_calibrate_.StartCalibrate();
      std::cout << "external param is calibrated success,saved in ./config/Rt.txt" << std::endl;
    }
    key = cv::waitKey(1);
  }
  camera.Close();
  return 0;
}