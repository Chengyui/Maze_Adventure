// Other.cpp : ˢ�½��桢���ð�ť������Ի�����ʵ���ļ�

#include "Game.h"		// ��Ϸͷ�ļ�

// ȫ�ֱ���

extern char ch;			// ������Ϣ
extern MOUSEMSG m_msg;	// �����Ϣ

// COtner �ຯ��ʵ��

// ���Ʊ���
void COther::putAll()
{
	IMAGE BK;
	loadimage(&BK, L"begin_background.png");
	//setbkcolor(RGB(50, 50, 50));
	putimage(0, 0, 800, 480, &BK, 0, 0);
	//cleardevice();
}

// ���ð�ť
bool COther::button(int a, int b, wchar_t str[])
{
	static int x, y;																// �������

	setfillcolor(RGB(0, 0, 0));
	solidrectangle(a - 10, b, a + 19 * wcslen(str) +10, b + 30);					// ���Ʊ߿�

	x = m_msg.x;
	y = m_msg.y;																	// ��ȡ����

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30) // ��ý�����ʾ
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
	wcscpy_s(f.lfFaceName, L"����");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a, b+3 , str);	// �������

	return 0;
}

