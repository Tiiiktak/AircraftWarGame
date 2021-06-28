#include "CScenes.h"
using namespace cv;

void CScenes::running()
{
	if (m_runDis == 0)
	{
		m_runningImg = m_levelBackImg[m_nowLevel - 1].clone();
	}
	else
	{

		Mat ori_back = m_levelBackImg[m_nowLevel - 1].clone();
		Mat black = Mat(ori_back.size(), CV_8UC3, Scalar(0, 0, 0));

		Mat ori_down = ori_back(Rect(0, 0, 407, 685 - m_runDis));
		Mat ori_up = ori_back(Rect(0, 685 - m_runDis, 407, m_runDis));

		Mat mask_up = black(Rect(0, 0, 407, m_runDis));
		Mat mask_down = black(Rect(0, m_runDis, 407, 685 - m_runDis));

		ori_down.copyTo(mask_down);
		ori_up.copyTo(mask_up);

		m_runningImg = black.clone();
	}

	if (m_runflag == 2) // 数字越大地图越慢（可能卡顿）
	{
		m_runDis = m_runDis == 684 ? 0 : m_runDis + 1;
		m_runflag = 0;
	}
	m_runflag++;
}

CScenes::CScenes()
{
	for (int i = 1; i <= 5; i++)
	{
		Mat temp = imread("./images/img_bg_level_" 
								+ std::to_string(i) + ".jpg");
		resize(temp, temp, Size(407, 685));
		m_levelBackImg.push_back(temp);
	}
	m_nowLevel = rand() % 5 + 1;
	m_runDis = 0;
	m_runflag = 0;
}

CScenes::~CScenes()
{
	m_levelBackImg.clear();
	m_runningImg.release();
}


cv::Mat CScenes::CreateBackGround()
{
	running();

	return m_runningImg;
}
