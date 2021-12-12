#include "Game.h"		// ��Ϸͷ�ļ�
// ȫ�ֱ���

extern char ch;						// ������Ϣ
extern long long times, start_time;	// ��ʱ��
extern MOUSEMSG m_msg;				// �����Ϣ
extern long long tick;

//Cextreme ����ʵ��

//Cextreme����
void Cextreme::game()
{

	COther* but = new COther();

	while (1)
	{
		clear();									// �������

		deepFS();									// �����Թ�

		x = 2;
		y = 2;										// ��������

		start_time = int(time(NULL));				// ���ó�ʼʱ�� 0 
		long long  pre_time = start_time;		    //��¼ʱ�䣬��ӹ����ƶ�
		while (1)
		{
			times = int(time(NULL)) - start_time;	// �ۼ�ʱ��

			ch = '#';								// ������Ϣ���

			if (_kbhit())							// ������Ϣ��ȡ
				ch = _getch();

			while (MouseHit())						// �����Ϣ��ȡ
				m_msg = GetMouseMsg();

			man_Move();								// �����ƶ�����

			if (x == 14 && y == 15)				// �����յ��ж�
				break;

			but->putAll();							// ���Ʊ���
			IMAGE img_bk;
			loadimage(&img_bk, L"background.png");
			putimage(16, 17, 465 - 16, 465 - 17, &img_bk, 0, 0);
			//setfillcolor(BLACK);
			//solidrectangle(16, 17, 465, 465);		// ������Ϸ��



			putRoom();								// ���ƽ���
			putMan();								// ��������





			if (times >= time_limit){
				/*wchar_t * time_out[10];
				time_out[0] = L"���Ƿ�Ҫ�ص���ҳ��\n";
				but->button(563, 400, L"�ص���ҳ");
				but->button(563, 350, L"����ͣ��");
				if (but->putMessageBox(120, 165, 400, 150, L"��ʱ��������Ϸʧ��", time_out, 1, MY_OK))	// �ص���ҳ�Ի���
				{
				delete but;
				but = NULL;
				return;
				}*/
				break;
			}

			if (but->button(563, 400, L"�ص���ҳ"))											// �ص���ҳ��ť
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"���Ƿ�Ҫ�ص���ҳ��\n";
				but->button(563, 400, L"�ص���ҳ");
			
				if (but->putMessageBox(120, 165, 400, 150, L"�ص���ҳ", text, 1, MY_YESNO))	// �ص���ҳ�Ի���
				{
					delete but;
					but = NULL;
					return;
				}
				start_time = int(time(NULL)) - t;
				times = t;
			}

		
			FlushBatchDraw();
			tick++;
			Sleep(5);
		}
		if (times >= time_limit){
			failPut(1);
			break;
		}


		if (winPut())				// ͨ��һ�ؿ�����
			break;

		if (pass == all_pass)		// ͨ��ȫ�ؿ�����
		{
			gameOver();
			break;
		}
		pass++;
		n += 2;
		m += 2;
		if (n > 99 || m > 99)	// ��һ��
		{
			n = 99;
			m = 99;
		}
	}

	delete but;
	but = NULL;
}
void Cextreme::deepFS()
{
	tot = 0;						// �ڵ������

	for (int i = 1; i <= n; i++)	// ��ʼ��
	{
		for (int j = 1; j <= m; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
			{
				room[i][j] = ROAD;
				flag[0][++tot] = tot;
				flag[1][tot] = i;
				flag[2][tot] = j;
			}
			else
			{
				room[i][j] = WALL;
			}
		}
	}
	for (int i = 1; i <= tot; i++)
	{
		tip[i] = 0;
		if (i % ((n - 1) / 2) != 0)
		{
			reg[i][i + 1] = 1;
			reg[i + 1][i] = 1;
		}
		if (i <= tot - (n - 1) / 2)
		{
			reg[i][i + (n - 1) / 2] = 1;
			reg[i + (n - 1) / 2][i] = 1;
		}
	}

	dfs(tot);				// ����ͼ�� DFS ����

	for (int i = 1; i <= tot; i++)
	{
		for (int j = 1; j <= tot; j++)
		{
			if (reg[i][j] == 2 || reg[j][i] == 2)
			{
				my_line(flag[1][i], flag[2][i], flag[1][j], flag[2][j]);
			}
		}
	}
	room[2][2] = YOU;
	room[n - 1][m] = END;	// ��ͼ�� DFS �����ʾ���Թ���
	//room[13][2] = MONSTER;

}

void Cextreme::putRoom()
{
	wchar_t tim[25], pas1[50], pas2[50], coin_text[25];	// ��ʱ����ǰ�ؿ����ܹؿ�

	//swprintf_s(pas1, L"�� %d ��\0", pass);

	swprintf_s(tim, L"ʣ��ʱ�� %lld s\0", time_limit - times); // ��Ϊ����ʱ
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	wcscpy_s(f.lfFaceName, L"����");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	//outtextxy(480, 25, pas1);

	outtextxy(480, 85, tim);				// �������
	IMAGE img_wall;	//׼��ͼƬ
	IMAGE img_road;
	IMAGE you;
	IMAGE end;
	IMAGE road_coin;
	IMAGE mon;
	loadimage(&road_coin, L"road&coin.png");
	loadimage(&img_wall, L"wall.png");	//����ͼƬ  L"����.jpg"��ͼƬ�����·��,Ҳ����ʹ�þ���·��
	loadimage(&img_road, L"road.png");
	loadimage(&you, L"player1.png");
	loadimage(&end, L"endpoint.png");
	loadimage(&mon, L"mon&road.png");

	for (int i = x - 4; i <= x + 4; i++)	// �����Թ�
	{
		for (int j = y - 4; j <= y + 4; j++)
		{
			if (i < 1 || j < 1) {
				continue;
			}
			if (room[i][j] == WALL)
			{
				putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &img_wall);
			}
			else if (room[i][j] == ROAD || YOU)
			{

				putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &img_road);

			}
			else if (room[i][j] == END)
			{
				putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &end);
				to_x = i;
				to_y = j;
			}
			else if (room[i][j] == YOU)
			{
				putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &you);
				x = i;
				y = j;


			}
			/*else if (room[i][j] == MONSTER){
			putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &mon);
			mon_x = i;
			mon_y = j;
			}*/
		}
	}

	if (x + 4 >= n - 1 && y + 4 >= m){
		putimagePng((m - 1 - y) * 50 + 266, (n - 1 - 1 - x) * 50 + 266, &end);
	}
	/*if ((x + 4 >= mon_x&&y - 4 <= mon_y) || (x + 4 >= mon_x&&y + 4 >= mon_y) || (x -4 >= mon_x&&y + 4 >= mon_y) || (x + 4 >= mon_x&&y - 4 <= mon_y)){
	putimagePng((mon_y - 1 - y) * 50 + 266, (mon_x - 1 - x) * 50 + 266, &mon);
	}*/
}

void Cextreme::putMan(){

	IMAGE you;

	if (status == 0)
		loadimage(&you, L"player0.png");
	else if (status == 1)
		loadimage(&you, L"player1.png");
	else if (status == 2)
		loadimage(&you, L"player2.png");
	else if (status == 3)
		loadimage(&you, L"player3.png");
	putimagePng(216, 216, &you); // ��������


}
