#include "map_editing_page.h"
#include "enum_lib.h"
map_editing_page::map_editing_page(int next_id, int w, int h, maps& my_maps) :abstract_page(next_id, w, h) ,my_maps(my_maps){
	//左右模块尺寸
	left_width = width * 0.8;
	right_width = width - left_width;
	left_height = right_height = height;
	//地图实际尺寸
	map_width = left_width * 0.85;
	map_height = map_width / 1.5;
	map_real_x = (width - left_width) / 2;
	map_real_y = (height - map_height) / 2;
	//地图左边的空间
	// 一个建筑选项的长宽(指右边选项中的建筑）（外层尺寸）
	single_object_width = right_width;
	single_object_height = right_height / 5;
	//初始化picture_button
	std::wstring build_exp[building_num] = { 
		L"road",
		L"library",
		L"dorminory",
		L"teaching_building",
		L"canteen" };
	for (int i = 0; i < building_num; i++) {
		std::wstring temp_path = L"building_img/build"+std::to_wstring(i)+L".png";
		my_picture_button.push_back(new picture_button(temp_path, build_exp[i].
			c_str(), single_object_width, single_object_height, left_width,single_object_height*i));
	}
	//默认不选择建筑(-1)
	now_select_building = -1;
}

void map_editing_page::get_keyboard_message() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		switch (msg.message) {
		case(WM_MOUSEMOVE):
			//先检测是否在图片按钮上面
			for (auto tempptr : my_picture_button) {
				tempptr->checkMouseOver(msg.x,msg.y);
			}
			if ((msg.x >= map_real_x) && (msg.x < (map_real_x + map_width) && (msg.y >= map_real_y) && (msg.y <= (map_real_y + map_height)) {
				if (now_select_building != -1) {
					if(now_select_building)
				}
			}
			break;
		case (WM_ACTIVATE):
			
		}
	}
}
