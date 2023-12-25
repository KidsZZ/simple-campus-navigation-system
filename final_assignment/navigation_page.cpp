#include "navigation_page.h"
#include "enum_lib.h"
#include "picture_button.h"
navigation_page::navigation_page(int w, int h, maps& my_maps) :abstract_page(page_id::NAVIGATION_PAGE, w, h), my_maps(my_maps)
{	

	//背景设置
	bk_img = new IMAGE();
	//背景图片放在项目文件的background_img下，命名background.png
	loadimage(bk_img, L"background_img\\background0.jpg");

	//设置页面模块尺寸
	left_width = width * 0.8;
	right_width = width - left_width;
	left_height = right_height = height;

	//地图缩放
	scale = 0.85;

	//地图实际长宽
	map_width = (left_width * (1 - scale));
	map_height = map_width / 1.5;
	
	//地图实际坐标
	map_real_x = (left_width - map_width) / 2;
	map_real_y = (left_height - map_height) / 2;

	// 返回按钮
	return_button = new button(150, 50, 0, 0, L"返回", [this]() {
		set_next_id(page_id::MAP_SELECT_PAGE);
		});

	//右边功能菜单设置
	// 一个建筑选项的长宽(指右边选项中的建筑）（外层尺寸）
	single_object_width = right_width;
	single_object_height = right_height / 4;

	//初始化picture_button
	//设置按钮文本
	std::wstring build_exp[building_num] = {
		L"road",
		L"library",
		L"dorminory",
		L"teaching_building",
		L"canteen" 
	};

	for (int i = 1; i < building_num; i++) {
		std::wstring temp_path = L"picture_hub\\house" + std::to_wstring(i) + L".png";
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

//需要选择两个建筑才能进行导航，所以需要在set_now_select_building_id中进行分类讨论
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
			//满足两个建筑，调用导航函数连接两个建筑
			my_maps.connect_houses(now_select_building[0], now_select_building[1]);
		}
		else {
			now_select_building_num++;
			now_select_building[1] = i;
			//满足两个建筑，调用导航函数连接两个建筑
			my_maps.connect_houses(now_select_building[0], now_select_building[1]);
		}
		break;
	case(2):
		//如果点击选择过的建筑，就删除建筑
		if (now_select_building[0] == i) {
			now_select_building_num--;
			now_select_building[0] = now_select_building[1];
			now_select_building[1] = -1;
			//不满足选择两个建筑，清除导航
			my_maps.clear_connnect_houses();
		}

		else if (now_select_building[1] == i) {
			now_select_building_num--;
			now_select_building[1] = -1;
			//不满足选择两个建筑，清除导航
			my_maps.clear_connnect_houses();
		}
		//不满足以上条件为无效点击
		else {
			printf("\n选择无效！\n");
		}
		break;
	default:
		printf("navigation_page switch error2!");
	}
}


//接收鼠标数据
void navigation_page::get_keyboard_message() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		switch (msg.message) {

		//如果是移动
		case(WM_MOUSEMOVE):

			//检测是否在返回按钮上
			return_button->checkMouseOver(msg.x, msg.y);

			//检测是否在图片按钮上面
			for (auto tempptr : my_picture_button) {
				tempptr->checkMouseOver(msg.x, msg.y);
			}

			break;
		//如果是鼠标点击
		case (WM_LBUTTONDOWN):

			//如果在返回按钮上
			return_button->checkMouseClick(msg.x, msg.y);

			//先检测是否在图片按钮上面
			for (auto tempptr : my_picture_button) {
				tempptr->checkMouseClick(msg.x, msg.y);
			}
			break;
		}
	}
}

void navigation_page::draw() {

	//背景设置
	putimage(0, 0, width, height, bk_img, 0, 0);

	//绘制地图
	my_maps.draw_selected(map_width, map_height, map_real_x, map_real_y);

	//返回按键
	return_button->draw();

	//建筑选项
	for (auto tempptr : my_picture_button) {
		tempptr->draw();
	}
}

navigation_page::~navigation_page() {

	//删除背景图片
	delete bk_img;

	//删除返回按钮
	delete return_button;

	//删除建筑选项
	while (!my_picture_button.empty()) {
		delete my_picture_button.back();
		my_picture_button.pop_back();
	}

}

int navigation_page::return_page_id()
{
	if (return_flag) {
		return_flag = false;
		return next_id;
	}
	else {
		return page_id::NAVIGATION_PAGE;
	}
}
