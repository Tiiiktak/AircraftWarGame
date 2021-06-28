#pragma once
#ifndef MyTool
#define MyTool
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")
// ����
cv::Mat CopyRGBA2BGR(cv::Mat rgba_img, cv::Mat bgr_img,
	cv::Point dest, double alpha);
// �жϵ��ھ�����
bool ifPointInRect(cv::Point pt, cv::Rect rect);
// �ж��������Ƿ��ཻ
bool checkRectCont(cv::Rect rect1, cv::Rect rect2);
// ����BGM
void PlayBGM(int type); 
// ������Ч
void PlayEffect(int type);
// �����ӵ�
void PlayBullet(int type);
#endif // !MyTool

