// Help.cpp : 帮助信息类实现文件

#include "Game.h"		// 游戏头文件

// 全局变量

extern MOUSEMSG m_msg;	// 鼠标消息

// CHelp 类函数实现

// 绘制界面
void CHelp::put()
{
	COther* but = new COther();

	while (1)
	{

		while (MouseHit())							// 鼠标消息获取
			m_msg = GetMouseMsg();

		but->putAll();								// 绘制背景

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"黑体");
			outtextxy(250 + i, 30 + i, L"帮 助");
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"黑体");
		outtextxy(250 + 3, 30 + 3, L"帮 助");		// 标题输出

		setfillcolor(RGB(100, 100, 100));
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 5);
		fillrectangle(125, 120, 510, 360);			// 绘制边框


		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 25;
		wcscpy_s(f.lfFaceName, L"宋体 Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);			
		settextcolor(WHITE);
		outtextxy(140, 130, L"游戏开始选择系列关卡");
		outtextxy(140, 170, L"有三种系列：");
		outtextxy(140, 200, L"普通模式：正计时");
		outtextxy(140, 230, L"金币模式：倒计时吃金币并到终点");
		outtextxy(140, 260, L"怪物模式：躲避怪物并到终点");
	
		if (but->button(280, 400, L"回到主页"))					// 回到主页按钮
			break;

		FlushBatchDraw();
	}

	delete but;
	but = NULL;
}

//////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////