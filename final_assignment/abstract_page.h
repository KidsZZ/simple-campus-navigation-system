#pragma once

//此类为抽象类，为四个页面类提供接口函数
//这是窗口的基类，在Widget.h中通过调用四个页面具体实现的函数实现页面间的切换

class abstract_page {
public:

	//设置下一个页面id，在初始化时设为自身，在程序运行时进行更改
	//设置页面的长宽比
	abstract_page(int next_id, int w, int h) :next_id(next_id), width(w), height(h) {
	};

	//更新地图数据函数（废弃，整个程序使用同一个maps保存地图数据）
	//virtual void update_maps() = 0;
	
	//信息接收函数
	//接收鼠标信息，进行处理
	virtual void get_keyboard_message() = 0;
	//绘制画面
	virtual void draw() = 0;
	//返回下一个页面序号(当返回EXIT时结束程序)
	int return_page_id() {
		return next_id;
	}
	//析构函数（虚函数）
	virtual ~abstract_page() {};
	void set_next_id(int id) {
		next_id = id;
	}
protected:
	//保存下一个页面的id
	int next_id;
	//保存页面横宽比;
	int width, height;
	//使用4个地图存档
	static const int show_maps_num = 4;
};