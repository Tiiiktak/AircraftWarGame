#include "CEnemy.h"
using namespace cv;

void CEnemy::CreateBullet()
{
	if (m_isClear)
		return;
	auto temp = clock();
	if (temp - time_point > 2000)
	{
		int k, i = 1;
		if (m_type <= 5)
			// 一发子弹
			k = 1;
		else if (m_type <= 7)
			// 两发子弹
			k = 2;
		else
		{	//  boss,五发子弹
			k = 5;
			i = 1;
		}
		for (; i <= k; i++)
		{
			Point pos = Point(m_Position.x + i * m_bulletSpace, m_Position.y);
			CBullet* bt;
			if (m_bullets.size() == 0)
				bt = new CBullet(m_type, pos, m_Attack);
			else
				bt = new CBullet(m_bullets[0]->getBulletImg(), m_type, pos, m_Attack);
			m_bullets.push_back(bt);
		}
		time_point = temp;
	}
}

void CEnemy::DeleteBullet()
{
	std::vector<CBullet*>::iterator iter = m_bullets.begin();
	for (; iter != m_bullets.end(); )
	{
		if ((*iter)->m_isOut)
		{
			delete (*iter);
			iter = m_bullets.erase(iter);
		}
		else
			iter++;
	}
}

cv::Mat CEnemy::DrawBullet(cv::Mat& back)
{
	Mat temp = back.clone();
	std::vector<CBullet*>::iterator iter = m_bullets.begin();
	for (; iter != m_bullets.end(); iter++)
	{
		temp = (*iter)->Draw(temp);
	}
	return temp;
}

CEnemy::CEnemy(int enemy_type, int start_x)
{
	Mat all_enemy = imread("./images/plane_enemy.png", -1);
	Mat all_boss = imread("./images/plane_boss.png", -1);
	Mat plane; 
	switch (enemy_type)
	{
	// 1-3是玩家,
	// 4-5是单子弹（1血）
	case 4: // x-(277-347);y-(551-613)
		plane = all_enemy(Rect(277, 551, 70, 62));
		break;
	case 5: // x-(161-264);y-(474-548)
		plane = all_enemy(Rect(161, 474, 103, 74));
		break;
	// 6-7是双子弹（2血
	case 6: // x-(1-102);y-(483-557)
		plane = all_enemy(Rect(1, 483, 101, 74));
		break;
	case 7: // x-(367-479);y-(440-520)
		plane = all_enemy(Rect(367, 440, 112, 80));
		break;
	// 8-9是boss，五子弹（5血）
	case 8: // x-(6-453);y-(691-1024
		plane = all_boss(Rect(6, 691, 447, 328));
		resize(plane, plane, Size(plane.cols * 0.5, plane.rows * 0.5));
		break;
	case 9: // x-(455-1023);y-(655-1024)
		plane = all_boss(Rect(455, 655, 568, 368));
		resize(plane, plane, Size(plane.cols * 0.5, plane.rows * 0.5));
		break;
	}
	m_planeMats.push_back(plane);
	m_nowPlane = 0;
	m_type = enemy_type;
	m_isClear = false;
	m_width = m_planeMats[m_nowPlane].cols;
	m_height = m_planeMats[m_nowPlane].rows;
	m_Position = Point(start_x, 0);
	max_Position = Point(407 - m_width, 685 - m_height);
	m_isClear = false;

	switch (enemy_type)
	{
	case 4:
	case 5:
		m_isBoss = false;
		m_Blood = 4;
		m_Attack = 1;
		m_Value = 100;
		m_bulletSpace = m_width / 2; 
		break;
	case 6:
	case 7:
		m_isBoss = false;
		m_Blood = 8;
		m_Attack = 1;
		m_Value = 300;
		m_bulletSpace = m_width / 3;
		break;
	case 8:
	case 9:
		m_isBoss = true;
		m_Blood = 16;
		m_Attack = 2;
		m_Value = 1000;
		m_bulletSpace = m_width / 6;
		break;
	}
	time_point = clock();
}

CEnemy::~CEnemy()
{
	m_planeMats.clear();
	m_bullets.clear();
}

void CEnemy::Move()
{
	if (m_isBoss)
		m_Position.y++;
	else
		m_Position.y += 2;
	if (m_Position.x <= 0 || m_Position.x >= max_Position.x
		|| m_Position.y <= 0 || m_Position.y >= max_Position.y)
		m_isClear = true;
}

cv::Mat CEnemy::Draw(cv::Mat& back)
{
	Move();
	// 子弹
	CreateBullet();
	DeleteBullet();
	Mat temp = DrawBullet(back);

	if (m_isClear)
	{
		return temp;
	}
	// 调用函数绘制
	Mat plane = m_planeMats[m_nowPlane].clone();
	temp = CopyRGBA2BGR(plane, temp, m_Position, 1);

	return temp;
}

int CEnemy::CheckPlayerBullets(std::vector<CBullet*> player_bullets)
{
	int player_get = 0;
	std::vector<CBullet*>::iterator iter = player_bullets.begin();
	for (; iter != player_bullets.end(); iter++)
	{
		Rect me_rect = Rect(m_Position.x, m_Position.y, m_width, m_height);
		Rect bullet_rect = (*iter)->getPositionRect();
		if (checkRectCont(me_rect, bullet_rect)) // 两者相交，则敌人（自己）被击中
		{
			PlayBullet(1);
			m_Blood--;
			(*iter)->m_isOut = true;
			if (m_Blood == 0)
			{
				m_isClear = true;
				player_get = m_Value;
				PlayEffect(1);
				break;
			}
		}
	}
	return player_get;
}

int CEnemy::CheckPlayer(cv::Rect player_rect)
{
	int player_loss = 0;
	// 由于飞机边缘不规则，直接用矩形判断相撞容易误判，因此取消
	//Rect me_rect = Rect(m_Position.x, m_Position.y, m_width, m_height);
	//if (!m_isClear && checkRectCont(me_rect, player_rect)) // 敌机与玩家相撞
	//{
	//	m_Blood = 0;
	//	player_loss = m_Attack;
	//}
	std::vector<CBullet*>::iterator iter = m_bullets.begin();
	for (; iter != m_bullets.end(); iter++)
	{
		Rect bullet_rect = (*iter)->getPositionRect();
		if (checkRectCont(player_rect, bullet_rect)) // 飞机被敌机子弹击中
		{
			(*iter)->m_isOut = true;
			player_loss += m_Attack; // 玩家收到伤害
		}
	}
	return player_loss;
}

int CEnemy::getBulletsSize()
{
	return m_bullets.size();
}
