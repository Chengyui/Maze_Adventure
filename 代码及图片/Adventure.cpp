// Adventure.cpp : 冒险模式类文件

#include "Game.h"	// 游戏头文件

// 全局变量

char ch;						// 键盘消息
long long times, start_time;	// 计时器
MOUSEMSG m_msg;				// 鼠标消息
long long tick = 1;              //怪兽测试

// CAdventure 类函数实现


void CAdventure::playmusic(int flag){
	if (flag == 0){
		mciSendString(L"close  pace_music ", NULL, 0, NULL);//先关闭之前播放的本音乐
		mciSendString(L"open .\\pace.mp3 alias pace_music", NULL, 0, NULL);//bkmusic是自己定义的别名
		mciSendString(L"play pace_music", NULL, 0, NULL);
	}
	else if (flag == 1){
		mciSendString(L"close  coin_music ", NULL, 0, NULL);//先关闭之前播放的本音乐
		mciSendString(L"open .\\coin.mp3 alias coin_music", NULL, 0, NULL);//bkmusic是自己定义的别名
		mciSendString(L"play coin_music", NULL, 0, NULL);
	}
	else if (flag == 2){
		mciSendString(L"close  hurt_music ", NULL, 0, NULL);//先关闭之前播放的本音乐
		mciSendString(L"open .\\hurt.mp3 alias hurt_music", NULL, 0, NULL);//bkmusic是自己定义的别名
		mciSendString(L"play hurt_music", NULL, 0, NULL);
	}

}
void CAdventure::game()
{
	CAdventure* Adv;

	COther* but = new COther();

	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (1)
	{
		//mciSendString(L"close  bkmusic ", NULL, 0, NULL);//先关闭之前播放的本音乐
		//mciSendString(L"open .\\easybk.mp3 alias bkmusic", NULL, 0, NULL);//bkmusic是自己定义的别名
		//mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
		if (_kbhit())		// 键盘消息获取
		{
			ch = _getch();	// 键盘消息获取
			if (ch == 27)	// 按 Esc 退出
			{
				break;
			}
		}

		while (MouseHit())	// 鼠标消息获取
			m_msg = GetMouseMsg();

		but->putAll();		// 绘制背景

		/*for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(70, 0, L"宋体");
			outtextxy(235 + i, 85 + i, L"迷　宫");
		}*/
		//settextcolor(WHITE);
		settextcolor(RGB(250, 250, 250));
		settextstyle(50, 0, L"宋体");
		outtextxy(170 + 3, 85 + 3, L"MAZE ADVENTURE");		// 标题输出

		if (but->button(60, 260, L"　普通模式　"))		// 普通模式按钮
		{
			mciSendString(L"close  bkmusic ", NULL, 0, NULL);//先关闭之前播放的本音乐
			mciSendString(L"open .\\easybk.mp3 alias bkmusic", NULL, 0, NULL);//bkmusic是自己定义的别名
			mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
			Adv = new Cnormal();
			Adv->all_pass = 1; // 暂时将每个模式设置为只有一关
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

		if (but->button(220, 260, L"　极限模式　"))		// 极限模式按钮
		{
			mciSendString(L"close  bkmusic ", NULL, 0, NULL);//先关闭之前播放的本音乐
			mciSendString(L"open .\\easybk.mp3 alias bkmusic", NULL, 0, NULL);//bkmusic是自己定义的别名
			mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
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

		if (but->button(380, 260, L"　金币模式　"))		// 金币模式按钮
		{
			mciSendString(L"close  bkmusic ", NULL, 0, NULL);//先关闭之前播放的本音乐
			mciSendString(L"open .\\easybk.mp3 alias bkmusic", NULL, 0, NULL);//bkmusic是自己定义的别名
			mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
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

		if (but->button(540, 260, L"　怪物模式　"))		// 怪物模式按钮
		{
			mciSendString(L"close  bkmusic ", NULL, 0, NULL);//先关闭之前播放的本音乐
			mciSendString(L"open .\\bk2.mp3 alias bkmusic", NULL, 0, NULL);//bkmusic是自己定义的别名
			mciSendString(L"play bkmusic repeat", NULL, 0, NULL);
			
			Adv = new Cmonster();
			Adv->all_pass = 1;
			Adv->time_limit = 600;
			Adv->pass = 1;
			Adv->n = 25;
			Adv->m = 25;
			Adv->mon_x = rand()%25;
			Adv->mon_y = rand()%25;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}



		LOGFONT f;
		gettextstyle(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"宋体 Light");
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

// 通过一关卡界面
bool CAdventure::winPut()
{
	COther* but = new COther();

	wchar_t title[50];

	swprintf_s(title, L"成功通关！！使用时间 %lld s\0", times);

	while (1)
	{
		if (_kbhit())				// 键盘消息获取
			ch = _getch();
		
		while (MouseHit())
			m_msg = GetMouseMsg();	// 鼠标消息获取

		but->putAll();				// 绘制背景
		settextcolor(WHITE);
		settextstyle(30, 0, L"黑体");
		outtextxy(140 + 3, 90 + 3, title);		// 标题输出

		if (but->button(273, 300, L"回到主页"))	// 回到主页按钮
		{
			

			delete but;
			but = NULL;
			return 1;
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
	mciSendString(L"close  bkmusic ", NULL, 0, NULL);//先关闭之前播放的本音乐
	mciSendString(L"close  death_music ", NULL, 0, NULL);//先关闭之前播放的本音乐
	mciSendString(L"open .\\death.mp3 alias death_music", NULL, 0, NULL);//bkmusic是自己定义的别名
	mciSendString(L"play death_music", NULL, 0, NULL);

	COther* but = new COther();

	wchar_t title[50];
	if (flag==1)
		swprintf_s(title, L"超时，游戏失败，使用时间 %lld s\0", times);
	else if (flag==0)
		swprintf_s(title, L"金币数量不足，游戏失败，使用时间 %lld s\0", times);
	else if (flag==2)
		swprintf_s(title, L"被忍者猎杀，游戏失败，使用时间 %lld s\0", times);

	while (1)
	{
		if (_kbhit())				// 键盘消息获取
			ch = _getch();

		while (MouseHit())
			m_msg = GetMouseMsg();	// 鼠标消息获取

		but->putAll();				// 绘制背景

		settextcolor(WHITE);
		settextstyle(30, 0, L"黑体");
		outtextxy(100 + 3, 90 + 3, title);		// 标题输出

		

		if (but->button(273, 300, L"回到主页"))	// 回到主页按钮
		{
			delete but;
			but = NULL;
			return 1;
		}

		FlushBatchDraw();
		Sleep(5);
	}

	times = 0;
	delete but;
	but = NULL;
	return 0;
}

// 人物移动处理
void CAdventure::man_Move()
{
	if (ch == 'w' && room[x - 1][y] != WALL)		// 上移处理
	{
		playmusic(0);
		room[x - 1][y] = YOU;
		room[x][y] = ROAD;
		x--;
		status = 0;
		//ch = '#';									// 赋为其他值，防止人物持续移动
		//for (int i = 0; i < 6;i++)
		//monster_Move();
	}
	else if (ch == 's' && room[x + 1][y] != WALL)	// 下移处理
	{
		playmusic(0);
		room[x + 1][y] = YOU;
		room[x][y] = ROAD;
		x++;
		status = 1;
		//ch = '#';
	
	//	for (int i = 0; i < 6; i++)
		//	monster_Move();
	}
	else if (ch == 'a' && room[x][y - 1] != WALL)	// 左移处理
	{
		playmusic(0);
		room[x][y - 1] = YOU;
		room[x][y] = ROAD;
		y--;
		status = 2;
		//ch = '#';
		
		//for (int i = 0; i < 6; i++)
		//	monster_Move();
	}
	else if (ch == 'd' && room[x][y + 1] != WALL)	// 右移处理
	{
		playmusic(0);
		room[x][y + 1] = YOU;
		room[x][y] = ROAD;
		y++;
		status = 3;
		//ch = '#';
		
		
	}
	if (ch != '#')
	for (int i = 0; i < 4; i++)
		monster_Move();
	ch = '#';
}

//怪物移动处理

void CAdventure::monster_Move(){

	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };
	int dir;
	if (x == mon_x&&y>mon_y) dir = 0;
	else if (x == mon_x&&y<mon_y) dir = 1;
	else if (x>mon_x&&y==mon_y) dir = 2;
	else if (x < mon_x&&y==mon_y) dir = 3;
	else{
		//走有路的方向
		dir = rand() % 4;
		while (room[mon_x + dx[dir]][mon_y + dy[dir]] != ROAD){
			dir++;
			dir = dir % 4;
		}
		
	}
	if (room[mon_x + dx[dir]][mon_y + dy[dir]] == ROAD){
		//room[mon_x][mon_y] = ROAD;
		//room[mon_x + dx[dir]][mon_y + dy[dir]] == MONSTER;
		mon_x += dx[dir], mon_y += dy[dir];
	


	}
	
}
// 清空数据处理
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

// 暴力 DFS 搜索生成迷宫核心
int CAdventure::search(int x, int y)
{
	const int f[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 方向数组

	int e[4];												// 随机方向数组

	for (int i = 0; i < 4; i++)								// 随机化
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
	if (x == 1 || y == 1 || x == n || y == m || room[x][y] == ROAD || fmap[x][y] == 1)	// 越界（已打通）判断
		return 0;

	int back = 0;
	for (int i = 0; i <= 3; i++)
		if (room[x + f[i][0]][y + f[i][1]] == ROAD)
			back++;
	if (back >= 2)		// 判断是否成回路
	{
		back = 0;
		return 0;
	}

	room[x][y] = ROAD;	// 打通
	for (int i = 0; i <= 3; i++)
	{
		fmap[x][y] = 1; // 标记
		search(x + f[e[i]][0], y + f[e[i]][1]);
		fmap[x][y] = 0; // 回溯
	}

	return 0;
}


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
	if (a < 1) cst[e[3]] = step;												// 随机化

	for (int i = 1; i <= 4; i++)
	{
		if ((reg[step][cst[i]] == 1 || reg[cst[i]][step] == 1) && !tip[cst[i]]) // 打通（走过）判断
		{

			reg[step][cst[i]] = 2;												// 标记打通
			reg[cst[i]][step] = 2;												// 标记打通
			tip[cst[i]] = 1;													// 标记走过
			tip[step] = 1;														// 标记走过
			dfs(cst[i]);
		}
	}
	return 0;
}

// 辅助函数
int CAdventure::my_line(int x_1, int y_1, int x_2, int y_2)
{
	if (x_1 == x_2)		// 连通处理
		room[x_1][(y_1 + y_2) / 2] = ROAD;
	else if (y_1 == y_2)
		room[(x_1 + x_2) / 2][y_1] = ROAD;
	return 0;
}