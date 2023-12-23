//本文件实现对widget.h中对象的具体代码实现
#include "Widget.h"

//enum_lib是一个单独储存程序需要用到的常量的库（命名常量便于信息传递）
#include "enum_lib.h"

//include四个具体网页的头文件
#include "home_page.h"
#include "navigation_page.h"
#include "map_select_page.h"
#include "map_editing_page.h"

//easyx头文件
#include <graphics.h>

//构造函数
//完成对类中各种变量的初始化
//将将地图数据保存在项目的map_lib文件夹下
//将初始的界面设置为home_page
Widget::Widget(int w, int h) :width(w),height(h),now_page_id(page_id::HOME_PAGE),path(L"maps_lib/"),my_maps(path) {

	//由widget类展开创建程序窗口
	//各个页面实现对widget类创建的窗口的具体绘制
	//通过绘制不同内容实现不同窗口
	initgraph(width, height);

	//初始化四个页面
	//开始界面
	my_page.push_back(new home_page(width, height));
	//地图选择界面
	my_page.push_back(new map_select_page(width, height,my_maps));
	//地图编辑界面
	my_page.push_back(new map_editing_page(width, height, my_maps));
	//地图导航界面
	my_page.push_back(new navigation_page(width, height, my_maps));
}

//widget主函数，实现循环
void Widget::run() {
	//记录当前状态，当running为false时退出循环	
	bool running = true;

	//使用渲染缓冲区,防止闪屏
	//使用此方法后，会将接下来绘制的画面全部绘制在另一个图层上
	//然后一次性呈现到画面上
	BeginBatchDraw();

	//主逻辑运行区
	while (running) {

		//获得当前时间
		DWORD start_time = GetTickCount();

		//处理输入
		//页面对象会在此函数中更新相关参数
		my_page[now_page_id]->get_keyboard_message();

		//将结果输出到画布上
		//页面对象将更新过的参数绘制到画布上
		my_page[now_page_id]->draw();

		//接收页面返回的下一个页面的索引
		now_page_id = my_page[now_page_id]->return_page_id();

		//如果页面返回的是exit，则退出循环，退出程序
		if (now_page_id == page_id::EXIT) {
			running = false;
		}

		//切换画布，将绘制好的图案一次性呈现到画布上
		FlushBatchDraw();

		//获取当前时间
		DWORD end_time = GetTickCount();

		//计算此次循环程序运行了多长时间
		DWORD delta_time = end_time - start_time;

		//使用动态刷新
		//如果程序运行时间小于一帧需要的时间，则延时多出来的时间
		//当前为一秒60帧
		if (delta_time < 1000 / 60) {
			Sleep(1000 / 60 - delta_time);
		}
	}
	//关闭渲染缓冲区
	EndBatchDraw();
	return;
}

//程序关闭函数，完成动态内存分配的空间的内存释放
void Widget::close() {

	//关闭画布
	closegraph();

	//释放每一个页面对象
	while (!my_page.empty()) {

		//删除尾部指针指向空间分配的内存
		delete my_page.back();

		//释放尾部
		my_page.pop_back();
	}
}