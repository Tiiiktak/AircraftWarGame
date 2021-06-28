#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "CMouseControl.h"
#include "CGame.h"
#include "MyTool.h"
#include "CEndUI.h"

extern cv::Point MOUSE_POSITION;

class CStartUI
{
private:
	std::string m_windowName; // 窗口名
	cv::Mat* m_logoImg; // logo图片(四通道)
	cv::Mat* m_harfBoardImg; // 背景板（上半部分）
	cv::Mat* m_startButtonImg; // 开始游戏
	cv::Mat* m_nextPlaneBtnImg; // 下一飞机按钮
	cv::Mat* m_backgroundImg; // 首页背景图片
	int width, height; // 背景图宽高
	cv::Mat* m_runningBack; // imshow用的变化图片
	void LogProgram(); // 程序启动
	void HomePage(); // 首页
	cv::Mat ChoosePlane(); // 选飞机
	int m_choosePlane; // 选中飞机编号0,1,2
	std::vector<cv::Mat> m_playerPlanes; // 玩家飞机选择
	bool DealMooseClick(); // 处理鼠标点击事件
	int m_recordingScore; // 历史记录
public:
	CStartUI();
	~CStartUI();
	void Run();
};

