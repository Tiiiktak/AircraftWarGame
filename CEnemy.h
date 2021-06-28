#pragma once
#include "CAirPlane.h"
class CEnemy :
	public CAirPlane
{
private:
	bool m_isBoss; // 是否是boss

	clock_t time_point;
	void CreateBullet(); // 创建子弹
	void DeleteBullet(); // 删除子弹
	cv::Mat DrawBullet(cv::Mat& back); // 画子弹 
public:
	CEnemy(int enemy_type, int start_x);
	~CEnemy(); 
	void Move(); 
	cv::Mat Draw(cv::Mat& back); // 绘制 
		// 检查玩家子弹
	int CheckPlayerBullets(std::vector<CBullet*> player_bullets);
	int CheckPlayer(cv::Rect player_rect); // 检查玩家
	int getBulletsSize(); // 获取子弹数量
};

