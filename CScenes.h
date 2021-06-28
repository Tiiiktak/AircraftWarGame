#pragma once
#include <vector>
#include "CPlayer.h"
#include "MyTool.h"

class CScenes
{
private:
	std::vector<cv::Mat> m_levelBackImg; // 战斗背景（五个等级）
	cv::Mat m_runningImg; // 运动图像（imshow用）
	int m_nowLevel; // 当前等级

	int m_runflag; // 使地图移动减速
	int m_runDis; // 记录地图移动
	void running(); 
public:
	CScenes(); 
	~CScenes();
	cv::Mat CreateBackGround();
};

