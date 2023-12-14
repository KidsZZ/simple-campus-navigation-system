#pragma once
//class houses用于对地图中的建筑进行渲染
#include <graphics.h>
#include <string>
#include <vector>
#include "maps.h"
class houses {
public:
	//构造函数，初始化img对象(传入对象地址的通配形式，如img/img*.png，使用实际照片序号替换*标记）
	houses(std::string path,int n);
	//绘制函数:传入当前地图数据，并将房屋绘制上
	void draw(maps<> &my_maps);
	//析构函数，析构img对象
	//不用设为虚函数，在子类中没有新的数据成员
	~houses();
protected:
	//使用枚举类记录房子编号
	enum house_type{
		museum = 1,
		dorminory,
		teaching_building,
		canteen
	};
	//储存房子的
	std::vector<IMAGE*> house_img;
	//储存大门的朝向，使用上左下右的顺序存储
	//开门为true，不开门为false
	std::vector<bool[4]> house_orientation;
};