#include "CBullet.h"
using namespace cv; 

void CBullet::running()
{
	if (m_fromType >= 1) // 玩家的子弹，向上运动y--
		m_Position.y -= 6;
	else if (m_Attack == 1)
	{		
		m_Position.y += 4; // 敌机子弹，向下运动
	}
	else
	{
		m_Position.y += 2; // boss子弹
	}
	if (m_Position.y <= 0 || m_Position.y >= max_Position.y)
		m_isOut = true;
}

CBullet::CBullet(int type, cv::Point start_position, int attack)
{
	Mat all_bullet = imread("./images/img_bullet.png", -1);
	switch (type)
	{
	case 1: //x-(213-243),y-(232-414)
		m_bulletImg = all_bullet(Rect(213, 232, 30, 182));
		resize(m_bulletImg, m_bulletImg,
			Size(m_bulletImg.cols * 0.8, m_bulletImg.rows * 0.8));
		break;
	case 2: // x-(429-492),y-(637-784)
		m_bulletImg = all_bullet(Rect(429, 637, 63, 147));
		resize(m_bulletImg, m_bulletImg,
			Size(m_bulletImg.cols * 0.8, m_bulletImg.rows * 0.8));
		break;
	case 3: //x-(59-87),y-(480,670) 
		m_bulletImg = all_bullet(Rect(59, 480, 28, 90));
		break; 
	// 敌机的子弹
	case 4:
	case 5: // x(715-760);y(200,257)
		m_bulletImg = all_bullet(Rect(715, 200, 45, 57));
		flip(m_bulletImg, m_bulletImg, 0);
		// 待翻转
		break;
	case 6: // x(730-755);y(677-777)
	case 7: 
		m_bulletImg = all_bullet(Rect(730, 677, 25, 100));
		break;
	case 8: 
	case 9: // x(780-834);y-(482-532)
		m_bulletImg = all_bullet(Rect(780, 482, 54, 50));
		break;
	default:
		break;
	}
	resize(m_bulletImg, m_bulletImg, 
		Size(m_bulletImg.cols * 0.3, m_bulletImg.rows * 0.3));

	if (type <= 3)
		m_fromType = type;
	else
		m_fromType = 0;

	m_width = m_bulletImg.cols;
	m_height = m_bulletImg.rows;
	max_Position = Point(407 - m_width, 685 - m_height);
	m_Position.x = start_position.x - m_width / 2 < 0 ? 
		0 : start_position.x - m_width / 2;
	if (type <= 3)
	{
		m_fromType = type;
		// 玩家飞机给的初始坐标需要上移
		m_Position.y = start_position.y - m_height;
	}
	else 
	{
		m_fromType = 0;
		// 敌机给的初始坐标下移
		m_Position.y = start_position.y + m_height;
		if (m_Attack == 2) // boss
			m_Position.y += 50;
	}
	m_Attack = attack;
	m_isOut = false;
}

CBullet::CBullet(cv::Mat bullet, int type, cv::Point start_position, int attack)
{
	m_bulletImg = bullet.clone();
	if (type <= 3)
		m_fromType = type;
	else
		m_fromType = 0;

	m_width = m_bulletImg.cols;
	m_height = m_bulletImg.rows;
	max_Position = Point(407 - m_width, 685 - m_height);
	m_Position.x = start_position.x;
	if (type <= 3)
	{
		m_fromType = type;
		// 玩家飞机给的初始坐标需要上移
		m_Position.y = start_position.y - m_height;
	}
	else
	{
		m_fromType = 0;
		// 敌机给的初始坐标下移
		m_Position.y = start_position.y + m_height;
	}
	m_Attack = attack;
	m_isOut = false;
}

CBullet::~CBullet()
{
	m_bulletImg.release();
}

cv::Mat CBullet::Draw(cv::Mat& back)
{
	running();
	if (m_isOut)
		return back;
	Mat temp = CopyRGBA2BGR(m_bulletImg, back, m_Position, 1);

	return temp;
}

cv::Mat CBullet::getBulletImg()
{
	return m_bulletImg;
}

cv::Rect CBullet::getPositionRect()
{
	Rect temp = Rect(m_Position.x, m_Position.y, m_width, m_height);
	return temp;
}
