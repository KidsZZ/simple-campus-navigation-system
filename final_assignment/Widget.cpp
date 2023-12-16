#include "Widget.h"
#include "home_page.h"
#include "navigation_page.h"
#include "map_select_page.h"
#include "map_editing_page.h"
#include <graphics.h>
#include "enum_lib.h"

Widget::Widget(int w, int h) :width(w),height(h),now_page_id(page_id::HOME_PAGE)/*,my_maps(path)*/ {
	//初始化my_maps
	//my_maps.read_file();
	//初始化四个页面
	my_page.push_back(new home_page(page_id::HOME_PAGE, width, height));
	/*my_page.push_back(new map_select_page(page_id::MAP_SELECT_PAGE, width, height,my_maps));
	my_page.push_back(new map_editing_page(page_id:: MAP_EDITING_PAGE, width, height, my_maps));
	my_page.push_back(new navigation_page(page_id::NAVIGATION_PAGE, width, height,my_maps));*/
}

void Widget::run() {
	bool running = true;
	//使用渲染缓冲区
	BeginBatchDraw();
	while (running) {
		DWORD start_time = GetTickCount();
		//处理输入
		my_page[now_page_id]->get_keyboard_message();

		//将结果输出到画布上
		my_page[now_page_id]->draw();

		//处理页面交换
		if ((now_page_id = my_page[now_page_id]->return_page_id()) == page_id::EXIT) {
			running = false;
		}
		//切换画布
		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		//使用动态刷新
		if (delta_time < 1000 / 60) {
			Sleep(1000 / 60 - delta_time);
		}
	}
	//关闭渲染缓冲区
	EndBatchDraw();
	return;
}

void Widget::close() {
	closegraph();
	for (int i = 0; i < 4; i++) {
		delete my_page[i];
	}
}