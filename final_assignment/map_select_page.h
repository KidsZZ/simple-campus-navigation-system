#pragma once

#include "abstract_page.h"
#include "maps.h"
#include <vector>
class map_select_page :public abstract_page {
public:
	//构造函数，要通过基类初始化页面的宽高和下一个页面id
	map_select_page(int next_id,int w,int h, maps<show_maps_num>& my_maps);
	//virtual void update_maps()override;
	virtual bool get_keyboard_message()override;
	virtual void draw()override;

	virtual int return_page_id()override;
	virtual ~map_select_page();
private:
	//使用maps类实现地图保存及操作(引用传递）
	maps<show_maps_num> &my_maps;

};