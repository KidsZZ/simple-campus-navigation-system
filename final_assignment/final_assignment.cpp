/*
此函数为程序主函数，在其中建立循环

循环基本逻辑为：
    1.读入消息并传输 2.处理消息 3.输出处理结果到画面

本程序通过键盘实现输入，使用方向键控制对地图中物体的选取，使用WASD控制旁边的功能栏
*/

#include <iostream>
#include <graphics.h>
#include "Widget.h"

int main()
{
    Widget myWindow(1280,720);
    myWindow.run();
    myWindow.close();
}
