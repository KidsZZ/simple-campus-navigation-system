#pragma once
#include "abstract_page.h"
#include <string>
#include "option.h"
#include <vector>
class home_page :public abstract_page {
public:
	home_page(int next_id, int w, int h);
	virtual void get_keyboard_message()override;
	virtual void draw()override;
	virtual ~home_page()override;
private:
	std::wstring title_text;
	std::wstring first_button_text;
	std::wstring second_button_text;
	std::vector<option*> my_option;
	int mouse_x, mouse_y;
	int title_x, title_y;
	int button_width, button_height;
	int first_button_x, first_button_y;
	int second_button_x, second_button_y;
};