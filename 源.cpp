#include"Airp.h"
ExMessage msg = { 0 };






bool inarea(int mx, int my, int x, int y, int w, int h)
{
	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}
	return false;
}
void showgameinstructions()
{
	setfillcolor(0x7F000000);
	solidrectangle(50, 100, BGWEIGHT - 50, BGHEIGHT - 100);
	//标题
	settextcolor(WHITE);
	settextstyle(40, 0, _T("宋体"));
	outtextxy((BGWEIGHT - textwidth(_T("游戏玩法"))) / 2, 120, _T("游戏玩法"));
	settextstyle(20, 0, _T("宋体"));
	const TCHAR* instructions =
		_T("操作说明：\n")
		_T("W/↑键 - 向上移动\n")
		_T("S/↓键 - 向下移动\n")
		_T("A/←键 - 向左移动\n")
		_T("D/→键 - 向右移动\n")
		_T("空格键 - 发射子弹\n\n")
		_T("击落敌机获得分数\n")
		_T("避免与敌机碰撞");
	RECT rect = { 70,180,BGWEIGHT - 70,BGHEIGHT - 120 };
	drawtext(instructions, &rect, DT_WORDBREAK | DT_CENTER);
	const int closeBtnSize = 40;       // 按钮尺寸
	const int margin = 20;             // 边距
	const int closeBtnx = BGWEIGHT - 50 - margin- closeBtnSize; // 右边界计算
	const int closeBtny = 110;
	bool isHover=inarea(msg.x, msg.y, closeBtnx, closeBtny, closeBtnSize, closeBtnSize);
	// 动态颜色（悬停时加深）
	if (isHover) 
	{
		setfillcolor(0xFF3333);  // 悬停颜色
		setlinecolor(0xFFFFFFFF); // 白色边框
	}
	else 
	{
		setfillcolor(0xFF5555);  // 默认颜色
		setlinecolor(0x7FFFFFFF); // 半透明白边框
	}

	// 绘制带边框的圆角按钮
	setlinestyle(PS_SOLID, 2);
	fillroundrect(closeBtnx, closeBtny,
		closeBtnx + closeBtnSize,
		closeBtny + closeBtnSize, 8, 8);
	roundrect(closeBtnx, closeBtny,
		closeBtnx + closeBtnSize,
		closeBtny + closeBtnSize, 8, 8);

	// 绘制关闭符号"×"
	setlinestyle(PS_SOLID, 3);
	line(closeBtnx + 10, closeBtny + 10,
		closeBtnx + closeBtnSize - 10,
		closeBtny + closeBtnSize - 10);
	line(closeBtnx + 10, closeBtny + closeBtnSize - 10,
		closeBtnx + closeBtnSize - 10,
		closeBtny + 10);
}




int main()
{
	initgraph(BGWEIGHT, BGHEIGHT);
	
	
	//加载图片
	IMAGE img_start;
	loadimage(&img_start, "res/startscene.jpg", BGWEIGHT, BGHEIGHT);
	const int btnx = 100, btny = 400, btnw = 150, btnh = 70;
	const int menubtny = btny + btnh + 20;

	bool isClicked = false;
	bool showmenu = false;
	while (true)
	{
		// 消息处理
		while (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN) 
			{
				if (showmenu)
				{
					// 主界面按钮检测
					if (inarea(msg.x, msg.y, BGWEIGHT - 50 - 20 - 40, 110, 40, 40))
					{
						showmenu = false;
					}
				}
					else
				{
						// 主界面按钮检测
						if (inarea(msg.x, msg.y, btnx, btny, btnw, btnh)) {
							isClicked = true;
							break;
						}
						if (inarea(msg.x, msg.y, btnx, menubtny, btnw, btnh)) {
							showmenu = true;
					}
				}
			}
		}
	
	if (isClicked) break;

		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img_start);

		// 绘制开始按钮
		setfillcolor(inarea(msg.x, msg.y, btnx, btny, btnw, btnh) ? BLUE : RED);
		fillroundrect(btnx, btny, btnx + btnw, btny + btnh, 10, 10);

		// 绘制菜单按钮（相同样式）
		setfillcolor(inarea(msg.x, msg.y, btnx, menubtny, btnw, btnh) ? BLUE : RED);
		fillroundrect(btnx, menubtny, btnx + btnw, menubtny + btnh, 10, 10);

		// 按钮文字
		settextstyle(30, 0, _T("宋体"));
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		outtextxy(btnx + 20, btny + 20, _T("开始游戏"));
		outtextxy(btnx + 20, menubtny + 20, _T("游戏玩法"));

		// 显示玩法菜单
		if (showmenu) {
			showgameinstructions();
		}
		EndBatchDraw();
		Sleep(8);
	}
	
	closegraph();

	
	//游戏开始的函数
	
	start();
	return 0;




}