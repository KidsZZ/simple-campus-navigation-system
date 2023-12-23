#include "navigation_page.h"
#include "enum_lib.h"
#include "picture_button.h"
navigation_page::navigation_page(int w, int h, maps& my_maps) :abstract_page(page_id::NAVIGATION_PAGE, w, h), my_maps(my_maps)
{
	left_width = width * 0.8;
	right_width = width - left_width;
	left_height = right_height = height;
	scale = 0.8;
	map_real_x = (left_width * (1 - scale)) / 2;
	map_real_y = (left_height * (1 - scale)) / 2;

	// 返回按钮
	return_button = new button(150, 50, 0, 0, L"返回", [this]() {
		set_next_id(page_id::MAP_SELECT_PAGE);
		});
	//右边功能菜单设置
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
	for (int i = 1; i < building_num; i++) {
		std::wstring temp_path = L"building_img/build" + std::to_wstring(i) + L".png";
		my_picture_button.push_back(new picture_button(temp_path, build_exp[i].
			c_str(), single_object_width, single_object_height, left_width, single_object_height * (i - 1), [this, i]() {
				//为每个图片按钮设置lambda表达式
				set_now_select_building_id(i);
			}));
		//将默认值都设为-1，表示当前没有选择
		now_select_building[0] = -1;
		now_select_building[1] = -1;
		now_select_building_num = 0;
	}
}
void navigation_page::set_now_select_building_id(int i)
{
	switch (now_select_building_num) {
	case(0):
		//没有选择时
		++now_select_building_num;
		now_select_building[0] = i;
		break;
	case(1):
		//重复点击删除选择建筑
		if (now_select_building[0] == i) {
			now_select_building_num--;
			now_select_building[0] = -1;
		}
		//将编号小的建筑放在前面
		else if (now_select_building[0] > i) {
			now_select_building_num++;
			now_select_building[1] = now_select_building[0];
			now_select_building[0] = i;
			my_maps.connect_houses(now_select_building[0], now_select_building[1]);
		}
		else {
			now_select_building_num++;
			now_select_building[1] = i;
			my_maps.connect_houses(now_select_building[0], now_select_building[1]);
		}
		break;
	case(2):
		if (now_select_building[0] == i) {
			now_select_building_num--;
			now_select_building[0] = now_select_building[1];
			now_select_building[1] = -1;
			my_maps.clear_connnect_houses();
		}
		else if (now_select_building[1] == i) {
			now_select_building_num--;
			now_select_building[1] = -1;
			my_maps.clear_connnect_houses();
		}
		else {
			printf("\n选择无效！\n");
		}
		break;
	}
}

void navigation_page::get_keyboard_message() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		switch (msg.message) {
		case(WM_MOUSEMOVE):
			//先检测是否在图片按钮上面
			for (auto tempptr : my_picture_button) {
				tempptr->checkMouseOver(msg.x, msg.y);
			}
			//如果在按钮上
			return_button->checkMouseOver(msg.x, msg.y);
			break;
		case (WM_ACTIVATE):
			//先检测是否在图片按钮上面
			for (auto tempptr : my_picture_button) {
				tempptr->checkMouseClick(msg.x, msg.y);
			}
			//检测是否在地图上
			//如果在地图地图上，当now_select_building不为-1时传递参数给maps
			//如果在按钮上
			return_button->checkMouseClick(msg.x, msg.y);
			break;
		}
	}
}

void navigation_page::draw() {
	//背景
	setbkcolor(0xf6eb76);
	cleardevice();
	//地图
	my_maps.draw_selected(map_width, map_height, map_real_x, map_real_y);
	//返回按键
	return_button->draw();
	//建筑选项
	for (auto tempptr : my_picture_button) {
		tempptr->draw();
	}
}

navigation_page::~navigation_page() {
	delete return_button;
	while (!my_picture_button.empty()) {
		delete my_picture_button.back();
		my_picture_button.pop_back();
	}

}