
#include "Game.h"		// 游戏头文件



// 全局变量

extern char ch;						// 键盘消息
extern long long times, start_time;	// 计时器
extern MOUSEMSG m_msg;				// 鼠标消息

// Ccoin 函数实现

// Ccoin核心
void Ccoin::game()
{
	
	COther* but = new COther();
	
	while (1)
	{
		clear();									// 清空数据

		deepFS();									// 生成迷宫

		x = 2;
		y = 2;										// 重置坐标

		start_time = int(time(NULL));				// 设置初始时间 0 
				   
		while (1)
		{
			times = int(time(NULL)) - start_time;	// 累加时间

			ch = '#';								// 键盘消息清空

			if (_kbhit())							// 键盘消息获取
				ch = _getch();

			while (MouseHit())						// 鼠标消息获取
				m_msg = GetMouseMsg();

			man_Move();								// 人物移动处理

			if (x == 14 && y == 15)				// 到达终点判断
				break;

			but->putAll();							// 绘制背景
			IMAGE img_bk;
			loadimage(&img_bk, L"background.png");
			putimage(16,17,465-16,465-17,&img_bk,0,0);
			//setfillcolor(BLACK);
			//solidrectangle(16, 17, 465, 465);		// 绘制游戏区

			putRoom();								// 绘制界面
			putMan();								// 绘制人物

			
			
		/*	if (times > start_time + 2){
				start_time = times;
				monster_move();
			}*/

			if (times >= time_limit){
				
				break;
			}

			if (but->button(563, 400, L"回到主页"))											// 回到主页按钮
			{
				delete but;
				but = NULL;
				return;
			}

			

			FlushBatchDraw();
			Sleep(5);
		}
		if (times >= time_limit){
			failPut(1);
			break;
		}
		if (coins>10){
			failPut(0);
			break;
		}
	

		if (winPut())				// 通过一关卡界面
			break;
		pass++;
		n += 2;
		m += 2;
		if (n > 99 || m > 99)	// 下一关
		{
			n = 99;
			m = 99;
		}
	}

	delete but;
	but = NULL;
}


void Ccoin::deepFS()
{
	tot = 0;						// 节点数清空

	for (int i = 1; i <= n; i++)	// 初始化
	{
		for (int j = 1; j <= m; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
			{
				room[i][j] = ROAD;
				if (rand() % 3 == 1) 
				{ 
					coin[i][j] = 1;
					coins++;
				}
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

	dfs(tot);				
	
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
	room[n - 1][m] = END;	// 将图论 DFS 结果显示到迷宫中
	coin[2][2] = 0;
	
}

// 绘制界面
void Ccoin::putRoom()
{
	wchar_t tim[25], pas1[50], pas2[50],coin_text[25];	// 计时、当前关卡和总关卡

	//swprintf_s(pas1, L"第 %d 关\0", pass);
	swprintf_s(coin_text, L"剩余 %d 枚金币\0", coins);
	swprintf_s(tim, L"剩余时间 %lld s\0", time_limit-times); // 改为倒计时
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	wcscpy_s(f.lfFaceName, L"黑体");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	//outtextxy(480, 25, pas1);
	outtextxy(480, 55, coin_text);
	outtextxy(480, 85, tim);				// 输出文字
	IMAGE img_wall;	//准备图片
	IMAGE img_road;
	IMAGE you;
	IMAGE end;
	IMAGE road_coin;
	loadimage(&road_coin, L"road&coin.png");
	loadimage(&img_wall, L"wall.png");	//加载图片  L"背景.jpg"是图片的相对路径,也可以使用绝对路径
	loadimage(&img_road, L"road.png");
	loadimage(&you, L"player1.png");
	loadimage(&end, L"endpoint.png");

	for (int i = x - 4; i <= x + 4; i++)	// 绘制迷宫
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
			else if (room[i][j] == ROAD||YOU)
			{
				if (coin[i][j]==0) 
				putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266 ,&img_road);
				else{
					putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &road_coin);
				}
			}
			else if (room[i][j] == END)
			{
				putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &end);
				to_x = i;
				to_y = j;
			}
			else if (room[i][j] == YOU)
			{
				putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266,  &you);
				x = i;
				y = j;
				//if (coin[i][j]){
				//	coins++;
				//	coin[i][j] = 0;
			//	}
				
			}
		}
	}
	
	if (x+4>=n-1&&y+4>=m){
		putimagePng((m - 1 - y) * 50 + 266, (n-1 - 1 - x) * 50 + 266, &end);
	}
}

void Ccoin::putMan(){
	
	IMAGE you;
	
	if (status==0)
	loadimage(&you,L"player0.png");
	else if (status == 1)
		loadimage(&you, L"player1.png");
	else if (status == 2)
		loadimage(&you, L"player2.png");
	else if (status == 3)
		loadimage(&you, L"player3.png");
	putimagePng(216, 216, &you); // 绘制人物
	if (coin[x][y]){
		playmusic(1);
		coins--;
		coin[x][y] = 0;
	}

	

}