
// Maze.cpp : ���򿪶��ļ�

#include "Game.h"						// ��Ϸͷ�ļ�
#pragma comment(lib,"Winmm.lib")

// ����������

int main()
{
srand((unsigned int)time(NULL));	// �������


initgraph(700, 480);				// ����ͼ�λ�����

CAdventure* bed = new CAdventure();
bed->game();						// ��ʼ��Ϸ

delete bed;
bed = NULL;

closegraph();
return 0;							// ��Ϸ����
}




