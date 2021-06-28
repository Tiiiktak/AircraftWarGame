#pragma once
#include "MyTool.h"
#include "CAirPlane.h"
#include "CMouseControl.h"

// 玩家飞机类，继承自飞机基类

class CPlayer :
	public CAirPlane
{
private:
	bool m_isUpdate; // 当前是否升级
	void Update(); //升级飞机

	clock_t time_point; 
	void CreateBullet(); // 创建子弹
	void DeleteBullet(); // 删除子弹
	cv::Mat DrawBullet(cv::Mat& back); // 画子弹 
public:
	CPlayer(int plane_type); 
	~CPlayer();
	void Move(); // 移动函数
	cv::Mat Draw(cv::Mat& back); // 绘制
	int getHP(); // 返回HP
	std::vector<CBullet*> getBulletsVec(); // 返回子弹
	void plusValue(int t); // 加分 
	int getValue(); // 获取分数
	cv::Rect getPositionRect();
	void LossBlood(int loss); //掉血
};

