//这是主页面窗口，管理不同页面（*因为easyx不支持多窗口，所以通过对不同窗口记录index值来切换不同窗口）
//使用abstract_page统一窗口接口，并使用vector<abstract_page*>进行统一储存和管理
//在run函数的循环结尾更新下次的网页编号，实现接收当前网页返回的下个网页的值
//对网页间的链接由具体网页的对象实现，不在widget类中进行链接

#pragma once

#include <vector>
#include <string>
#include "abstract_page.h"
#include "maps.h"
#include "enum_lib.h"


class Widget {

public:

	//构造函数
	//将四个页面载入my_page,设置页面长宽比，将now_page_id设为home_page_id
	Widget(int w,int h);

	//主成员函数
	//通过死循环依次执行用户信息读入，处理及绘图输入等步骤
	//使用GetTickCount()来实现动态延时，保证60帧刷新频率不会被程序运行时间改变
	void run();

	//关闭应用程序及网页
	//替代析构函数的功能，实现具体网页对象空间的释放
	void close();

private:
	
	//使用vector保存具体网页对象的指针，使用到了类的继承相关知识点中的隐含转换
	//将类的指针统一用abstract_page保存，体现了多态的思想，提高了代码复用性
	std::vector<abstract_page*> my_page;

	//页面id设置(废弃，使用统一my_mpas传参)
	//int previous_page_id = HOME_PAGE;
	
	//当前页面id
	//在run（）函数的末尾需要接收当前页面的返回值更新，使得页面的切换成为可能
	int now_page_id;

	//页面的宽和高
	//需要传递给各个页面的对象，完成对页面中不同元素的定位
	int width, height;

	//使用4个地图存档
	//目前未使用，仅作为记录
	static const int show_maps_num = 4;

	//保存储存地图数据的文件的地址
	//因为easyx主要支持宽字符，所以项目中的字符串都由wstring保存，然后使用.c_str()函数转换为c风格的字符串
	const std::string path;

	//保存地图信息
	//项目逻辑核心对象，实现对地图数据的保存，绘制和运算
	//非常重要
	//由于其一致性，只在widget中保存一份，其余通过引用的方式传递给各个页面
	maps my_maps;

};










