#pragma once
#include "MyTool.h"
#include "CMouseControl.h"

//结算
class CEndUI
{
private:
	std::string m_windowName; // 窗口名
	cv::Mat* m_backgroundImg; // 首页背景图片
	cv::Mat* m_runningBack; // imshow用的变化图片
	int width, height; // 背景图宽高
	cv::Mat* m_girlImg; // 女孩图片
	cv::Mat* m_baseMap; // 得分背景
	std::vector<cv::Mat*> m_NumScore; // 得分数字
	std::vector<cv::Mat*> m_TitleImg; // 标语
	cv::Mat* m_sureBtnImg; // 确定
	int m_playerScore, m_maxScore; 
	std::vector<cv::Point> m_numPos; // 6个数字的坐标
	cv::Mat Numrunning(cv::Mat& back);
	clock_t begin_time;
	bool m_explodeFlag, m_titleFlag; 
	cv::Mat Titlerunning(cv::Mat& back); // 称号
public:
	CEndUI(int player_score, int max_score); 
	~CEndUI();
	void Settlement(); // 结算
};

