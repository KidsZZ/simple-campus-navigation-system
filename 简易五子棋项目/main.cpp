#include <graphics.h>
#include <vector>
#include <conio.h>
#include <ctime>
#include <cmath>
#include<Windows.h>
#pragma comment( lib, "MSIMG32.LIB")
const int n = 15;

const int x = 50;
const int y = 50;

int chess_len = 30;//棋子长度

int current_x = 0;//当前坐标
int current_y = 0;

int current_play = 1;//当前下棋角色，1表示白棋，2表示黑棋
IMAGE bk;//背景图片
IMAGE white;//白棋
IMAGE black;//黑棋
int map[n + 1][n + 1] = { 0 };//棋盘数组
bool isEnd = false;//游戏结束标志

void putTranspareImage(IMAGE* target, int x, int y, IMAGE* source)
{
	/*在屏幕上显示透明贴图函数*/
	HDC targetDc = GetImageHDC(target);
	HDC sourceDc = GetImageHDC(source);
	int w = (*source).getwidth();
	int h = (*source).getheight();

	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	//使用 Windows GDI 函数实现半透明位图
	AlphaBlend(targetDc, x, y, w, h, sourceDc, 0, 0, w, h, bf);
}

//判断游戏是否结束
void judge() {
	bool l = true, r = true;
	int count = 0;

	for (int i = 1; i <= 4; ++i) {
		if (l && current_y - i >= 0) {
			if (map[current_x][current_y - i] == current_play) {	//判断左右直线
				count++;
			}
			else {
				l = false;
			}
		}
		if (r && current_y + i <= n) {
			if (map[current_x][current_y + i] == current_play) {
				count++;
			}
			else {
				r = false;
			}
		}
	}
	if (count >= 4) {
		isEnd = true;
		return;
	}

	l = r = true;
	count = 0;
	for (int i = 1; i <= 4; ++i) {
		if (l && current_x - i >= 0) {
			if (map[current_x - i][current_y] == current_play) {	//判断上下直线
				count++;
			}
			else {
				l = false;
			}
		}
		if (r && current_x + i <= n) {
			if (map[current_x + i][current_y] == current_play) {
				count++;
			}
			else {
				r = false;
			}
		}
	}
	if (count >= 4) {
		isEnd = true;
		return;
	}

	l = r = true;
	count = 0;
	for (int i = 1; i <= 4; ++i) {	//左上到右下的直线
		if (l && current_x - i >= 0 && current_y - i >= 0) {
			if (map[current_x - i][current_y - i] == current_play) {
				count++;
			}
			else {
				l = false;
			}
		}
		if (r && current_x + i <= n && current_y + i <= n) {
			if (map[current_x + i][current_y + i] == current_play) {
				count++;
			}
			else {
				r = false;
			}
		}
	}
	if (count >= 4) {
		isEnd = true;
		return;
	}

	l = r = true;
	count = 0;
	for (int i = 1; i <= 4; ++i) {	//右上到左下的直线
		if (l && current_x - i >= 0 && current_y + i <= n) {
			if (map[current_x - i][current_y + i] == current_play) {
				count++;
			}
			else {
				l = false;
			}
		}
		if (r && current_x + i <= n && current_y - i >= 0) {
			if (map[current_x + i][current_y - i] == current_play) {
				count++;
			}
			else {
				r = false;
			}
		}
	}
	if (count >= 4) {
		isEnd = true;
		return;
	}
}

//更新棋盘
void updata(BYTE vkcode) {
	if (vkcode == 0x41) {   //A键
		if (current_y - 1 >= 0) {
			current_y -= 1;
		}
	}
	else if (vkcode == 0x44) {//D
		if (current_y + 1 <= n) {
			current_y += 1;
		}
	}
	else if (vkcode == 0x57) {//W
		if (current_x - 1 >= 0) {
			current_x -= 1;
		}
	}
	else if (vkcode == 0x53) {//S
		if (current_x + 1 <= n) {
			current_x += 1;
		}
	}
	else if (vkcode == VK_SPACE) {//空格
		if (!map[current_x][current_y]) {
			map[current_x][current_y] = current_play;
			judge();
			current_play = 3 - current_play;
		}
	}
}

//绘制
void draw() {

	//背景
	putimage(0, 0, &bk);

	//绘制棋盘
	setlinecolor(BLACK);
	for (int i = 0; i <= n; ++i) {
		line(x, y + i * chess_len, x + n * chess_len, y + i * chess_len);
		line(x + i * chess_len, y, x + i * chess_len, y + n * chess_len);
	}

	//在当前位置绘制红色框框
	setlinecolor(RED);
	rectangle(x + current_y * chess_len - chess_len / 2, y + current_x * chess_len - chess_len / 2,
		x + current_y * chess_len + chess_len / 2, y + current_x * chess_len + chess_len / 2);

	//绘制棋子
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			if (map[i][j] == 1) {
				putTranspareImage(NULL, x + j * chess_len - 14, y + i * chess_len - 14, &white);
			}
			else if (map[i][j] == 2) {
				putTranspareImage(NULL, x + j * chess_len - 14, y + i * chess_len - 14, &black);
			}
		}
	}
	setlinecolor(BLACK);
	rectangle(550, 50, 750, 350);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, L"宋体");
	outtextxy(575, 50, L"出棋方");
	if (current_play == 1) {
		setfillcolor(WHITE);
	}
	else if (current_play == 2) {
		setfillcolor(BLACK);
	}
	solidcircle(650, 200, 80);
}

int main() {
	loadimage(&bk, L"back.jpg");
	loadimage(&white, L"bai.png", 28, 28);
	loadimage(&black, L"hei.png", 28, 28);
	initgraph(800, 600);
	ExMessage msg;
	BeginBatchDraw();
	while (!isEnd) {

		if (peekmessage(&msg, EM_KEY)) {
			if (msg.message == WM_KEYUP) {
				updata(msg.vkcode);
			}
		}
		draw();
		FlushBatchDraw();
		Sleep(10);
		cleardevice();
	}

	MessageBox(GetHWnd(), current_play == 1 ? L"游戏结束，黑棋获胜！" : L"游戏结束，白棋获胜！", L"Game Over", MB_OK);
	EndBatchDraw();
}