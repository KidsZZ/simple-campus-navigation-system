#pragma once
//class abstract_house是不同house类的基类，为house_management类通过多态进行管理提供接口函数
#include <graphics.h>
#include <string>
class abstract_house {
public:
	//构造函数，初始化img对象(在派生类的构造函数中要对基类成员进行个性化赋值
	abstract_house(std::string path);
	virtual int get_id() = 0;
	//绘制函数
	virtual void draw(int x, int y) = 0;
	//析构函数，析构img对象
	//不用设为虚函数，在子类中没有新的数据成员
	~abstract_house();
protected:
	//使用枚举类记录房子编号
	enum house_type{
		museum = 1,
		dorminory,
		teaching_building,
		canteen
	};
	//储存房子的
	IMAGE* img;
	//储存大门的朝向，使用上左下右的顺序存储
	//开门为true，不开门为false
	bool door_orientation[4];
};