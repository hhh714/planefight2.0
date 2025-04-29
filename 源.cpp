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
	//����
	settextcolor(WHITE);
	settextstyle(40, 0, _T("����"));
	outtextxy((BGWEIGHT - textwidth(_T("��Ϸ�淨"))) / 2, 120, _T("��Ϸ�淨"));
	settextstyle(20, 0, _T("����"));
	const TCHAR* instructions =
		_T("����˵����\n")
		_T("W/���� - �����ƶ�\n")
		_T("S/���� - �����ƶ�\n")
		_T("A/���� - �����ƶ�\n")
		_T("D/���� - �����ƶ�\n")
		_T("�ո�� - �����ӵ�\n\n")
		_T("����л���÷���\n")
		_T("������л���ײ");
	RECT rect = { 70,180,BGWEIGHT - 70,BGHEIGHT - 120 };
	drawtext(instructions, &rect, DT_WORDBREAK | DT_CENTER);
	const int closeBtnSize = 40;       // ��ť�ߴ�
	const int margin = 20;             // �߾�
	const int closeBtnx = BGWEIGHT - 50 - margin- closeBtnSize; // �ұ߽����
	const int closeBtny = 110;
	bool isHover=inarea(msg.x, msg.y, closeBtnx, closeBtny, closeBtnSize, closeBtnSize);
	// ��̬��ɫ����ͣʱ���
	if (isHover) 
	{
		setfillcolor(0xFF3333);  // ��ͣ��ɫ
		setlinecolor(0xFFFFFFFF); // ��ɫ�߿�
	}
	else 
	{
		setfillcolor(0xFF5555);  // Ĭ����ɫ
		setlinecolor(0x7FFFFFFF); // ��͸���ױ߿�
	}

	// ���ƴ��߿��Բ�ǰ�ť
	setlinestyle(PS_SOLID, 2);
	fillroundrect(closeBtnx, closeBtny,
		closeBtnx + closeBtnSize,
		closeBtny + closeBtnSize, 8, 8);
	roundrect(closeBtnx, closeBtny,
		closeBtnx + closeBtnSize,
		closeBtny + closeBtnSize, 8, 8);

	// ���ƹرշ���"��"
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
	
	
	//����ͼƬ
	IMAGE img_start;
	loadimage(&img_start, "res/startscene.jpg", BGWEIGHT, BGHEIGHT);
	const int btnx = 100, btny = 400, btnw = 150, btnh = 70;
	const int menubtny = btny + btnh + 20;

	bool isClicked = false;
	bool showmenu = false;
	while (true)
	{
		// ��Ϣ����
		while (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN) 
			{
				if (showmenu)
				{
					// �����水ť���
					if (inarea(msg.x, msg.y, BGWEIGHT - 50 - 20 - 40, 110, 40, 40))
					{
						showmenu = false;
					}
				}
					else
				{
						// �����水ť���
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

		// ���ƿ�ʼ��ť
		setfillcolor(inarea(msg.x, msg.y, btnx, btny, btnw, btnh) ? BLUE : RED);
		fillroundrect(btnx, btny, btnx + btnw, btny + btnh, 10, 10);

		// ���Ʋ˵���ť����ͬ��ʽ��
		setfillcolor(inarea(msg.x, msg.y, btnx, menubtny, btnw, btnh) ? BLUE : RED);
		fillroundrect(btnx, menubtny, btnx + btnw, menubtny + btnh, 10, 10);

		// ��ť����
		settextstyle(30, 0, _T("����"));
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		outtextxy(btnx + 20, btny + 20, _T("��ʼ��Ϸ"));
		outtextxy(btnx + 20, menubtny + 20, _T("��Ϸ�淨"));

		// ��ʾ�淨�˵�
		if (showmenu) {
			showgameinstructions();
		}
		EndBatchDraw();
		Sleep(8);
	}
	
	closegraph();

	
	//��Ϸ��ʼ�ĺ���
	
	start();
	return 0;




}