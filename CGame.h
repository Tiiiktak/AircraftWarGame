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
	std::string m_windowName; // ������
	CScenes* m_scenes; // ����
	CPlayer* m_player; // ���
	std::vector<CEnemy*> m_enemys; //�л�

	void CreateEnemy(); // ��������
	void DeleteEnemy();
	cv::Mat DrawEnemy(cv::Mat& back); // ���л�
	void CheckAttackEnemy(); // �������л�
	void CheckAttackPlayer(); // �������

	cv::Mat* m_suspendBtnImg; // ��ͣ��ť
	cv::Mat DrawSuspendBtn(cv::Mat& back); // ����ͣ��
	std::vector<cv::Mat*> m_hpImgs; // Ѫ��vec
	cv::Mat DrawHP(cv::Mat& back); // ��HP��
	int m_plusScoreFlag;
	std::vector<cv::Mat*> m_NumScore; // �÷�����
	cv::Mat DrawScore(cv::Mat& back); // ���÷�
	cv::Mat DrawUI(cv::Mat& back); // ����UI
	cv::Mat* m_continueGameBtnImg; // ������Ϸ��ť
	cv::Mat* m_backMenuBtnImg; // �������˵���ť
	cv::Mat* m_go2EndBtnImg; // ֱ�ӽ���
	int PauseUI(cv::Mat& back, bool flag = 0); // ��ͣ����
	int m_finallyScore; // ���շ���
public:
	CGame(int player_type);
	~CGame(); 
	int RunGame(); // ��ʼ��Ϸ��0�������¿�ʼ
};

