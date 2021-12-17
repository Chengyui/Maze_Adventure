// Other.cpp : 刷新界面、放置按钮、输出对话框类实现文件

#include "Game.h"		// 游戏头文件

// 全局变量

extern char ch;			// 键盘消息
extern MOUSEMSG m_msg;	// 鼠标消息

// COtner 类函数实现

// 绘制背景
void COther::putAll()
{
	IMAGE BK;
	loadimage(&BK, L"begin_background.png");
	//setbkcolor(RGB(50, 50, 50));
	putimage(0, 0, 800, 480, &BK, 0, 0);
	//cleardevice();
}

// 放置按钮
bool COther::button(int a, int b, wchar_t str[])
{
	static int x, y;																// 鼠标坐标

	setfillcolor(RGB(0, 0, 0));
	solidrectangle(a - 10, b, a + 19 * wcslen(str) +10, b + 30);					// 绘制边框

	x = m_msg.x;
	y = m_msg.y;																	// 获取坐标

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30) // 获得焦点显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 10, b, a + 19 * wcslen(str) + 10, b + 30);

		if (m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;

			return 1;
		}
	}

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	wcscpy_s(f.lfFaceName, L"宋体");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a, b+3 , str);	// 输出文字

	return 0;
}

