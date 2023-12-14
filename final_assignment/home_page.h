#pragma once
#include "abstract_page.h"
class home_page :public abstract_page {
public:
	home_page(int next_id, int w, int h);
	//占位，不调用
	virtual void update_maps();
	virtual bool get_keyboard_message()override;
	virtual void draw()override;
	virtual int return_page_id()override;
	virtual ~home_page()override;
};