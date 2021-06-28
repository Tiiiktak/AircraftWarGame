#pragma once
#include "MyTool.h"

// 子弹
class CBullet
{
private:
	cv::Mat m_bulletImg; // 子弹图片
	cv::Point m_Position; // 当前坐标
	cv::Point max_Position; // 最大坐标
	int m_width, m_height; // 子弹宽高
	int m_fromType; // 子弹来源（1-3玩家，0-敌机）
	int m_Attack; // 攻击强度
	void running(); // 子弹运动
public:
	bool m_isOut; // 子弹是否结束生命
	CBullet(int type, cv::Point start_position, int attack);
	CBullet(cv::Mat bullet, int type, cv::Point start_position, int attack);
	~CBullet(); 
	cv::Mat Draw(cv::Mat& back); // 画子弹
	cv::Mat getBulletImg(); // 获取子弹img
	cv::Rect getPositionRect(); // 获取子弹当前rect
};

