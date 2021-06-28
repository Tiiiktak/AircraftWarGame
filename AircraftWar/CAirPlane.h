#pragma once
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "CBullet.h"

// �ɻ��࣬��Ϊ�������ͷɻ�����
class CAirPlane
{
protected:
	std::vector<cv::Mat> m_planeMats; // �ɻ�Mat(���)
	cv::Point m_Position; // ��ǰ����
	cv::Point max_Position; // �������
	int m_nowPlane; // ��ǰ�ɻ����
	int m_type; // �ɻ�����(1-3,��ң�0-�л���
	int m_Blood; // Ѫ��
	int m_Attack; // ����ǿ��
	int m_Value; // ��ֵ
	int m_width; // �ɻ����
	int m_height; // �ɻ��߶�

	int m_bulletSpace; // ͬһ���ӵ�����
	std::vector<CBullet*> m_bullets; // �ӵ�
	virtual void CreateBullet() = 0; // �����ӵ�
	virtual void DeleteBullet() = 0; // ɾ���ӵ�
	virtual cv::Mat DrawBullet(cv::Mat& back) = 0; // ���ӵ� 
public:
	bool m_isClear; // �ɻ��Ƿ����
	virtual void Move() = 0; // �ƶ�����
	virtual cv::Mat Draw(cv::Mat& back) = 0; // ���ƺ���
	int getValue(); // ��ȡ����
};

