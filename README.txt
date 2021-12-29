使用方式：

本程序运行指令：在build下运行./calibrate

1.保证相机已经正常连接。本程序使用的是海康的彩色相机，可以使用自带软件MVS进行测试相机是否已经可以正常打开。相机软件安装在/opt/MVS/bin下，运行./MVS.sh
2.本程序打开后，会一直显示实时图片，用鼠标选中显示窗口后，再使用键盘输入相关指令进行操作，指令如下：
i:判断当前照片是否合格（Size: 11 * 8）的棋盘格图像,如果合格，则对其进行保存（./images),用于后续的内参标定，建议保存图像不要少于12张
s:保存一张图片，并命名为RT.jpg。该功能可以用于外参标定，比如从该图片上选取4个控制点（角点），分别找到它们在像素坐标系和世界坐标系下的坐标，并将这些点记录到./config/InputPoints.txt下
1:执行内参标定操作
2:执行外参标定操作
ESC:退出

Instructions:
1. Ensure that the camera is properly connected. This program uses the color camera of Haikang, you can use your own software MVS to test whether the camera can be opened normally. Install the camera software in /opt/MVS/bin and run the./ mvs.sh command

2. After the program is opened, the real-time picture will always be displayed. Select the display window with the mouse, and then use the keyboard to enter relevant instructions for operation, as follows:

i: Checkerboard image to judge whether the current photo is qualified (Size: 11 * 8). If so, it will be saved (./images) for subsequent internal reference calibration. It is recommended to save no less than 12 images

s: Save an image and name it RT.jpg. This function can be used for calibration of external parameters. For example, select 4 control points (corner points) from the picture, find their coordinates in pixel coordinate system and world coordinate system respectively, and record these points in./config/ inputpoints.txt

1: perform internal parameter calibration operation

2: Perform external parameter calibration operation

ESC: quit

