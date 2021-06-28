#pragma once
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "CBullet.h"

// 飞机类，作为所有类型飞机基类
class CAirPlane
{
protected:
	std::vector<cv::Mat> m_planeMats; // 飞机Mat(多个)
	cv::Point m_Position; // 当前坐标
	cv::Point max_Position; // 最大坐标
	int m_nowPlane; // 当前飞机编号
	int m_type; // 飞机类型(1-3,玩家；0-敌机）
	int m_Blood; // 血量
	int m_Attack; // 攻击强度
	int m_Value; // 价值
	int m_width; // 飞机宽度
	int m_height; // 飞机高度

	int m_bulletSpace; // 同一排子弹间间距
	std::vector<CBullet*> m_bullets; // 子弹
	virtual void CreateBullet() = 0; // 创建子弹
	virtual void DeleteBullet() = 0; // 删除子弹
	virtual cv::Mat DrawBullet(cv::Mat& back) = 0; // 画子弹 
public:
	bool m_isClear; // 飞机是否被清除
	virtual void Move() = 0; // 移动函数
	virtual cv::Mat Draw(cv::Mat& back) = 0; // 绘制函数
	int getValue(); // 获取分数
};

