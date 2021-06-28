#include "CMouseControl.h"
using namespace cv;

Point MOUSE_POSITION = Point(0, 0);
bool MOUSE_CLICK = false;

void CMouseControl::onMouseMove(int event, int x, int y, int flags, void* userdata)
{
	CMouseControl* self = (CMouseControl*)userdata;
	switch (event)
	{
	case EVENT_MOUSEMOVE: // 鼠标移动
		MOUSE_POSITION = Point(x, y);
		break;
	case EVENT_LBUTTONDOWN: // 左键按下
		MOUSE_CLICK = true;
		break;
	case EVENT_LBUTTONUP: // 左键放开
		MOUSE_CLICK = false;
		break;
	}
	if (event == EVENT_MOUSEMOVE) 
	{
		MOUSE_POSITION = Point(x, y);
	}
}


CMouseControl::CMouseControl(std::string winname)
{
	m_windowName = winname;
	setMouseCallback(m_windowName, onMouseMove, this);
}

CMouseControl::~CMouseControl()
{
	setMouseCallback(m_windowName, NULL, NULL);
}

/*
#define CV_EVENT_MOUSEMOVE 0			滑动
#define CV_EVENT_LBUTTONDOWN 1			左键点击
#define CV_EVENT_RBUTTONDOWN 2          右键点击
#define CV_EVENT_MBUTTONDOWN 3          中键点击
#define CV_EVENT_LBUTTONUP 4            左键放开
#define CV_EVENT_RBUTTONUP 5            右键放开
#define CV_EVENT_MBUTTONUP 6            中键放开
#define CV_EVENT_LBUTTONDBLCLK 7        左键双击
#define CV_EVENT_RBUTTONDBLCLK 8        右键双击
#define CV_EVENT_MBUTTONDBLCLK 9        中键双击
*/