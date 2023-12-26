#pragma once
//通过检索地图数据中的road位置，对道路图片进行渲染
#include <vector>
#include <graphics.h>
#include "enum_lib.h"
#include<string>
class roads 
{
public:

	//构造函数，载入道路图片
	roads(std::wstring path, int n);

	//绘制函数，传入存放地图信息的结构体进行绘制
	void draw(int length,int x,int y,int direction)const;

	//析构函数，释放道路图片
	~roads();
	
private:

	//创建vector数组存放IMAGE*类的数据，命名为road_img
	std::vector<IMAGE*> road_img;
};











