#pragma once
#include "MyTool.h"
#include "CMouseControl.h"

//����
class CEndUI
{
private:
	std::string m_windowName; // ������
	cv::Mat* m_backgroundImg; // ��ҳ����ͼƬ
	cv::Mat* m_runningBack; // imshow�õı仯ͼƬ
	int width, height; // ����ͼ���
	cv::Mat* m_girlImg; // Ů��ͼƬ
	cv::Mat* m_baseMap; // �÷ֱ���
	std::vector<cv::Mat*> m_NumScore; // �÷�����
	std::vector<cv::Mat*> m_TitleImg; // ����
	cv::Mat* m_sureBtnImg; // ȷ��
	int m_playerScore, m_maxScore; 
	std::vector<cv::Point> m_numPos; // 6�����ֵ�����
	cv::Mat Numrunning(cv::Mat& back);
	clock_t begin_time;
	bool m_explodeFlag, m_titleFlag; 
	cv::Mat Titlerunning(cv::Mat& back); // �ƺ�
public:
	CEndUI(int player_score, int max_score); 
	~CEndUI();
	void Settlement(); // ����
};

