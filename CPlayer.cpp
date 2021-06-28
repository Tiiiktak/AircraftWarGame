#include "CPlayer.h"
using namespace cv; 

void CPlayer::Update()
{
	m_isUpdate = true;
	m_nowPlane = 1;
	m_Attack = 1;
	m_Blood = 5;
	m_width = m_planeMats[m_nowPlane].cols;
	m_height = m_planeMats[m_nowPlane].rows;
	max_Position = Point(407 - m_width, 685 - m_height);
	//子弹
	m_bulletSpace = m_width / 4;
}

void CPlayer::CreateBullet()
{
	auto temp = clock();
	if (temp - time_point > 600)
	{
		int i, k;
		if (!m_isUpdate) // 未升级（2发子弹
		{
			i = 1;
			k = 2;
		}
		else // 升级（3发
		{
			i = 1;
			k = 3;
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
		//PlayBullet(m_type);
	}
}

void CPlayer::DeleteBullet()
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

Mat CPlayer::DrawBullet(Mat& back)
{
	Mat temp = back.clone();
	std::vector<CBullet*>::iterator iter = m_bullets.begin();
	for (; iter != m_bullets.end(); iter++)
	{
		if (!(*iter)->m_isOut)
			temp = (*iter)->Draw(temp);
	}
	return temp;
}

CPlayer::CPlayer(int plane_type)
{
	// 读入飞机图像
	Mat all_plane = imread("./images/plane_player.png", -1);
	Mat base, update;
	m_type = plane_type;
	switch (plane_type)
	{
	case 1:
		// base- x(0-125); y(90-170)
		// update- x(0-135); y(0-89)
		base = all_plane(Rect(0, 90, 125, 80));
		update = all_plane(Rect(0, 0, 135, 89));
		break;
	case 2:
		// base- x(0-109); y(266-349)
		// update- x(0-114); y(172-265)
		base = all_plane(Rect(0, 266, 109, 83));
		update = all_plane(Rect(0, 172, 114, 93));
		break;
	case 3:
		// base- x(111-213); y(292-369)
		// update- x(245-356); y(180-256)
		base = all_plane(Rect(111, 292, 102, 77));
		update = all_plane(Rect(245, 180, 111, 76));
		break;
	default:
		break;
	}
	resize(base, base, Size(base.cols * 0.8, base.rows * 0.8));
	resize(update, update, Size(update.cols * 0.8, update.rows * 0.8));
	m_Value = 0;
	m_nowPlane = 0; 
	m_planeMats.push_back(base);
	m_planeMats.push_back(update);
	m_width = base.cols; 
	m_height = base.rows;
	m_isUpdate = false;
	m_isClear = false;
	m_Blood = 5; // 玩家5滴血
	m_Attack = 1; // 攻击强度1（敌机小兵生命1）
	m_Position = Point(203 - m_width / 2, 600 - m_height); //背景图：407 x 685
	max_Position = Point(407 - m_width, 685 - m_height);

	m_bulletSpace = m_width / 3;
	time_point = clock();
}

CPlayer::~CPlayer()
{
	m_planeMats.clear();
	m_bullets.clear();
}

Mat CPlayer::Draw(cv::Mat& back)
{
	Move();
	Mat plane = m_planeMats[m_nowPlane].clone();
	// 调用函数绘制
	Mat temp = CopyRGBA2BGR(plane, back, m_Position, 1);
	// 子弹
	CreateBullet();
	DeleteBullet();
	temp = DrawBullet(temp);

	return temp; 
}

int CPlayer::getHP()
{
	return m_Blood;
}

std::vector<CBullet*> CPlayer::getBulletsVec()
{
	return m_bullets;
}

void CPlayer::plusValue(int t)
{
	m_Value += t;
	if (!m_isUpdate && m_Value >= 2000)
		Update();
}

int CPlayer::getValue()
{
	return m_Value;
}

cv::Rect CPlayer::getPositionRect()
{
	Rect temp = Rect(m_Position.x, m_Position.y, m_width, m_height);
	return temp;
}

void CPlayer::LossBlood(int loss)
{
	if (loss != 0)
		PlayEffect(2);
	m_Blood = m_Blood - loss < 0 ? 0 : m_Blood - loss;
	if (m_Blood <= 0)
		m_isClear = true;
}

void CPlayer::Move()
{
	//if (!MOUSE_CLICK)
		//return;
	// 鼠标控制
	int x_left = MOUSE_POSITION.x - m_width / 2;
	int y_up = MOUSE_POSITION.y - m_height / 2;
	if (x_left <= 0)
		m_Position.x = 0;
	else if (x_left > max_Position.x)
		m_Position.x = max_Position.x;
	else
		m_Position.x = x_left;

	if (y_up <= 0)
		m_Position.y = 0;
	else if (y_up > max_Position.y)
		m_Position.y = max_Position.y;
	else
		m_Position.y = y_up;
}

