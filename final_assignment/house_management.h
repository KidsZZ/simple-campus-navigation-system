#pragma once
#include "houses.h"
#include "map.h"
#include <vector>
class house_management {
public:
	//默认构造函数，将现有house初始化
	house_management();
	//传入地图结构体，绘制房屋到地图上
	void draw(map& my_map);
	//析构函数
	~house_management();
private:
	std::vector <houses*> my_house;
};