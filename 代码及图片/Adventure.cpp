// Adventure.cpp : ð��ģʽ���ļ�

#include "Game.h"	// ��Ϸͷ�ļ�

// ȫ�ֱ���

char ch;						// ������Ϣ
long long times, start_time;	// ��ʱ��
MOUSEMSG m_msg;				// �����Ϣ
long long tick = 1;              //���޲���

// CAdventure �ຯ��ʵ��

// ð��ģʽ����
void CAdventure::playmusic(){
	mciSendString(L"close  music ", NULL, 0, NULL);//�ȹر�֮ǰ���ŵı�����
	mciSendString(L"open .\\pace.mp3 alias music", NULL, 0, NULL);//bkmusic���Լ�����ı���
	mciSendString(L"play music", NULL, 0, NULL);
}
void CAdventure::game()
{
	CAdventure* Adv;
	CHelp* help = new CHelp();
	COther* but = new COther();

	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (1)
	{
		//mciSendString(L"close  bkmusic ", NULL, 0, NULL);//�ȹر�֮ǰ���ŵı�����
		mciSendString(L"open .\\easybk.mp3 alias bkmusic", NULL, 0, NULL);//bkmusic���Լ�����ı���
		mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
		if (_kbhit())		// ������Ϣ��ȡ
		{
			ch = _getch();	// ������Ϣ��ȡ
			if (ch == 27)	// �� Esc �˳�
			{
				break;
			}
		}

		while (MouseHit())	// �����Ϣ��ȡ
			m_msg = GetMouseMsg();

		but->putAll();		// ���Ʊ���

		/*for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(70, 0, L"����");
			outtextxy(235 + i, 85 + i, L"�ԡ���");
		}*/
		//settextcolor(WHITE);
		settextcolor(RGB(250, 250, 250));
		settextstyle(50, 0, L"����");
		outtextxy(170 + 3, 85 + 3, L"MAZE ADVENTURE");		// �������

		if (but->button(60, 260, L"����ͨģʽ��"))		// ��ͨģʽ��ť
		{
			Adv = new Cnormal();
			Adv->all_pass = 1; // ��ʱ��ÿ��ģʽ����Ϊֻ��һ��
			Adv->time_limit = 60;
			Adv->pass = 1;
			Adv->n = 15;
			Adv->m = 15;
			Adv->mon_x = 13;
			Adv->mon_y = 2;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}

		if (but->button(220, 260, L"������ģʽ��"))		// ����ģʽ��ť
		{
			Adv = new Cextreme();
			Adv->all_pass = 1;
			Adv->time_limit = 20;
			Adv->pass = 1;
			Adv->n = 25;
			Adv->m = 25;
			Adv->mon_x = 13;
			Adv->mon_y = 2;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}

		if (but->button(380, 260, L"�����ģʽ��"))		// ���ģʽ��ť
		{
			Adv = new Ccoin();
			Adv->all_pass = 2;
			Adv->time_limit = 60;
			Adv->pass = 1;
			Adv->n = 15;
			Adv->m = 15;
			Adv->mon_x = 13;
			Adv->mon_y = 2;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}

		if (but->button(540, 260, L"������ģʽ��"))		// ����ģʽ��ť
		{
			mciSendString(L"close  bkmusic ", NULL, 0, NULL);//�ȹر�֮ǰ���ŵı�����
			mciSendString(L"open .\\bk2.mp3 alias bkmusic", NULL, 0, NULL);//bkmusic���Լ�����ı���
			mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
			
			Adv = new Cmonster();
			Adv->all_pass = 1;
			Adv->time_limit = 60;
			Adv->pass = 1;
			Adv->n = 15;
			Adv->m = 15;
			Adv->mon_x = 13;
			Adv->mon_y = 2;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}



		LOGFONT f;
		gettextstyle(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"���� Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		settextcolor(WHITE);

		outtextxy(250, 153, L"Powered By Chengjinguo");

		FlushBatchDraw();
		Sleep(10);
	}

	EndBatchDraw();

	delete but;
	but = NULL;
	delete Adv;
	Adv = NULL;
}

// ͨ��һ�ؿ�����
bool CAdventure::winPut()
{
	COther* but = new COther();

	wchar_t title[50];

	swprintf_s(title, L"�ɹ�ͨ�أ���ʹ��ʱ�� %lld s\0", times);

	while (1)
	{
		if (_kbhit())				// ������Ϣ��ȡ
			ch = _getch();

		while (MouseHit())
			m_msg = GetMouseMsg();	// �����Ϣ��ȡ

		but->putAll();				// ���Ʊ���
		settextcolor(WHITE);
		settextstyle(30, 0, L"����");
		outtextxy(140 + 3, 90 + 3, title);		// �������

		if (but->button(273, 215, L" ��һ��"))	// ��һ�ذ�ť
			break;

		if (but->button(273, 300, L"�ص���ҳ"))	// �ص���ҳ��ť
		{
			wchar_t* text[10];
			text[0] = L"��ȷ����Ҫ�ص���ҳ��\n";
			but->button(273, 300, L"�ص���ҳ");
			if (but->putMessageBox(120, 165, 400, 150, L"�ص���ҳ", text, 1, MY_YESNO))		// �ص���ҳ�Ի���
			{
				delete but;
				but = NULL;
				return 1;
			}
		}

		FlushBatchDraw();
		Sleep(5);
	}

	times = 0;
	delete but;
	but = NULL;
	return 0;
}
bool CAdventure::failPut(int flag){
	COther* but = new COther();

	wchar_t title[50];
	if (flag==1)
		swprintf_s(title, L"��ʱ����Ϸʧ�ܣ�ʹ��ʱ�� %lld s\0", times);
	else if (flag==0)
		swprintf_s(title, L"����������㣬��Ϸʧ�ܣ�ʹ��ʱ�� %lld s\0", times);
	else if (flag==2)
		swprintf_s(title, L"��������ɱ����Ϸʧ�ܣ�ʹ��ʱ�� %lld s\0", times);

	while (1)
	{
		if (_kbhit())				// ������Ϣ��ȡ
			ch = _getch();

		while (MouseHit())
			m_msg = GetMouseMsg();	// �����Ϣ��ȡ

		but->putAll();				// ���Ʊ���

		settextcolor(WHITE);
		settextstyle(30, 0, L"����");
		outtextxy(100 + 3, 90 + 3, title);		// �������

		if (but->button(273, 215, L" ��һ��"))	// ��һ�ذ�ť
			break;

		if (but->button(273, 300, L"�ص���ҳ"))	// �ص���ҳ��ť
		{
			wchar_t* text[10];
			text[0] = L"��ȷ����Ҫ�ص���ҳ��\n";
			but->button(273, 300, L"�ص���ҳ");
			if (but->putMessageBox(120, 165, 400, 150, L"�ص���ҳ", text, 1, MY_YESNO))		// �ص���ҳ�Ի���
			{
				delete but;
				but = NULL;
				return 1;
			}
		}

		FlushBatchDraw();
		Sleep(5);
	}

	times = 0;
	delete but;
	but = NULL;
	return 0;
}
// ͨ��ȫ�ؿ�����
void CAdventure::gameOver()
{
	COther* but = new COther();

	while (1)
	{
		if (_kbhit())				// ������Ϣ��ȡ
			ch = _getch();

		while (MouseHit())			// �����Ϣ��ȡ
			m_msg = GetMouseMsg();	

		but->putAll();				// ���Ʊ���

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"����");
			outtextxy(200 + i, 90 + i, L"��Ϸ����");
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"����");
		outtextxy(200 + 3, 90 + 3, L"��Ϸ����");	// �������

		if (but->button(273, 215, L"�ص���ҳ"))		// �ص���ҳ��ť
			break;

		if (but->button(273, 300, L"�˳���Ϸ"))		// �˳���Ϸ��ť
		{
			delete but;
			but = NULL;
			EndBatchDraw();
			closegraph();
			exit(0);
		}

		FlushBatchDraw();
		Sleep(5);
	}

	delete but;
	but = NULL;
}


// �����ƶ�����
void CAdventure::man_Move()
{
	if (ch == 'w' && room[x - 1][y] != WALL)		// ���ƴ���
	{
		playmusic();
		room[x - 1][y] = YOU;
		room[x][y] = ROAD;
		x--;
		status = 0;
		ch = '#';									// ��Ϊ����ֵ����ֹ��������ƶ�
		for (int i = 0; i < 6;i++)
		monster_Move();
	}
	else if (ch == 's' && room[x + 1][y] != WALL)	// ���ƴ���
	{
		playmusic();
		room[x + 1][y] = YOU;
		room[x][y] = ROAD;
		x++;
		status = 1;
		ch = '#';
	
		for (int i = 0; i < 6; i++)
			monster_Move();
	}
	else if (ch == 'a' && room[x][y - 1] != WALL)	// ���ƴ���
	{
		playmusic();
		room[x][y - 1] = YOU;
		room[x][y] = ROAD;
		y--;
		status = 2;
		ch = '#';
		
		for (int i = 0; i < 6; i++)
			monster_Move();
	}
	else if (ch == 'd' && room[x][y + 1] != WALL)	// ���ƴ���
	{
		playmusic();
		room[x][y + 1] = YOU;
		room[x][y] = ROAD;
		y++;
		status = 3;
		ch = '#';
		
		for (int i = 0; i < 6; i++)
			monster_Move();
	}
	
	
}

//�����ƶ�����

void CAdventure::monster_Move(){

	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };
	int dir;

	dir = rand() % 4;
	if (room[mon_x + dx[dir]][mon_y + dy[dir]] == ROAD){
		//room[mon_x][mon_y] = ROAD;
		//room[mon_x + dx[dir]][mon_y + dy[dir]] == MONSTER;
		mon_x += dx[dir], mon_y += dy[dir];


	}
	
}
// ������ݴ���
void CAdventure::clear()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			room[i][j] = 0;
			fmap[i][j] = 0;
		}
	}
	for (int i = 1; i <= (n + 1) / 2 * (m + 1) / 2; i++)
	{
		for (int j = 1; j <= (n + 1) / 2 * (m + 1) / 2; j++)
		{
			reg[i][j] = 0;
			feg[i][j] = 0;
		}
	}
	for (int i = 1; i <= (n + 1) / 2 * (m + 1) / 2; i++)
	{
		for (int j = 0; j < 3; j++)
			flag[j][i] = 0;
		tip[i] = 0;
	}
}

// ���� DFS ���������Թ�����
int CAdventure::search(int x, int y)
{
	const int f[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // ��������

	int e[4];												// �����������

	for (int i = 0; i < 4; i++)								// �����
	{
		e[i] = rand() % 4;
		for (int j = 0; j < i; j++)
		{
			if (e[i] == e[j])
			{
				e[i] = rand() % 4;
				j = -1;
			}
		}
	}
	if (x == 1 || y == 1 || x == n || y == m || room[x][y] == ROAD || fmap[x][y] == 1)	// Խ�磨�Ѵ�ͨ���ж�
		return 0;

	int back = 0;
	for (int i = 0; i <= 3; i++)
		if (room[x + f[i][0]][y + f[i][1]] == ROAD)
			back++;
	if (back >= 2)		// �ж��Ƿ�ɻ�·
	{
		back = 0;
		return 0;
	}

	room[x][y] = ROAD;	// ��ͨ
	for (int i = 0; i <= 3; i++)
	{
		fmap[x][y] = 1; // ���
		search(x + f[e[i]][0], y + f[e[i]][1]);
		fmap[x][y] = 0; // ����
	}

	return 0;
}

// ͼ�� DFS ���������Թ�����
int CAdventure::dfs(int step)
{
	int e[4];
	for (int i = 0; i < 4; i++)
	{
		e[i] = rand() % 4 + 1;
		for (int j = 0; j < i; j++)
		{
			if (e[i] == e[j])
			{
				e[i] = rand() % 4 + 1;
				j = -1;
			}
		}
	}
	int a = 0, cst[5];
	a = cst[e[0]] = step + 1;
	if (a > tot) cst[e[0]] = step;
	a = cst[e[1]] = step - 1;
	if (a < 1) cst[e[1]] = step;
	a = cst[e[2]] = step + (n - 1) / 2;
	if (a > tot) cst[e[2]] = step;
	a = cst[e[3]] = step - (n - 1) / 2;
	if (a < 1) cst[e[3]] = step;												// �����

	for (int i = 1; i <= 4; i++)
	{
		if ((reg[step][cst[i]] == 1 || reg[cst[i]][step] == 1) && !tip[cst[i]]) // ��ͨ���߹����ж�
		{

			reg[step][cst[i]] = 2;												// ��Ǵ�ͨ
			reg[cst[i]][step] = 2;												// ��Ǵ�ͨ
			tip[cst[i]] = 1;													// ����߹�
			tip[step] = 1;														// ����߹�
			dfs(cst[i]);
		}
	}
	return 0;
}

// ��������
int CAdventure::my_line(int x_1, int y_1, int x_2, int y_2)
{
	if (x_1 == x_2)		// ��ͨ����
		room[x_1][(y_1 + y_2) / 2] = ROAD;
	else if (y_1 == y_2)
		room[(x_1 + x_2) / 2][y_1] = ROAD;
	return 0;
}