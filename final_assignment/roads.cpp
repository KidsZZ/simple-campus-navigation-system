#pragma once
//通过检索地图数据中的road位置，对道路图片进行渲染
#include"roads.h"


	//析构函数，释放道路图片
roads::	~roads()
{
	road_img.clear();
};
