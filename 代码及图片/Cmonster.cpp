#include "Game.h"		// 游戏头文件
// 全局变量

extern char ch;						// 键盘消息
extern long long times, start_time;	// 计时器
extern MOUSEMSG m_msg;				// 鼠标消息
extern long long tick;
int hearts = 3;
int prex, prey;
//Cmonster 函数实现

//Cmonster核心
void Cmonster::game()
{

	COther* but = new COther();
	int mon_flag = 0; //撞到怪物的退出判断
	while (1)
	{
		hearts = 3;
		clear();									// 清空数据

		deepFS();									// 生成迷宫

		x = 2;
		y = 2;										// 重置坐标
		prex = x, prey = y;
		start_time = int(time(NULL));				// 设置初始时间 0 
		long long  pre_time = start_time;		    //记录时间，添加怪物移动
		while (1)
		{
			times = int(time(NULL)) - start_time;	// 累加时间

			ch = '#';								// 键盘消息清空

			if (_kbhit())							// 键盘消息获取
				ch = _getch();

			while (MouseHit())						// 鼠标消息获取
				m_msg = GetMouseMsg();

			man_Move();								// 人物移动处理

			if (x == n-1 && y == m)				// 到达终点判断
				break;

			but->putAll();							// 绘制背景
			IMAGE img_bk;
			loadimage(&img_bk, L"background.png");
			putimage(16, 17, 465 - 16, 465 - 17, &img_bk, 0, 0);
			//setfillcolor(BLACK);
			//solidrectangle(16, 17, 465, 465);		// 绘制游戏区

		

			putRoom(hearts);								// 绘制界面
			putMan();								// 绘制人物
		


			

			if (times >= time_limit){
				/*wchar_t * time_out[10];
				time_out[0] = L"你是否要回到主页？\n";
				but->button(563, 400, L"回到主页");
				but->button(563, 350, L"　暂停　");
				if (but->putMessageBox(120, 165, 400, 150, L"计时结束，游戏失败", time_out, 1, MY_OK))	// 回到主页对话框
				{
				delete but;
				but = NULL;
				return;
				}*/
				break;
			}
			
			if (abs(mon_x-x)<=2&&abs(mon_y-y)<=2) {
				if (prex != x || prey != y){
					playmusic(2);
					hearts--;
					prex = x, prey = y;
				}
				
				if (hearts <= 0){
					mon_flag = 1;
					break;
				}
				
			}

			if (but->button(563, 400, L"回到主页"))											// 回到主页按钮
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"你是否要回到主页？\n";
				but->button(563, 400, L"回到主页");
				if (but->putMessageBox(120, 165, 400, 150, L"回到主页", text, 1, MY_YESNO))	// 回到主页对话框
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
		if (mon_flag){
			failPut(2);
			break;
		}

		if (winPut())				// 通过一关卡界面
			break;

		if (pass == all_pass)		// 通过全关卡界面
		{
			gameOver();
			break;
		}
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
void Cmonster::deepFS()
{
	tot = 0;						// 节点数清空

	for (int i = 1; i <= n; i++)	// 初始化
	{
		for (int j = 1; j <= m; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
			{
				if (rand() % 10 == 1){
					med[i][j] = 1;
					meds++;
				}
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

	dfs(tot);				// 进行图论 DFS 生成

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
	//room[13][2] = MONSTER;
	med[2][2] = 0;
}

void Cmonster::putRoom(int lives)
{
	wchar_t tim[25], pas1[50], pas2[50], coin_text[25],commit[25];	// 计时、当前关卡和总关卡

	//swprintf_s(pas1, L"第 %d 关\0", pass);
	
	swprintf_s(commit, L"忍者伤害距离为2"); // 改为倒计时
	swprintf_s(tim, L"剩余时间 %lld s\0", time_limit - times); // 改为倒计时
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	wcscpy_s(f.lfFaceName, L"黑体");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	//outtextxy(480, 25, pas1);
	
	outtextxy(480, 105, tim);				// 输出文字
	outtextxy(480, 60,commit);				//输出提示

	IMAGE live;
	loadimage(&live, L"life.png");			//输出生命值
	lives = lives < 5 ? lives : 5;
	for (int i = 0; i < lives; i++)
		putimagePng(480 + 50 * i, 25,&live);


	IMAGE img_wall;	//准备图片
	IMAGE img_road;
	IMAGE you;
	IMAGE end;
	IMAGE road_coin;
	IMAGE mon;
	IMAGE road_med;

	loadimage(&road_coin, L"road&coin.png");
	loadimage(&img_wall, L"wall.png");	//加载图片  L"背景.jpg"是图片的相对路径,也可以使用绝对路径
	loadimage(&img_road, L"road.png");
	loadimage(&you, L"player1.png");
	loadimage(&end, L"endpoint.png");
	loadimage(&mon, L"mon&road.png");
	loadimage(&road_med, L"road&med.png");

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
			else if (room[i][j] == ROAD || YOU)
			{
				if (med[i][j]==0)
					putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &img_road);
				else 
					putimagePng((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, &road_med);
				
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

void Cmonster::putMan(){

	IMAGE you;

	if (status == 0)
		loadimage(&you, L"player0.png");
	else if (status == 1)
		loadimage(&you, L"player1.png");
	else if (status == 2)
		loadimage(&you, L"player2.png");
	else if (status == 3)
		loadimage(&you, L"player3.png");
	putimagePng(216, 216, &you); // 绘制人物
	IMAGE mon;
	loadimage(&mon, L"mon&road.png");
	//if ((x + 4 >= mon_x&&y - 4 <= mon_y) || (x + 4 >= mon_x&&y + 4 >= mon_y) || (x - 4 <= mon_x&&y + 4 >= mon_y) || (x - 4 <= mon_x&&y - 4 <= mon_y))
	if (abs(x - mon_x) <= 4 && abs(y-mon_y)<=4)
	putimagePng((mon_y - 1 - y) * 50 + 266, (mon_x - 1 - x) * 50 + 266, &mon);

	if (med[x][y]){
		playmusic(1);
		meds--;
		hearts++;
		med[x][y] = 0;
	}

}
