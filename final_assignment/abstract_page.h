#pragma once

//此类为抽象类，为四个页面类提供接口函数
//这是窗口的基类，在Widget.h中通过调用四个页面具体实现的函数实现页面间的切换

class abstract_page {
public:

	//设置下一个页面id，在初始化时设为自身，在程序运行时进行更改
	//设置页面的长宽比
	abstract_page(int next_id, int w, int h) :next_id(next_id), width(w), height(h) ,return_flag(false){
	};

	//更新地图数据函数（废弃，整个程序使用同一个maps保存地图数据）
	//virtual void update_maps() = 0;
	
	//信息接收函数
	//接收鼠标信息，进行处理
	virtual void get_keyboard_message() = 0;

	//绘制画面
	//通过储存在页面对象中的数据（在接收鼠标信息时更新），绘制新画面
	//需要完全覆盖原来的画面重新绘制
	virtual void draw() = 0;

	//返回下一个页面序号(当返回EXIT时结束程序)
	virtual int return_page_id() = 0;

	//设置下一个页面的id
	//给按钮等部件设置下一个页面提供统一的接口
	void set_next_id(int id) {
		return_flag = true;
		next_id = id;
	}

	//防止页面释放时出现问题
	//析构函数（虚函数）
	virtual ~abstract_page() {};

//基类中的数据成员保存每个页面通用的数据
protected:

	//保存下一个页面的id
	int next_id;

	//保存页面横宽比;
	int width, height;

	//使用4个地图存档
	static const int show_maps_num = 4;

	//确保再次回到页面不会闪屏
	bool return_flag;
};











