#include "CGame.h"
using namespace cv;

void CGame::CreateEnemy()
{
	if (rand() % 80 == 1)
	{
		CEnemy* temp = new CEnemy(rand() % 4 + 4, rand() % 300);
		m_enemys.push_back(temp);
	}
	if (m_player->getValue() >= 3000 && rand() % 300 == 1)
	{
		CEnemy* temp = new CEnemy(rand() % 2 + 8, rand() % 20 + 40);
		m_enemys.push_back(temp);
	}
}

void CGame::DeleteEnemy()
{
	std::vector<CEnemy*>::iterator iter = m_enemys.begin();
	for (; iter != m_enemys.end(); )
	{
		if ((*iter)->m_isClear && (*iter)->getBulletsSize() == 0)
		{
			delete (*iter);
			iter = m_enemys.erase(iter);
		}
		else
			iter++;
	}
}

cv::Mat CGame::DrawEnemy(Mat& back)
{
	Mat temp = back.clone();
	std::vector<CEnemy*>::iterator iter = m_enemys.begin();
	for (; iter != m_enemys.end(); iter++)
	{
		temp = (*iter)->Draw(temp);
	}
	return temp;
}

void CGame::CheckAttackEnemy()
{
	std::vector<CBullet*> player_bullets = m_player->getBulletsVec();
	int player_get = 0;
	std::vector<CEnemy*>::iterator iter = m_enemys.begin();
	for (; iter != m_enemys.end(); iter++)
	{
		if ((*iter)->m_isClear)
			continue;
		player_get += (*iter)->CheckPlayerBullets(player_bullets);
	}
	m_player->plusValue(player_get);
}

void CGame::CheckAttackPlayer()
{
	int player_loss = 0;
	Rect player_rect = m_player->getPositionRect();
	std::vector<CEnemy*>::iterator iter = m_enemys.begin();
	for (; iter != m_enemys.end(); iter++)
	{
		player_loss += (*iter)->CheckPlayer(player_rect);
		if (player_loss >= m_player->getHP())
			break;
	}
	m_player->LossBlood(player_loss);
}

cv::Mat CGame::DrawSuspendBtn(cv::Mat& back)
{
	Mat temp = back.clone();
	temp = CopyRGBA2BGR(*m_suspendBtnImg, temp, Point(350, 10), 1);
	return temp;
}

cv::Mat CGame::DrawHP(cv::Mat& back)
{
	Mat temp = CopyRGBA2BGR(*m_hpImgs[m_player->getHP()], back, Point(10, 20), 1);
	return temp;
}

cv::Mat CGame::DrawScore(cv::Mat& back)
{
	if (m_plusScoreFlag == 10)
	{
		m_player->plusValue(1);
		m_plusScoreFlag = 0;
	}
	m_plusScoreFlag++;
	std::string score_str = std::to_string(m_player->getValue());

	int x = 20;
	Mat temp = back.clone();
	for (int i = 0; i < score_str.size(); i++)
	{
		int num = score_str[i] - '0';
		temp = CopyRGBA2BGR(*m_NumScore[num], temp, Point(x, 60), 1);
		x += m_NumScore[i]->cols;
	}

	return temp;
}

cv::Mat CGame::DrawUI(cv::Mat& back)
{
	Mat temp = back.clone();
	// 右上角暂停键
	temp = DrawSuspendBtn(temp);

	// 血条
	temp = DrawHP(temp);

	// 得分
	temp = DrawScore(temp);

	return temp;
}

int CGame::PauseUI(Mat& back, bool flag)
{
	Mat gaussian_blur;
	int case_type = 0;
	if (flag == 0)
	{
		GaussianBlur(back, gaussian_blur, Size(7, 7), 3, 3);
		gaussian_blur = CopyRGBA2BGR(*m_continueGameBtnImg, gaussian_blur, Point(50, 250), 1);
		gaussian_blur = CopyRGBA2BGR(*m_go2EndBtnImg, gaussian_blur, Point(50, 350), 1);
		gaussian_blur = CopyRGBA2BGR(*m_backMenuBtnImg, gaussian_blur, Point(50, 450), 1);
		while (1)
		{
			imshow(m_windowName, gaussian_blur);
			int key = waitKeyEx(30) % 255;
			if (key == 27)
			{
				case_type = 1;
				break;
			}
			if (MOUSE_CLICK)
			{
				Point click_pt = MOUSE_POSITION;
				if (ifPointInRect(click_pt, Rect(50, 250, 178, 50))) // 继续游戏
				{
					case_type = 1;
				}
				else if (ifPointInRect(click_pt, Rect(50, 450, 217, 50))) // 返回menu
				{
					case_type = 2;
				}
				else if (ifPointInRect(click_pt, Rect(50, 350, 178, 50))) // 直接结算
				{
					case_type = 3;
				}
				break;
			}
		}
	}
	int wait_time = 3;
	while (wait_time--) // 等待3s
	{
		GaussianBlur(back, gaussian_blur, Size(3, 3), 3, 3);
		Mat now_wait_num = m_NumScore[wait_time + 1]->clone();
		resize(now_wait_num, now_wait_num, Size(now_wait_num.cols * 1.8, now_wait_num.rows * 1.8));
		gaussian_blur = CopyRGBA2BGR(now_wait_num, gaussian_blur, Point(185, 300), 1);
		PlayEffect(5);
		imshow(m_windowName, gaussian_blur);
		waitKey(1000);
	}
	return case_type;
}

CGame::CGame(int player_type)
{
	m_windowName = "AirPlaneWar Game";
	m_scenes = new CScenes(); 
	m_player = new CPlayer(player_type);

	m_suspendBtnImg = new Mat(imread("./images/ui_suspend_btn.png", -1));

	m_hpImgs.push_back(new Mat(imread("./images/ui_hp_base.png", -1)));
	for (int i = 1; i <= 5; i++)
		m_hpImgs.push_back(new Mat(imread(
			"./images/ui_hp_" + std::to_string(i) + ".png", -1)));

	m_plusScoreFlag = 0;
	for (int i = 0; i <= 9; i++)
	{
		Mat * temp = new Mat(imread(
			"./images/img_num_score_" + std::to_string(i) + ".png", -1));
		resize(*temp, *temp, Size(temp->cols * 0.4, temp->rows * 0.4));
		m_NumScore.push_back(temp);
	}

	m_continueGameBtnImg = new Mat(imread("./images/ui_continuegame.png", -1));
	m_backMenuBtnImg = new Mat(imread("./images/ui_back2menu.png", -1));
	m_go2EndBtnImg = new Mat(imread("./images/ui_zhijiejiesuan.png", -1));
}

CGame::~CGame()
{
	m_scenes->~CScenes();
	m_player->~CPlayer();
	m_suspendBtnImg->release();
	m_NumScore.clear();
	m_enemys.clear();
}

int CGame::RunGame()
{
	PlayBGM(2); // 普通战斗音乐
	m_finallyScore = 0;
	while (1)
	{
		// 背景
		Mat show_img = m_scenes->CreateBackGround();
		// 敌人
		CreateEnemy();
		// 中弹检查
		CheckAttackEnemy();
		CheckAttackPlayer();
		// 敌人删除
		DeleteEnemy();
		// 绘制敌人
		show_img = DrawEnemy(show_img);
		// 绘制玩家
		show_img = m_player->Draw(show_img);
		// 绘制界面UI
		show_img = DrawUI(show_img);
		imshow(m_windowName, show_img);

		int key = waitKeyEx(30) % 255; 
		// Esc，暂停
		if (key == 27) 
		{
			PlayEffect(0);
			int click_case = PauseUI(show_img);
			if (click_case == 2) // 重新开始，退出循环
			{
				m_finallyScore = 0;
				break;
			}
			else if (click_case == 3) // 直接结算
			{
				m_finallyScore = m_player->getValue();
				break;
			}
		}
		// 点击右上角‘X’
		if (getWindowProperty(m_windowName, WINDOW_NORMAL))
			exit(0);
		// 玩家没血，游戏结束
		if (m_player->getHP() <= 0)
		{
			m_finallyScore = m_player->getValue();
			PauseUI(show_img, 1);
			break;
		}
	}
	return m_finallyScore;
}
