#pragma once
#include "abstract_page.h"
#include "maps.h"
//class navigation实现对以编辑地图的一系列功能
class navigation :public abstract_page {
public:
	navigation(int next_id, int w, int h,maps<show_maps_num>& my_maps);
	//virtual void update_maps()override;
	virtual bool get_keyboard_message()override;
	virtual void draw()override;
	virtual int return_page_id()override;
	virtual ~navigation();
private:
	//使用maps类实现地图保存及操作(引用传递）
	maps<show_maps_num>& my_maps;
};