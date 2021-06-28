#pragma once
#include "MyTool.h"

// �ӵ�
class CBullet
{
private:
	cv::Mat m_bulletImg; // �ӵ�ͼƬ
	cv::Point m_Position; // ��ǰ����
	cv::Point max_Position; // �������
	int m_width, m_height; // �ӵ����
	int m_fromType; // �ӵ���Դ��1-3��ң�0-�л���
	int m_Attack; // ����ǿ��
	void running(); // �ӵ��˶�
public:
	bool m_isOut; // �ӵ��Ƿ��������
	CBullet(int type, cv::Point start_position, int attack);
	CBullet(cv::Mat bullet, int type, cv::Point start_position, int attack);
	~CBullet(); 
	cv::Mat Draw(cv::Mat& back); // ���ӵ�
	cv::Mat getBulletImg(); // ��ȡ�ӵ�img
	cv::Rect getPositionRect(); // ��ȡ�ӵ���ǰrect
};

