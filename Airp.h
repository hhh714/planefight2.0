//1、打开窗口，加载图片，链表结构、变量的定义
// 2、生成我方飞机、我方飞机的移动
//3、子弹的生成、发射、释放
//4、敌机生成移动和销毁
//5、子弹消灭敌机
//6、敌机与我方飞机的碰撞
//7、得分的显示
//8、音乐的播放
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
#pragma comment(lib,"winmm.lib")//把音乐包含进来

#define BGWEIGHT 400
#define BGHEIGHT 600
//我方飞机大小
#define myairweight 60
#define myairheight 80

//敌机大小
#define enemyweight 60
#define enemyheight 60
//子弹大小
#define zidanweight 30
#define zidanheight 30


//定义变量
IMAGE img[4];//图片数组
Node myplane;//我方飞机
LL mybullut;//我方子弹链表
LL enemyplane;//敌方飞机链表
int isend;
int count;




void init()
{
//加载图片
	//1、绝对路径：带盘符的路径
	//2、相对路径
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

	//我方飞机的初始化
	myplane.x = BGWEIGHT / 2 - myairweight / 2;
	myplane.y = BGHEIGHT - myairheight - 10;
	myplane.speed=10 ;
	myplane.next = NULL;

	//子单链表的初始化
	mybullut.head = NULL;
	mybullut.end = NULL;

	//敌方飞机的初始化
	enemyplane.head = NULL;
	enemyplane.end = NULL;

	//播下随机生成的种子
	srand((unsigned)time(NULL));
	isend = 0;//为1时，游戏结束
	count = 0;

	//加载音乐
	mciSendString("open res/music.mp3", NULL, 0, 0);
	mciSendString("play res/music.mp3", NULL, 0, 0);
}
//把图片贴在图形界面上
void draw()
{
//开始批量绘图
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
	//显示得分
	TCHAR str1[30];
	wsprintf(str1, "当前得分 ：%d", count);
	outtextxy(0, 0, str1);
	setbkcolor(0xcccccc);//设置文本背景颜色
	settextcolor(BLACK);


	//结束批量绘图
	EndBatchDraw();


}

//生成子弹的函数
void create_mybullut()
{
	LinkList_insert(&mybullut, myplane.x + myairweight / 2 - zidanweight, myplane.y, 5);

}


//玩游戏函数：控制飞机的移动
void play()
{
	if (_kbhit())//如果有键盘按下，才会执行语句，否则跳过
	{
		switch (_getch())//等待从键盘上输入字符
		{
			case 'w':
			case 'W':
			case 72://上键
				if(myplane.y>=0)
				myplane.y -= myplane.speed;
				break;
			case 's':
			case 'S':
			case 80://下键
				if(myplane.y<=BGHEIGHT-myairheight)
				myplane.y += myplane.speed;
				break;
			case 'a':
			case 'A':
			case 75://左键
				if(myplane.x>=0)
				myplane.x -= myplane.speed;
				break;
			case 'd':
			case 'D':
			case 77://右键
				if(myplane.x<=BGWEIGHT-myairweight)
				myplane.x += myplane.speed;
				break;
			case ' ':create_mybullut();
				break;
		}
	}
}

//我方子弹的移动 敌机的移动
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

//检测子弹与敌机是否发生碰撞
int blt_isconflict(Node*p,Node*q)  //p子弹q敌机
{
	//以中心点来判断
	int px = p->x + zidanweight / 2;
	int py = p->y + zidanheight / 2;
	int qx = q->x + enemyweight / 2;
	int qy = q->y + enemyheight / 2;

	//判断是否重叠
	if (abs(px - qx) < enemyheight / 2 + zidanweight / 2 && abs(py - qy) < enemyheight / 2 + zidanheight / 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

//检测我放飞机是否与敌机发生碰撞
int myplane_conflict(Node*p,Node*q)//p飞机q敌机
{
	//以中心点检测
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



//释放函数
void  Delete()
{
	//释放越界子弹
	for (Node* tempbullut = mybullut.head; tempbullut != NULL; tempbullut = tempbullut->next)
	{
		if (tempbullut->y < 0)
		{
			Node_delete(&mybullut, tempbullut);//一次删除一个节点
			return;
		}
	}
	//释放越界敌机

	for (Node* tempenenmy = enemyplane.head; tempenenmy != NULL; tempenenmy = tempenenmy->next)
	{
		if (tempenenmy->y >= BGHEIGHT)
		{
			Node_delete(&enemyplane, tempenenmy);
			return;
        }

	}

	//子弹消灭敌机
	//先遍历每一个子弹，在每一个子弹节点遍历所有敌机
	for (Node* tempbullut = mybullut.head; tempbullut != NULL; tempbullut = tempbullut->next)
	{
		for (Node* tempenemy = enemyplane.head; tempenemy != NULL; tempenemy = tempenemy->next)
		{
			if (blt_isconflict(tempbullut, tempenemy))
			{
				Node_delete(&mybullut, tempbullut);
				Node_delete(&enemyplane, tempenemy);
				count++;//得分加1
				return;
				
			}
			
		}
	}

	for (Node* temp = enemyplane.head; temp != NULL; temp = temp->next)
	{

		//敌机与我方飞机是否发生冲突
		if (myplane_conflict(&myplane, temp))
		{
			isend = 1;
			return;
		}

	}



}
//敌机的生成
void enemy_create()
{
	static int val = 0;//限制敌机生成
	if (val >= 100)
	{
		LinkList_insert(&enemyplane, rand() % (BGWEIGHT - enemyweight), -enemyheight,rand()%5+1);
		val = 0;
	}
	val++;
}







//所有功能从这个函数开始
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


			
			LinkList_all(&mybullut);//释放所有子弹节点
			LinkList_all(&enemyplane);

			

			//跳出弹窗：提示失败
			TCHAR str[50];
			mciSendString("open res/endingmusic.mp3", NULL, 0, 0);
			mciSendString("play res/endingmusic.mp3", NULL, 0, 0);

			wsprintf(str, "得分：%d    是否重新开始游戏", count);
			int temp= MessageBox(GetForegroundWindow(), str, "游戏失败",MB_YESNO);
			if (temp == IDYES)
			{
				
				init();//初始化游戏
			}
			else
			{
			
				break;

			}
		}

	}
	closegraph();
}