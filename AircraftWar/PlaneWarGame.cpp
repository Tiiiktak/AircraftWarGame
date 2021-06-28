#include <iostream>
#include <opencv2/highgui.hpp>
#include "CMouseControl.h"
#include "CStartUI.h"
using namespace std;
using namespace cv;

// 游戏窗口名："AirPlaneWar Game"

int main()
{
    cout << "\t####### 全民飞机大战 #######" << endl; 
    cout << "\t---------------------------" << endl;
    cout << "\t游戏中按 'Esc键' 才能暂停哦！" << endl;
    cout << "\t---------------------------" << endl;
    cout << "\t玩家攻击强度：1" << endl;
    cout << "\t玩家血量：5" << endl;
    cout << "\t2000分后会自动升级" << endl;
    cout << "\t---------------------------" << endl;
    cout << "\t敌机攻击强度：1" << endl;
    cout << "\t敌机血量：4/8" << endl;
    cout << "\t---------------------------" << endl;
    cout << "\tBOSS攻击强度：1" << endl;
    cout << "\tBOSS血量：16" << endl;

    srand((unsigned)time(NULL));
    CStartUI* start = new CStartUI();
    start->Run();
    return 0;
}
