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
  // test
  // camera.external_param_calibrate_.StartCalibrate();
  // std::cout << "test" << std::endl;
  // std::cout << " Camera_matrix_:" << camera.internal_param_calibrate_.camera_matrix_ << std::endl;
  // std::cout << " dist_coeffs_:" << camera.internal_param_calibrate_.dist_coeffs_ << std::endl;
  // std::cout << " r_mat_:" << camera.external_param_calibrate_.r_mat_ << std::endl;
  // std::cout << " tvec_:" << camera.external_param_calibrate_.tvec_ << std::endl;
  camera.Open();//open camera
  int key = 0;
  cv::namedWindow("show",CV_WINDOW_NORMAL);
  cvSetMouseCallback("show", on_mouse, 0);//关键内置函数
  while (key != 27) {
    cv::Mat image = camera.Grab(true);
    cv::imshow("show",image);
    if (key == 'i') {
      if (camera.internal_param_calibrate_.FindCornerImage(image)) {
        cv::imshow("show",image);
        key = cv::waitKey(0);
      } else {
        printf("find no corners\r\n");
      }
    } else if (key == 's') {
      static int count = 1;
      std::string file_name = "./images/Image";
      file_name.append(std::to_string(count).append(".jpg"));
      cv::imwrite(file_name,image);
      count++;
    } else if (key == 'g') {
      camera.internal_param_calibrate_.StartCalibrate();
      camera.external_param_calibrate_.StartCalibrate();
    }
    key = cv::waitKey(1);
  }
  camera.Close();
  return 0;
}