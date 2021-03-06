// Game.h : 游戏类头文件

#pragma once		// 防止该头文件被多次调用

#include "GameMaze.h"	// 初始化头文件
#include "EasyXPng.h"

// 游戏类

// 刷新界面、放置按钮、输出对话框类
class COther
{
public:
	COther() {}
	~COther() {}
	
	void putAll();																											// 绘制背景
	bool button(int a, int b, wchar_t str[]);																				// 放置按钮
	int putMessageBox(int x, int y, int wight, int hight, wchar_t title[], wchar_t * text[], int g_num, int var = MY_OK);	// 输出对话框
};

// 冒险模式类
class CAdventure
{
public:
	int pass, all_pass;												// 关卡和总关卡
	int to_x, to_y, x, y, room[150][150], n, m;						// 终点坐标、任务坐标、迷宫地图储存和迷宫大小
	int mon_x, mon_y;												//怪物坐标
	int tot, reg[2600][2600], feg[2600][2600], flag[3][2600];	// 图节点总数、邻接矩阵、辅助邻接矩阵和迷宫中坐标与图节点编号关系记录
	bool fmap[150][150], tip[2600];								// 辅助迷宫地图、图节点是否走过记录
	int time_limit = 60;
	int status = 1;		   //代表人物的运动方向 0:上，1:下，2：左，3：右
	
	CAdventure() {}
	~CAdventure() {}
	
	virtual void game();									// 各模式（系列）核心

	bool winPut();											// 通过一关卡界面
	bool failPut(int flag=1);

	void man_Move();										// 人物移动处理
	void clear();											// 清空数据处理
	void monster_Move();

	int search(int x, int y);								// DFS 搜索生成迷宫核心
	int dfs(int step);										
	int my_line(int x_1, int y_1, int x_2, int y_2);		// 辅助函数
	void playmusic(int flag);
};

// 普通模式
class Cnormal : public CAdventure
{
public:
	Cnormal() {}
	~Cnormal() {}
	
	void game();	// 各模式（系列）核心


private:
	void deepFS();		// 随机生成迷宫
	void putRoom();	// 绘制界面
	void putMan(); //绘制人物
};

//金币模式
class Ccoin : public CAdventure
{
public:
	int coins = 0;
	int coins_limit=5; //代表要求得到的金币数量
	int coin[150][150];//代表金币的位置。
	
	Ccoin() {
		memset(coin, 0, sizeof(coin));
	}
	~Ccoin() {}
	
	void game();	// 各模式（系列）核心
	

private:
	void deepFS();	// 随机生成迷宫
	void putRoom(); // 绘制界面
	void putMan(); //绘制人物
};

//极限模式
class Cextreme : public CAdventure
{
public:
	Cextreme() {}
	~Cextreme() {}
	
	void game();	// 各模式（系列）核心

private:
	void deepFS();		// 随机生成迷宫
	void putRoom(); // 绘制界面
	void putMan(); //绘制人物
};

//怪物模式
class Cmonster :public CAdventure{

public:
	
	int med[150][150];//代表药品的位置。
	int meds = 0;
	int meds_limit = 3;
	void game();
	Cmonster(){
		memset(med, 0, sizeof med);
	}
	~Cmonster(){}

private:
	void deepFS();	//随机生成迷宫
	void putRoom(int flag); //绘制界面
	void putMan();  //绘制人物
	
};