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
	std::string m_windowName; // ������
	cv::Mat* m_logoImg; // logoͼƬ(��ͨ��)
	cv::Mat* m_harfBoardImg; // �����壨�ϰ벿�֣�
	cv::Mat* m_startButtonImg; // ��ʼ��Ϸ
	cv::Mat* m_nextPlaneBtnImg; // ��һ�ɻ���ť
	cv::Mat* m_backgroundImg; // ��ҳ����ͼƬ
	int width, height; // ����ͼ���
	cv::Mat* m_runningBack; // imshow�õı仯ͼƬ
	void LogProgram(); // ��������
	void HomePage(); // ��ҳ
	cv::Mat ChoosePlane(); // ѡ�ɻ�
	int m_choosePlane; // ѡ�зɻ����0,1,2
	std::vector<cv::Mat> m_playerPlanes; // ��ҷɻ�ѡ��
	bool DealMooseClick(); // ����������¼�
	int m_recordingScore; // ��ʷ��¼
public:
	CStartUI();
	~CStartUI();
	void Run();
};

