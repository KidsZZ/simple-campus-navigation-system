#pragma once
#include <string>
#include<iostream>
#include "enum_lib.h"
#include<fstream>
#include <string>
#include <graphics.h>
class lines
{
public:
	lines() {};
	//构造函数，初始化数据
	lines(int length, int width, int row,int column,int fixed_length);
	//析构函数
	~lines();
	//绘制函数，绘制分割线（x,y）为地图左上角的点
	void draw(int x,int y);

	static int row;           //地图的行数
	static int column;        //地图的列数
	static int fixed_length;  //“线”的宽度
	static int length;        //地图长度
	static int width;         //地图宽度

};
