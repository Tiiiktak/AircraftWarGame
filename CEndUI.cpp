#include "CEndUI.h"
using namespace cv;

cv::Mat CEndUI::Numrunning(cv::Mat& back)
{
	Mat temp = back.clone();
	clock_t now_time = clock();
	if (now_time - begin_time >= 1100)
	{
		PlayEffect(8);
		if (m_playerScore > 999999)	m_playerScore = 999999;
		std::string score_str = std::to_string(m_playerScore);
		int score_len = score_str.length();
		for (int i = 0; i < 6 - score_len; i++)
		{
			temp = CopyRGBA2BGR(*m_NumScore[0], temp, m_numPos[i], 1);
		}
		for (int i = 6 - score_len, j = 0; i < 6; i++, j++)
		{
			int now_num = score_str[j] - '0';
			temp = CopyRGBA2BGR(*m_NumScore[now_num], temp, m_numPos[i], 1);
		}
		m_explodeFlag = true;
		*m_runningBack = temp.clone();
	}
	else
	{
		PlayEffect(7);
		for (int i = 0; i < 6; i++)
		{
			int now_num = rand() % 10;
			temp = CopyRGBA2BGR(*m_NumScore[now_num], temp, m_numPos[i], 1);
		}
	}
	return temp;
}

cv::Mat CEndUI::Titlerunning(cv::Mat& back)
{
	waitKey(700);
	PlayEffect(9);
	Mat temp = back.clone();
	if (m_playerScore > m_maxScore) // 破纪录
	{
		temp = CopyRGBA2BGR(*m_TitleImg[0], temp, Point(65, 260), 1);
	}else if (m_playerScore <= 2000) // 加油哦
	{
		temp = CopyRGBA2BGR(*m_TitleImg[1], temp, Point(75, 260), 1);
	}
	else // 皇牌飞行员
	{
		temp = CopyRGBA2BGR(*m_TitleImg[2], temp, Point(70, 285), 1);
	}
	m_titleFlag = true;
	*m_runningBack = temp.clone();
	return temp;
}

CEndUI::CEndUI(int player_score, int max_score)
{
	m_windowName = "AirPlaneWar Game";
	m_backgroundImg = new Mat(imread("./images/bg_home.jpg"));
	// 背景图resize 后：407 x 685
	resize(*m_backgroundImg, *m_backgroundImg, Size(m_backgroundImg->cols * 0.8, m_backgroundImg->rows * 0.8 + 1));
	m_runningBack = new Mat(m_backgroundImg->clone());

	width = m_backgroundImg->cols;
	height = m_backgroundImg->rows;

	m_girlImg = new Mat(imread("./images/ui_girl.png", -1));
	resize(*m_girlImg, *m_girlImg, Size(m_girlImg->cols * 0.8, m_girlImg->rows * 0.8));
	
	m_baseMap = new Mat(imread("./images/ui_purple_basemap.png", -1));
	resize(*m_baseMap, *m_baseMap, Size(m_baseMap->cols * 0.65, m_baseMap->rows * 0.65));

	for (int i = 0; i <= 9; i++)
	{
		Mat* temp = new Mat(imread(
			"./images/img_num_score_" + std::to_string(i) + ".png", -1));
		resize(*temp, *temp, Size(temp->cols * 0.6, temp->rows * 0.6));
		m_NumScore.push_back(temp);
	}
	for (int i = 1; i <= 3; i++)
	{
		Mat* temp = new Mat(imread(
			"./images/ui_title_" + std::to_string(i) + ".png", -1));
		resize(*temp, *temp, Size(temp->cols * 0.7, temp->rows * 0.7));
		m_TitleImg.push_back(temp);
	}

	m_sureBtnImg = new Mat(imread("./images/ui_queding.png", -1));

	m_playerScore = player_score;;
	m_maxScore = max_score;

	int num_w = 40;
	for (int i = 1; i <= 6; i++)
		m_numPos.push_back(Point(40 + i * num_w, 350));

	m_explodeFlag = false;
	m_titleFlag = false;
}

CEndUI::~CEndUI()
{
	m_backgroundImg->release();
	m_runningBack->release();
	m_NumScore.clear();
	m_TitleImg.clear();
}

void CEndUI::Settlement()
{
	PlayEffect(6); // gameover voice
	*m_runningBack = CopyRGBA2BGR(*m_girlImg, *m_runningBack, Point(55, 100), 1);
	*m_runningBack = CopyRGBA2BGR(*m_baseMap, *m_runningBack, Point(10, 280), 1);
	*m_runningBack = CopyRGBA2BGR(*m_sureBtnImg, *m_runningBack, Point(160, 500), 1);
	begin_time = clock();
	while (1)
	{
		Mat temp = m_runningBack->clone();
		if (!m_explodeFlag)
			temp = Numrunning(temp);
		else if (!m_titleFlag)
			temp = Titlerunning(temp);
		imshow(m_windowName, temp);
		waitKey(30);
		if (MOUSE_CLICK)
		{
			Point click_pt = MOUSE_POSITION;
			if (ifPointInRect(click_pt, Rect(160, 500, m_sureBtnImg->cols, m_sureBtnImg->rows)))
			{
				// 点击”确定“按钮
				PlayEffect(0);
				break;
			}
		}
		// 点击右上角 "X" 关闭窗口
		if (getWindowProperty(m_windowName, WINDOW_NORMAL))
			break;
	}
}
