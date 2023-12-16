#pragma once
#include "abstract_page.h"
#include "maps.h"
//class map_editing实现对地图的编辑
class map_editing_page :public abstract_page {
public:
	map_editing_page(int next_id, int w, int h, maps<show_maps_num>& my_maps);
	//virtual void update_maps()override;
	virtual void get_keyboard_message()override;
	virtual void draw()override;
	virtual ~map_editing_page();
private:
	//使用maps类实现地图保存及操作(引用传递）
	maps<show_maps_num>& my_maps;
};