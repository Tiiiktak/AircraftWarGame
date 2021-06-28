#pragma once
#include "CAirPlane.h"
class CEnemy :
	public CAirPlane
{
private:
	bool m_isBoss; // �Ƿ���boss

	clock_t time_point;
	void CreateBullet(); // �����ӵ�
	void DeleteBullet(); // ɾ���ӵ�
	cv::Mat DrawBullet(cv::Mat& back); // ���ӵ� 
public:
	CEnemy(int enemy_type, int start_x);
	~CEnemy(); 
	void Move(); 
	cv::Mat Draw(cv::Mat& back); // ���� 
		// �������ӵ�
	int CheckPlayerBullets(std::vector<CBullet*> player_bullets);
	int CheckPlayer(cv::Rect player_rect); // ������
	int getBulletsSize(); // ��ȡ�ӵ�����
};

