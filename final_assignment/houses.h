#pragma once
//class houses用于对地图中的建筑进行渲染
#include <graphics.h>
#include <string>
#include <vector>
#include "maps.h"
#include "enum_lib.h"
class houses {
public:
	//构造函数，初始化img对象(传入对象地址的通配形式，如img/img*.png，使用实际照片序号替换*标记）
	houses(std::wstring path, int n);
	//绘制函数:传入当前地图数据，并将房屋绘制上
	void draw(int width,int height,int x,int y);
	//为绘制道路提供此种类的房子是否在这个方向开门
	bool is_door(int direction, int house_type);
	//析构函数，析构img对象
	//不用设为虚函数，在子类中没有新的数据成员
	~houses();

private:
	//使用枚举类记录房子编号
	
	//储存房子的图片
	std::vector<IMAGE*> house_img;
	//储存大门的朝向，使用上左右下的顺序存储
	//开门为true，不开门为false
	std::vector<bool[4]> house_orientation;
};