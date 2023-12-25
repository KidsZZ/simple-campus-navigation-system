﻿/*
此函数为程序主函数，在其中建立循环

循环基本逻辑为：
    1.读入消息并传输 2.处理消息 3.输出处理结果到画面

本程序通过键盘实现输入，使用方向键控制对地图中物体的选取，使用WASD控制旁边的功能栏



本项目使用easyx 大暑版作为绘图函数

本项目由郑喆宇和李佳徽合作完成，使用git以及github实现多人协作以及版本控制

本项目采用面向对象的编程思路，在完成头文件的编写后再编写函数的具体实现，实现分步走编程思路：
    1.完成项目宏观架构并论证可行性
    2.完成具体代码实现
优点：最大可能排除在项目开始编写后发现架构思路出错

包含《c++语言程序设计》一书中绝大部分的知识点，下面列出一些使用到的编程重点：
    1.虚函数
    2.stl容器vector
    3.自主设计页面切换的算法
    4.lambda表达式设置回调函数
*/

#include <iostream>
#include <graphics.h>
#include "Widget.h"

int main()
{   
    //创建应用程序窗口类
    Widget myWindow(1280,720);

    //运行应用程序
    myWindow.run();

}


