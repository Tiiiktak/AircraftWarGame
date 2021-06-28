#pragma once
#include "MyTool.h"
#include "CAirPlane.h"
#include "CMouseControl.h"

// ��ҷɻ��࣬�̳��Էɻ�����

class CPlayer :
	public CAirPlane
{
private:
	bool m_isUpdate; // ��ǰ�Ƿ�����
	void Update(); //�����ɻ�

	clock_t time_point; 
	void CreateBullet(); // �����ӵ�
	void DeleteBullet(); // ɾ���ӵ�
	cv::Mat DrawBullet(cv::Mat& back); // ���ӵ� 
public:
	CPlayer(int plane_type); 
	~CPlayer();
	void Move(); // �ƶ�����
	cv::Mat Draw(cv::Mat& back); // ����
	int getHP(); // ����HP
	std::vector<CBullet*> getBulletsVec(); // �����ӵ�
	void plusValue(int t); // �ӷ� 
	int getValue(); // ��ȡ����
	cv::Rect getPositionRect();
	void LossBlood(int loss); //��Ѫ
};

