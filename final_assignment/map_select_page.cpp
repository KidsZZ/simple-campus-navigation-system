#include "map_select_page.h"
#include "enum_lib.h"
map_select_page::map_select_page(int w, int h, maps& my_maps) :abstract_page(page_id::MAP_SELECT_PAGE, w, h), my_maps(my_maps){

	//设置背景
	bk_img = new IMAGE();
	//背景图片放在项目文件的background_img下，命名background.png
	loadimage(bk_img, L"background_img\\background0.jpg");

	//左边模块占比80%，右边占比20%
	left_width = width * 0.8;
	right_width = width - left_width;
	left_height = right_height = height;

	//地图宽高,等分为4份
	map_width = left_width / 2;
	map_height = left_height / 2;

	//地图缩放比例
	unselected_scale = 0.65;
	selected_scale = 0.8;

	//按钮尺寸
	button_width = 200;
	button_height = 70;
	//按钮文本
	first_button_text = L"开始导航";
	second_button_text = L"编辑地图";
	//按钮坐标
	//第一个按钮放在三分之一的位置
	first_button_x = left_width;
	first_button_y = right_height / 3;
	//第二个按钮放在三分之二的位置
	second_button_x = first_button_x;
	second_button_y = right_height * 2 / 3;

	//初始化悬停状态数组
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			is_map_over[i][j] = false;
		}

		//将当前选择的地图从my_maps中读取
		map_selected_id = my_maps.now_selected_map_id();

		//创建按钮
		//第一个按钮：开始导航
		my_button.push_back(new button(button_width, button_height, first_button_x, first_button_y, first_button_text, [this, &my_maps]() {
			set_next_id(page_id::NAVIGATION_PAGE);
			my_maps.set_selected_map_id(map_selected_id);
			//主要用于保存当前选择地图的编号
			my_maps.write_file();
			printf("click navigation_button\n");

			}));
		//第二个按钮：编辑地图
		my_button.push_back(new button(button_width, button_height, second_button_x, second_button_y, second_button_text, [this, &my_maps]() {
			set_next_id(page_id::MAP_EDITING_PAGE);
			my_maps.set_selected_map_id(map_selected_id);
			//主要用于保存当前选择地图的编号
			my_maps.write_file();
			}));

		//返回按钮
		return_button = new button(250, 50, 0, 0, L"返回", [this, &my_maps]() {
			//切换页面，保存信息
			set_next_id(page_id::HOME_PAGE);
			my_maps.write_file();
			printf("click return_button\n");
			});

		//设置鼠标不在上面时地图尺寸
		map_left_space_x = map_width / 2 * (1 - unselected_scale);
		map_left_space_y = map_height / 2 * (1 - unselected_scale);
		//设置鼠标在上面时地图尺寸
		map_left_space_x_selected = map_width / 2 * (1 - selected_scale);
		map_left_space_y_selected = map_height / 2 * (1 - selected_scale);

		//初始化四张地图的实际坐标，都认为左上角为0，0
		for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= 1; j++) {
				map_real[i][j][0] = map_left_space_x;
				map_real[i][j][1] = map_left_space_y;
			}
		}

	}
}

//接收鼠标数据
//主要检查：地图选项，返回按钮，功能按钮
void map_select_page::get_keyboard_message()
{
	ExMessage msg;
	while (peekmessage(&msg)) {
		switch (msg.message) {
		case(WM_MOUSEMOVE):
			//先检测是否在功能按钮上面
			for (button* temp_button_ptr : my_button) {
				temp_button_ptr->checkMouseOver(msg.x,msg.y);
			}
			//再检测是否在返回按键上
			return_button->checkMouseOver(msg.x, msg.y);
			//再检测是否在地图上
			//当地图扩大时，检测范围也要改变
			for (int i = 0; i <= 1; i++) {
				for (int j = 0; j <= 1; j++) {
					if((map_real[i][j][0] + map_width * j) <= msg.x &&
						(map_width - map_real[i][j][0] + map_width * j) >= msg.x &&
						(map_real[i][j][1] + map_height * i) <= msg.y &&
						(map_height - map_real[i][j][1] + map_height * i >= msg.y)) {
						//设置当前地图为选中
						is_map_over[i][j] = true;
						//更改有效边界
						map_real[i][j][0] = map_left_space_x_selected;
						map_real[i][j][1] = map_left_space_y_selected;
					}
					else {
						//设置未选中
						is_map_over[i][j] = false;
						//更改有效边界
						map_real[i][j][0] = map_left_space_x;
						map_real[i][j][1] = map_left_space_y;
					}
				}
			}
			break;
		case (WM_LBUTTONDOWN):

			//先检测是否在返回按键上
			return_button->checkMouseClick(msg.x, msg.y);

			//再检测是否在功能按键上
			for (button* temp_button_ptr : my_button) {
				temp_button_ptr->checkMouseClick(msg.x, msg.y);
			}

			//再检测是否在地图上
			for (int i = 0; i <= 1; i++) {
				for (int j = 0; j <= 1; j++) {
					//如果点击的是地图，就设置map_selected_id，如果不是，就忽视
					if ((map_real[i][j][0] + map_width * j) <= msg.x &&
						(map_width - map_real[i][j][0] + map_width * j) >= msg.x &&
						(map_real[i][j][1] + map_height * i) <= msg.y &&
						(map_height - map_real[i][j][1] + map_height * i >= msg.y)) {
						//设置当前地图为选中
						map_selected_id = i * 2 + j;
					}
				}
			}
			break;
		}
	}
}

//绘制元素：返回按键，地图选项，功能按钮
void map_select_page::draw()
{	
	//绘制背景
	putimage(0, 0, width, height, bk_img, 0, 0);

	//绘制地图背景（选中的地图背景为浅蓝）
	int map_i = map_selected_id / 2;
	int map_j = map_selected_id % 2;

	//设置背景颜色为浅蓝
	setfillcolor(0xe6d8ad);//格式为bgr
	solidrectangle(map_width * map_j + map_width * 0.05, map_height * map_i + map_height * 0.05, map_width * (map_j + 1) - map_width * 0.05 , map_height * (map_i + 1) - map_height * 0.05);


	//绘制功能按钮
	for (auto temp_ptr : my_button) {
		temp_ptr->draw();
	}


	//绘制地图
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			//使用储存在map_real中的数据分别绘制地图
			my_maps.draw(map_width - map_real[i][j][0] * 2, map_height - map_real[i][j][1] * 2, map_width * j + map_real[i][j][0], map_height * i + map_real[i][j][1], i * 2 + j);
		}
	}
	//绘制返回按钮
	return_button->draw();
}

//析构函数
//释放内存
map_select_page::~map_select_page() {
	//背景图片
	delete bk_img;

	//返回按钮
	delete return_button;

	//功能按钮
	while (!my_button.empty()) {
		delete my_button.back();
		my_button.pop_back();

	}
}

int map_select_page::return_page_id() {
	if (return_flag) {
		return_flag = false;
		return next_id;
	}
	else {
		return page_id::MAP_SELECT_PAGE;
	}
}

