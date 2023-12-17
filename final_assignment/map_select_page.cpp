#include "map_select_page.h"

map_select_page::map_select_page(int next_id, int w, int h, maps<show_maps_num>& my_maps) :abstract_page(next_id, w, h), my_maps(my_maps) {
	//左边模块占比80%，右边占比20%
	left_width = width * 0.8;
	right_width = width - left_width;
	left_height = right_width = height;
	map_width = left_width / 2;
	map_height = left_height / 2;
	unselected_scale = 0.65;
	selected_scale = 0.8;
	button_width = 280;
	button_height = 60;
	first_button_text = L"开始导航";
	second_button_text = L"编辑地图";
	first_button_x = left_width + (right_width - button_width) / 2;
	first_button_y = right_height / 3;
	second_button_x = first_button_x;
	second_button_y = right_height * 2 / 3;
}

void map_select_page::get_keyboard_message()
{

}

