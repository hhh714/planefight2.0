//1���򿪴��ڣ�����ͼƬ������ṹ�������Ķ���
// 2�������ҷ��ɻ����ҷ��ɻ����ƶ�
//3���ӵ������ɡ����䡢�ͷ�
//4���л������ƶ�������
//5���ӵ�����л�
//6���л����ҷ��ɻ�����ײ
//7���÷ֵ���ʾ
//8�����ֵĲ���
#include<easyx.h>
#include"list.h"
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<mmsystem.h>
#include<windows.h>
#include<graphics.h>

#pragma comment(lib,"MSIMG32.LIB")
#pragma warning(disable.4996)
#pragma comment(lib,"winmm.lib")//�����ְ�������

#define BGWEIGHT 400
#define BGHEIGHT 600
//�ҷ��ɻ���С
#define myairweight 60
#define myairheight 80

//�л���С
#define enemyweight 60
#define enemyheight 60
//�ӵ���С
#define zidanweight 30
#define zidanheight 30


//�������
IMAGE img[4];//ͼƬ����
Node myplane;//�ҷ��ɻ�
LL mybullut;//�ҷ��ӵ�����
LL enemyplane;//�з��ɻ�����
int isend;
int count;




void init()
{
//����ͼƬ
	//1������·�������̷���·��
	//2�����·��
	loadimage(&img[0], "res/bkground.jpg",BGWEIGHT,BGHEIGHT);
	loadimage(&img[1], "res/myplane.png", myairweight, myairheight);
	setbkcolor(WHITE);
	setcolor(WHITE);

	loadimage(&img[2], "res/enemyplane.png", enemyweight, enemyheight);
	setbkcolor(WHITE);
	setcolor(WHITE);
	loadimage(&img[3], "res/mybullut.png", zidanweight, zidanheight);
	setbkcolor(WHITE);
	setcolor(WHITE);

	//�ҷ��ɻ��ĳ�ʼ��
	myplane.x = BGWEIGHT / 2 - myairweight / 2;
	myplane.y = BGHEIGHT - myairheight - 10;
	myplane.speed=10 ;
	myplane.next = NULL;

	//�ӵ�����ĳ�ʼ��
	mybullut.head = NULL;
	mybullut.end = NULL;

	//�з��ɻ��ĳ�ʼ��
	enemyplane.head = NULL;
	enemyplane.end = NULL;

	//����������ɵ�����
	srand((unsigned)time(NULL));
	isend = 0;//Ϊ1ʱ����Ϸ����
	count = 0;

	//��������
	mciSendString("open res/music.mp3", NULL, 0, 0);
	mciSendString("play res/music.mp3", NULL, 0, 0);
}
//��ͼƬ����ͼ�ν�����
void draw()
{
//��ʼ������ͼ
	BeginBatchDraw();
	putimage(0, 0, &img[0]);
	putimage(myplane.x, myplane.y, &img[1],SRCAND);
	//putimage(100, 100, &img[2]);
	for (Node* temp = enemyplane.head; temp != NULL; temp = temp->next)
	{
		putimage(temp->x, temp->y, &img[2],SRCAND);
	}
	//putimage (200,200, &img[3]);
	for (Node* temp = mybullut.head; temp != NULL; temp = temp->next)
	{
		putimage(temp->x, temp->y, &img[3],SRCAND);
	}
	//��ʾ�÷�
	TCHAR str1[30];
	wsprintf(str1, "��ǰ�÷� ��%d", count);
	outtextxy(0, 0, str1);
	setbkcolor(0xcccccc);//�����ı�������ɫ
	settextcolor(BLACK);


	//����������ͼ
	EndBatchDraw();


}

//�����ӵ��ĺ���
void create_mybullut()
{
	LinkList_insert(&mybullut, myplane.x + myairweight / 2 - zidanweight, myplane.y, 5);

}


//����Ϸ���������Ʒɻ����ƶ�
void play()
{
	if (_kbhit())//����м��̰��£��Ż�ִ����䣬��������
	{
		switch (_getch())//�ȴ��Ӽ����������ַ�
		{
			case 'w':
			case 'W':
			case 72://�ϼ�
				if(myplane.y>=0)
				myplane.y -= myplane.speed;
				break;
			case 's':
			case 'S':
			case 80://�¼�
				if(myplane.y<=BGHEIGHT-myairheight)
				myplane.y += myplane.speed;
				break;
			case 'a':
			case 'A':
			case 75://���
				if(myplane.x>=0)
				myplane.x -= myplane.speed;
				break;
			case 'd':
			case 'D':
			case 77://�Ҽ�
				if(myplane.x<=BGWEIGHT-myairweight)
				myplane.x += myplane.speed;
				break;
			case ' ':create_mybullut();
				break;
		}
	}
}

//�ҷ��ӵ����ƶ� �л����ƶ�
void move()
{
	for (Node* temp = mybullut.head; temp != NULL; temp = temp->next)
	{
		temp->y -= temp->speed;

	}
	for (Node* tempenemy = enemyplane.head; tempenemy != NULL; tempenemy = tempenemy->next)
	{
		tempenemy->y += tempenemy->speed;
	}
}

//����ӵ���л��Ƿ�����ײ
int blt_isconflict(Node*p,Node*q)  //p�ӵ�q�л�
{
	//�����ĵ����ж�
	int px = p->x + zidanweight / 2;
	int py = p->y + zidanheight / 2;
	int qx = q->x + enemyweight / 2;
	int qy = q->y + enemyheight / 2;

	//�ж��Ƿ��ص�
	if (abs(px - qx) < enemyheight / 2 + zidanweight / 2 && abs(py - qy) < enemyheight / 2 + zidanheight / 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

//����ҷŷɻ��Ƿ���л�������ײ
int myplane_conflict(Node*p,Node*q)//p�ɻ�q�л�
{
	//�����ĵ���
	int px = p->x + myairweight / 2;
	int py = p->y + myairheight / 2;
	int qx = q->x + enemyweight / 2;
	int qy = q->y + enemyheight / 2;
	if (abs(px - qx) < enemyweight / 2 + myairweight / 2 && abs(py - qy) < enemyheight / 2 + myairheight / 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}


}



//�ͷź���
void  Delete()
{
	//�ͷ�Խ���ӵ�
	for (Node* tempbullut = mybullut.head; tempbullut != NULL; tempbullut = tempbullut->next)
	{
		if (tempbullut->y < 0)
		{
			Node_delete(&mybullut, tempbullut);//һ��ɾ��һ���ڵ�
			return;
		}
	}
	//�ͷ�Խ��л�

	for (Node* tempenenmy = enemyplane.head; tempenenmy != NULL; tempenenmy = tempenenmy->next)
	{
		if (tempenenmy->y >= BGHEIGHT)
		{
			Node_delete(&enemyplane, tempenenmy);
			return;
        }

	}

	//�ӵ�����л�
	//�ȱ���ÿһ���ӵ�����ÿһ���ӵ��ڵ�������ел�
	for (Node* tempbullut = mybullut.head; tempbullut != NULL; tempbullut = tempbullut->next)
	{
		for (Node* tempenemy = enemyplane.head; tempenemy != NULL; tempenemy = tempenemy->next)
		{
			if (blt_isconflict(tempbullut, tempenemy))
			{
				Node_delete(&mybullut, tempbullut);
				Node_delete(&enemyplane, tempenemy);
				count++;//�÷ּ�1
				return;
				
			}
			
		}
	}

	for (Node* temp = enemyplane.head; temp != NULL; temp = temp->next)
	{

		//�л����ҷ��ɻ��Ƿ�����ͻ
		if (myplane_conflict(&myplane, temp))
		{
			isend = 1;
			return;
		}

	}



}
//�л�������
void enemy_create()
{
	static int val = 0;//���Ƶл�����
	if (val >= 100)
	{
		LinkList_insert(&enemyplane, rand() % (BGWEIGHT - enemyweight), -enemyheight,rand()%5+1);
		val = 0;
	}
	val++;
}







//���й��ܴ����������ʼ
void start()
{
	initgraph(BGWEIGHT, BGHEIGHT,EX_SHOWCONSOLE);
	init();
	draw();
	while (1)
	{
		play();
		draw();
		move();
		Sleep(8);
		Delete();
		enemy_create();
		
		if (isend == 1)
		{
			mciSendString("stop res/music.mp3", NULL, 0, 0);


			
			LinkList_all(&mybullut);//�ͷ������ӵ��ڵ�
			LinkList_all(&enemyplane);

			

			//������������ʾʧ��
			TCHAR str[50];
			mciSendString("open res/endingmusic.mp3", NULL, 0, 0);
			mciSendString("play res/endingmusic.mp3", NULL, 0, 0);

			wsprintf(str, "�÷֣�%d    �Ƿ����¿�ʼ��Ϸ", count);
			int temp= MessageBox(GetForegroundWindow(), str, "��Ϸʧ��",MB_YESNO);
			if (temp == IDYES)
			{
				
				init();//��ʼ����Ϸ
			}
			else
			{
			
				break;

			}
		}

	}
	closegraph();
}