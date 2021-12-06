// Game.h : ��Ϸ��ͷ�ļ�

#pragma once		// ��ֹ��ͷ�ļ�����ε���

#include "GameMaze.h"	// ��ʼ��ͷ�ļ�
#include "EasyXPng.h"

// ��Ϸ��

// ˢ�½��桢���ð�ť������Ի�����
class COther
{
public:
	COther() {}
	~COther() {}
	
	void putAll();																											// ���Ʊ���
	bool button(int a, int b, wchar_t str[]);																				// ���ð�ť
	int putMessageBox(int x, int y, int wight, int hight, wchar_t title[], wchar_t * text[], int g_num, int var = MY_OK);	// ����Ի���
};

// ð��ģʽ��
class CAdventure
{
public:
	int pass, all_pass;												// �ؿ����ܹؿ�
	int to_x, to_y, x, y, room[150][150], n, m;						// �յ����ꡢ�������ꡢ�Թ���ͼ������Թ���С
	int mon_x, mon_y;												//��������
	int tot, reg[2600][2600], feg[2600][2600], flag[3][2600];	// ͼ�ڵ��������ڽӾ��󡢸����ڽӾ�����Թ���������ͼ�ڵ��Ź�ϵ��¼
	bool fmap[150][150], tip[2600];								// �����Թ���ͼ��ͼ�ڵ��Ƿ��߹���¼
	int time_limit = 60;
	int status = 1;		   //����������˶����� 0:�ϣ�1:�£�2����3����
	
	CAdventure() {}
	~CAdventure() {}
	
	virtual void game();									// ��ģʽ��ϵ�У�����

	bool winPut();											// ͨ��һ�ؿ�����
	bool failPut(int flag=1);
	void gameOver();										// ͨ��ȫ�ؿ�����
	void man_Move();										// �����ƶ�����
	void clear();											// ������ݴ���
	void monster_Move();

	int search(int x, int y);								// DFS ���������Թ�����
	int dfs(int step);										// ͼ�� DFS ���������Թ�����
	int my_line(int x_1, int y_1, int x_2, int y_2);		// ��������
	void playmusic();
};

// ��ͨģʽ
class Cnormal : public CAdventure
{
public:
	Cnormal() {}
	~Cnormal() {}
	
	void game();	// ��ģʽ��ϵ�У�����


private:
	void deepFS();		// ��������Թ�
	void putRoom();	// ���ƽ���
	void putMan(); //��������
};

//���ģʽ
class Ccoin : public CAdventure
{
public:
	int coins = 0;
	int coins_limit=5; //����Ҫ��õ��Ľ������
	int coin[150][150];//�����ҵ�λ�á�
	
	Ccoin() {
		memset(coin, 0, sizeof(coin));
	}
	~Ccoin() {}
	
	void game();	// ��ģʽ��ϵ�У�����
	

private:
	void deepFS();	// ��������Թ�
	void putRoom(); // ���ƽ���
	void putMan(); //��������
};

//����ģʽ
class Cextreme : public CAdventure
{
public:
	Cextreme() {}
	~Cextreme() {}
	
	void game();	// ��ģʽ��ϵ�У�����

private:
	void deepFS();		// ��������Թ�
	void putRoom(); // ���ƽ���
	void putMan(); //��������
};

//����ģʽ
class Cmonster :public CAdventure{

public:
	Cmonster(){}
	~Cmonster(){}
	
	void game();

private:
	void deepFS();	//��������Թ�
	void putRoom(); //���ƽ���
	void putMan();  //��������
	
};
// ������Ϣ��
class CHelp
{
public:
	CHelp() {}
	~CHelp() {}

	void put();		// ���ƽ���
};
