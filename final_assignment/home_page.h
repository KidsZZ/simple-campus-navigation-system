#pragma once
#include "abstract_page.h"
#include <string>
#include "button.h"
#include <vector>
class home_page :public abstract_page {
public:
	home_page(int w, int h);
	virtual void get_keyboard_message()override;
	virtual void draw()override;
	virtual ~home_page()override;
private:
	std::wstring title_text;
	std::wstring first_button_text;
	std::wstring second_button_text;
	std::vector<button*> my_button;
	int title_size;
	int mouse_x, mouse_y;
	int title_x, title_y;
	int button_width, button_height;
	int first_button_x, first_button_y;
	int second_button_x, second_button_y;
};