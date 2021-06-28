#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>

extern cv::Point MOUSE_POSITION; // ���ļ�ȫ�ֱ������������
extern bool MOUSE_CLICK; // �����

class CMouseControl
{
private:
	static void onMouseMove(int event, int x, int y, 
		int flags, void* userdata);
	std::string m_windowName; // ��������
public:
	CMouseControl(std::string winname);
	~CMouseControl();
};

