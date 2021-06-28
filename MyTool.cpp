#include "MyTool.h"

cv::Mat CopyRGBA2BGR(cv::Mat rgba_img, cv::Mat bgr_img,
	cv::Point dest, double alpha)
{
	// rgba_img 四通道图
	// bgr_img 三通道图（背景）
	// dest 目标坐标（左上角
	// alpha 四通道图的不透明度
	cv::Mat dest_img = bgr_img.clone();
	for (int i = 0; i < rgba_img.rows; i++)
	{
		cv::Vec4b* article_ptr = rgba_img.ptr<cv::Vec4b>(i);
		cv::Vec3b* back_ptr = dest_img.ptr<cv::Vec3b>(dest.y + i);
		for (int j = 0; j < rgba_img.cols; j++)
		{
			if (article_ptr[j][3] != 0)
			{
				for (int k = 0; k < 3; k++)
					back_ptr[j + dest.x][k] = back_ptr[j + dest.x][k] * (1 - alpha)
					+ article_ptr[j][k] * alpha;
			}
		}
	}

	return dest_img;
}

bool ifPointInRect(cv::Point pt, cv::Rect rect)
{
	bool ans = false;
	if (pt.x >= rect.x && pt.x <= rect.x + rect.width)
	{
		if (pt.y >= rect.y && pt.y <= rect.y + rect.height)
			ans = true;
	}
	return ans;
}

bool checkRectCont(cv::Rect rect1, cv::Rect rect2)
{
	cv::Point rect1_pt1 = cv::Point(rect1.x, rect1.y);
	cv::Point rect1_pt2 = cv::Point(rect1.x + rect1.width, rect1.y + rect1.height);
	
	cv::Point rect2_pt1 = cv::Point(rect2.x, rect2.y);
	cv::Point rect2_pt2 = cv::Point(rect2.x + rect2.width, rect2.y + rect2.height);

	bool wflag = (abs(rect1_pt1.x + rect1_pt2.x - rect2_pt1.x - rect2_pt2.x)
		<= (rect1.width + rect2.width));
	bool hflag = (abs(rect1_pt1.y + rect1_pt2.y - rect2_pt1.y - rect2_pt2.y)
		<= (rect1.height + rect2.height));

	if (wflag && hflag)
		return true;
	else
		return false;
}

void PlayBGM(int type)
{
	switch (type)
	{
	case 0: // 启动游戏
		mciSendString(_T("close all"), NULL, 0, NULL);
		mciSendString(_T("play .\\music\\bgm_log.mp3"), NULL, 0, NULL);
		break;
	case 1: // 游戏首页
		mciSendString(_T("close all"), NULL, 0, NULL);
		mciSendString(_T("play .\\music\\bgm_home.mp3 repeat"), NULL, 0, NULL);
		break;
	case 2: // 游戏普通战斗
		mciSendString(_T("close all"), NULL, 0, NULL);
		mciSendString(_T("play .\\music\\bgm_zhandou1.mp3 repeat"), NULL, 0, NULL);
		mciSendString(_T("play .\\music\\voice_readygo.mp3"), NULL, 0, NULL);
		break;
	}
}

void PlayEffect(int type)
{
	switch (type)
	{
	case 0: // 点击按钮音效
		mciSendString(_T("play .\\music\\effect_click_btn.mp3"), NULL, 0, NULL);
		break;
	case 1: // 敌机坠毁
		mciSendString(_T("play .\\music\\effect_enemy_crash.mp3"), NULL, 0, NULL);
		break;
	case 2: // 玩家掉血
		mciSendString(_T("play .\\music\\effect_player_shot.mp3"), NULL, 0, NULL);
		break;
	case 4: // 首页选飞机按钮
		mciSendString(_T("play .\\music\\effect_click_next.mp3"), NULL, 0, NULL);
		break;
	case 5: // 倒计时音效ding
		mciSendString(_T("play .\\music\\effect_time_ding.mp3"), NULL, 0, NULL);
		break;
	case 6: // gameover_voice
		mciSendString(_T("play .\\music\\voice_gameover.mp3"), NULL, 0, NULL);
		break;
	case 7: // 结算分数动
		mciSendString(_T("play .\\music\\effect_jiesuan.mp3"), NULL, 0, NULL);
		break;
	case 8: // 结算出分
		mciSendString(_T("play .\\music\\effect_explode.mp3"), NULL, 0, NULL);
		break;
	case 9: // 称号显示
		mciSendString(_T("play .\\music\\effect_title_jiesuan.mp3"), NULL, 0, NULL);
		break;
	}
}

void PlayBullet(int type)
{
	switch (type)
	{
	case 1:
		mciSendString(_T("play .\\music\\effect_bullet1.wav"), NULL, 0, NULL);
		break;
	case 2:
		mciSendString(_T("play .\\music\\effect_bullet2.wav"), NULL, 0, NULL);
		break;
	case 3:
		mciSendString(_T("play .\\music\\effect_bullet2.wav"), NULL, 0, NULL);
		break;
	}
}