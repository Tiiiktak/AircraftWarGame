#pragma once
#include <vector>
#include "CPlayer.h"
#include "MyTool.h"

class CScenes
{
private:
	std::vector<cv::Mat> m_levelBackImg; // ս������������ȼ���
	cv::Mat m_runningImg; // �˶�ͼ��imshow�ã�
	int m_nowLevel; // ��ǰ�ȼ�

	int m_runflag; // ʹ��ͼ�ƶ�����
	int m_runDis; // ��¼��ͼ�ƶ�
	void running(); 
public:
	CScenes(); 
	~CScenes();
	cv::Mat CreateBackGround();
};

