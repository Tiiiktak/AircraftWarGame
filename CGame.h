#pragma once
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "CMouseControl.h"
#include "CScenes.h"
#include "CPlayer.h"
#include "CEnemy.h"

class CGame
{
private:
	std::string m_windowName; // 窗口名
	CScenes* m_scenes; // 背景
	CPlayer* m_player; // 玩家
	std::vector<CEnemy*> m_enemys; //敌机

	void CreateEnemy(); // 创建敌人
	void DeleteEnemy();
	cv::Mat DrawEnemy(cv::Mat& back); // 画敌机
	void CheckAttackEnemy(); // 检查清除敌机
	void CheckAttackPlayer(); // 攻击玩家

	cv::Mat* m_suspendBtnImg; // 暂停按钮
	cv::Mat DrawSuspendBtn(cv::Mat& back); // 画暂停键
	std::vector<cv::Mat*> m_hpImgs; // 血条vec
	cv::Mat DrawHP(cv::Mat& back); // 画HP条
	int m_plusScoreFlag;
	std::vector<cv::Mat*> m_NumScore; // 得分数字
	cv::Mat DrawScore(cv::Mat& back); // 画得分
	cv::Mat DrawUI(cv::Mat& back); // 绘制UI
	cv::Mat* m_continueGameBtnImg; // 继续游戏按钮
	cv::Mat* m_backMenuBtnImg; // 返回主菜单按钮
	cv::Mat* m_go2EndBtnImg; // 直接结算
	int PauseUI(cv::Mat& back, bool flag = 0); // 暂停界面
	int m_finallyScore; // 最终分数
public:
	CGame(int player_type);
	~CGame(); 
	int RunGame(); // 开始游戏（0代表重新开始
};

