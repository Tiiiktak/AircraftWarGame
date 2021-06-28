#pragma once
#ifndef MyTool
#define MyTool
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")
// 绘制
cv::Mat CopyRGBA2BGR(cv::Mat rgba_img, cv::Mat bgr_img,
	cv::Point dest, double alpha);
// 判断点在矩形内
bool ifPointInRect(cv::Point pt, cv::Rect rect);
// 判断两矩形是否相交
bool checkRectCont(cv::Rect rect1, cv::Rect rect2);
// 播放BGM
void PlayBGM(int type); 
// 播放音效
void PlayEffect(int type);
// 播放子弹
void PlayBullet(int type);
#endif // !MyTool

