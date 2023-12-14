#pragma once
#include "abstract_page.h"
#include "maps.h"
//class map_editing实现对地图的编辑
class map_editing :public abstract_page {
public:
	map_editing(int next_id, int w, int h, maps<show_maps_num>& my_maps);
	//virtual void update_maps()override;
	virtual bool get_keyboard_message()override;
	virtual void draw()override;
	//地图编辑器在退出前对编辑过的地图执行写入文件操作
	virtual int return_page_id()override;
	virtual ~map_editing();
private:
	//使用maps类实现地图保存及操作(引用传递）
	maps<show_maps_num>& my_maps;
};