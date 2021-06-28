#include "CStartUI.h"
using namespace cv;

void CStartUI::LogProgram()
{
	m_runningBack = new Mat(m_backgroundImg->size(), CV_8UC3, Scalar(0, 0, 0));
	std::vector<Mat> log_img; 
	// �����ɫͼƬ
	for (int i = 1; i <= 5; i++) 
	{
		Mat temp = imread("./images/log_" + std::to_string(i) + ".png");
		resize(temp, temp, Size(width, int(temp.rows * width / temp.cols)));
		log_img.push_back(temp);
	}
	imshow(m_windowName, *m_runningBack);

	// ��ʼ��������BGM
	PlayBGM(0);
	waitKey(840); // ��Ƶ�յ�

	// 5�Ž�ɫͼ������ʾ
	int log_h = 137;
	for (int i = 0; i < 5; i++)
	{
		Mat roi = (*m_runningBack)(Rect(0, i * log_h, width, log_h));
		log_img[i].copyTo(roi);
		imshow(m_windowName, *m_runningBack);
		waitKey(290);
	}

	// logo
	Mat log_logo = (*m_logoImg).clone();
	double logo_alpha = 0;
	double logo_size = 0.5;
	int logo_base_w = log_logo.cols;
	int logo_base_h = log_logo.rows;
	int logo_pos_y = 280;
	// logo�������
	while (logo_alpha <= 1)
	{
		resize(*m_logoImg, log_logo, Size(logo_base_w * logo_size, logo_base_h * logo_size));
		Mat temp_back = CopyRGBA2BGR(log_logo, *m_runningBack,
			Point(200 - log_logo.cols / 2, logo_pos_y - log_logo.rows / 2), logo_alpha);
		imshow(m_windowName, temp_back);
		waitKey(6);
		logo_alpha += 0.01;
		logo_size += logo_size >= 0.8 ? 0 : 0.004;
	}
	// logo����
	while (logo_pos_y >= 120)
	{
		Mat temp_back = CopyRGBA2BGR(log_logo, *m_runningBack,
			Point(200 - log_logo.cols / 2, logo_pos_y - log_logo.rows / 2), logo_alpha);
		logo_pos_y--;
		imshow(m_windowName, temp_back);
		waitKey(4);
	}
	// ����ͼ��Ϊ��ʼ����+logo
	*m_runningBack = CopyRGBA2BGR(log_logo, *m_backgroundImg,
		Point(200 - log_logo.cols / 2, logo_pos_y - log_logo.rows / 2), logo_alpha);
	waitKey(20);
}

void CStartUI::HomePage()
{
	// ��Ϸ��ҳbgm
	PlayBGM(1);

	Mat board_up = m_harfBoardImg->clone();
	Mat board_down;
	flip(board_up, board_down, 0); // ��ֱ��ת
	int board_w = board_up.cols;
	int board_h = board_up.rows;

	// ��ʾ��ť������
	*m_runningBack = CopyRGBA2BGR(board_up, *m_runningBack, Point(37, 250), 0.8);
	*m_runningBack = CopyRGBA2BGR(board_down, *m_runningBack, Point(37, 250 + board_h), 0.8);
	
	// ��ʾ����ʼ��Ϸ��
	Mat start_game_btn = m_startButtonImg->clone();
	*m_runningBack = CopyRGBA2BGR(start_game_btn, *m_runningBack, Point(115, 560), 1);

	// ��ʾѡ�ɻ����Ұ�ť
	Mat next_btn, pre_btn;
	next_btn = m_nextPlaneBtnImg->clone();
	flip(next_btn, pre_btn, 1);
	*m_runningBack = CopyRGBA2BGR(pre_btn, *m_runningBack, Point(50, 340), 1);
	*m_runningBack = CopyRGBA2BGR(next_btn, *m_runningBack, Point(320, 340), 1);

	imshow(m_windowName, *m_runningBack);
}

Mat CStartUI::ChoosePlane()
{
	Mat back = m_runningBack->clone();
	Mat plane= m_playerPlanes[m_choosePlane].clone();
	back = CopyRGBA2BGR(plane, back, Point(115, 320), 1);
	return back;
}

bool CStartUI::DealMooseClick()
{
	bool if_start_game = false;
	Point click_pt = MOUSE_POSITION;
	if (ifPointInRect(click_pt, Rect(115, 560, 173, 47))) // �������ʼ��Ϸ��
	{
		if_start_game = true;
		PlayEffect(0);
	}
	else if (ifPointInRect(click_pt, Rect(50, 340, 37, 86)))
	{
		m_choosePlane = m_choosePlane == 0 ? 2 : m_choosePlane - 1;
		PlayEffect(4);
	}
	else if (ifPointInRect(click_pt, Rect(320, 340, 37, 86)))
	{
		m_choosePlane = m_choosePlane == 2 ? 0 : m_choosePlane + 1;
		PlayEffect(4);
	}
	MOUSE_CLICK = false;
	return if_start_game;
}

CStartUI::CStartUI()
{
	m_windowName = "AirPlaneWar Game";
	m_logoImg = new Mat(imread("./images/logo.png", -1));

	m_harfBoardImg = new Mat(imread("./images/ui_board.png", -1));
	resize(*m_harfBoardImg, *m_harfBoardImg, Size(m_harfBoardImg->cols * 0.7, m_harfBoardImg->rows * 0.7));
	
	m_startButtonImg = new Mat(imread("./images/ui_startgame.png", -1));
	m_nextPlaneBtnImg = new Mat(imread("./images/ui_right_next_button.png", -1));
	resize(*m_nextPlaneBtnImg, *m_nextPlaneBtnImg, 
		Size(m_nextPlaneBtnImg->cols * 0.8, m_nextPlaneBtnImg->rows * 0.8));

	m_backgroundImg = new Mat(imread("./images/bg_home.jpg"));
	// ����ͼresize ��407 x 685
	resize(*m_backgroundImg, *m_backgroundImg, Size(m_backgroundImg->cols * 0.8, m_backgroundImg->rows * 0.8 + 1));
	m_runningBack = new Mat(m_backgroundImg->size(), CV_8UC3, Scalar(0, 0, 0));
	//std::cout << m_backgroundImg->size();
	width = m_backgroundImg->cols; 
	height = m_backgroundImg->rows;

	Mat show_plane = imread("./images/plane_showicon.png", -1);
	m_playerPlanes.push_back(show_plane(Rect(212, 237, 163, 98))); // x(212-375),y(237-335)
	m_playerPlanes.push_back(show_plane(Rect(203, 404, 166, 88))); // x(203-369),y(404-492)
	m_playerPlanes.push_back(show_plane(Rect(4, 244, 167, 120))); // x(4-171),y(244-364)
	m_choosePlane = 0;

	m_recordingScore = 0;
}

CStartUI::~CStartUI()
{
	m_backgroundImg->release();
	m_runningBack->release();
	m_logoImg->release();
}

void CStartUI::Run()
{
	namedWindow(m_windowName);
	CMouseControl* mouse = new CMouseControl(m_windowName);

	// ��Ϸ�����Ķ���
	LogProgram();
	
	// ��Ϸ��ҳ
	HomePage();

	while (1)
	{
		// ��ʾ�ɻ�
		Mat temp = ChoosePlane();

		imshow(m_windowName, temp);
		waitKeyEx(30);

		if (MOUSE_CLICK && DealMooseClick())
		{
			// ������Ϸ & ��ȡ��Ϸ��������¿�ʼor����
			CGame* now_game = new CGame(m_choosePlane + 1);	
			int now_score = now_game->RunGame();
			// ��ʼ����
			PlayBGM(1);
			// ���¿�ʼ
			if (now_score == 0)
				continue;
			// ����
			else
			{
				CEndUI* settle = new CEndUI(now_score, m_recordingScore);
				settle->Settlement(); // ��ʼ����
				m_recordingScore = now_score > m_recordingScore ? now_score : m_recordingScore;
			}
			// ���
			now_game->~CGame();
		}
		// ������Ͻ� "X" �رմ���
		if (getWindowProperty(m_windowName, WINDOW_NORMAL))
			break;
	}

	destroyWindow(m_windowName);
	mouse->~CMouseControl();
}
