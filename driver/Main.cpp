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
  if (camera.Open() == 0) {
    std::cout << "open camra success!" << std::endl;
  };//open camera
  int key = 0;
  cv::namedWindow("show",CV_WINDOW_NORMAL);
  cvSetMouseCallback("show", on_mouse, 0);//关键内置函数
  while (key != 27) {
    cv::Mat image = camera.Grab(true);
    //cv::Mat image = cv::imread("./images/RT.jpg");
    cv::imshow("show",image);
    if (key == 'i') {
      if (camera.internal_param_calibrate_.FindCornerImage(image)) {
        cv::imshow("show",image);
        key = cv::waitKey(0);
      } else {
        printf("find no corners\r\n");
      }
    } else if (key == 's') {
      cv::imwrite("./images/RT.jpg",image);
    } else if (key == 'g') {
      camera.internal_param_calibrate_.StartCalibrate();
      camera.external_param_calibrate_.StartCalibrate();
    }
    key = cv::waitKey(1);
  }
  camera.Close();
  return 0;
}