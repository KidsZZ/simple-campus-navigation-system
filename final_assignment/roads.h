#pragma once
//通过检索地图数据中的road位置，对道路图片进行渲染
#include <vector>
#include <graphics.h>
#include "map.h"
#include "enum_lib.h"
#include<string>
class roads {
public:
	//构造函数，载入道路图片
	roads();
	//析构函数，释放道路图片
	~roads();
	//绘制函数，传入存放地图信息的结构体进行绘制
	void draw(int width,int height,int x,int y,int direction);
	
private:
	std::vector<IMAGE*> road_img;
};