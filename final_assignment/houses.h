#pragma once
//class houses用于对地图中的建筑进行渲染
#include <graphics.h>
#include <string>
#include <vector>
#include "enum_lib.h"
#include<cstdlib>
class houses 
{
public:

	//构造函数，初始化img对象(传入对象地址的通配形式，如img/img*.png，使用实际照片序号替换*标记）
	houses(std::wstring path, int n);

	//绘制函数:传入当前地图数据，并将房屋绘制上
	void draw(int length,int x,int y,int house_type)const;

	//为绘制道路提供此种类的房子是否在这个方向开门
	//在此函数中调用了char_to_int函数进行转化类型操作
	bool is_door(int direction, char c)const;

	//析构函数，析构img对象
	//不用设为虚函数，在子类中没有新的数据成员
	~houses();


private:
	//使用枚举类记录房子编号
	//储存房子的图片
	std::vector<IMAGE*> house_img;

	//储存大门的朝向，使用上左右下的顺序存储
	//开门为true，不开门为false
	//预先开出足够的空间
	bool house_orientation[30][4];
};


















