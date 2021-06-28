#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>

extern cv::Point MOUSE_POSITION; // 跨文件全局变量，鼠标坐标
extern bool MOUSE_CLICK; // 鼠标点击

class CMouseControl
{
private:
	static void onMouseMove(int event, int x, int y, 
		int flags, void* userdata);
	std::string m_windowName; // 窗口名字
public:
	CMouseControl(std::string winname);
	~CMouseControl();
};

