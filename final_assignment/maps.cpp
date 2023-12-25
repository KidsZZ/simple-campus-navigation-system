#pragma once
//class maps 用于管理map类，处理多地图存档及其文档写入
//实现的地图为15列10行
#include"maps.h"

//**在传输地址时，对于txt文件，传输string，对于图片，传输wstring


//将地图存档数据全都放在一个文件夹中，并将该文件夹的路径传入path
//构造函数，给出数据文件位置，调用read_file载入地图数据
//初始化列表
maps::maps(std::string path)
	: my_houses(L"picture_hub\\", 4), my_roads(L"picture_hub\\", 11)
{
	//从磁盘文件中读入之前选择的地图id
	selected_map_id = read_select_map_id();

	//利用for循环初始化四张地图，并且载入地图数据
	for (int i = 0; i < NUM; i++)
	{
		//利用new创建数据地址
		//拼接出每张地图的路径，文件名
		//再传递给map构造函数
		this->path = path + "map"+std::to_string(i) + ".txt";
		my_maps[i] = new map(this->path, my_houses, my_roads, column, row);
	}

}

int maps::read_select_map_id() {
	std::ifstream map_id_file(path + "index.txt");
	int file_map_id;
	map_id_file >> file_map_id;
	map_id_file.close();
	return file_map_id;
}
//向文件中写入当前选择的地图id
void maps::write_select_map_id() {
	std::ofstream map_id_file;
	//将原来选择的id删除
	map_id_file.open(path + "index.txt", std::ios::trunc);
	map_id_file << selected_map_id;
	map_id_file.close();
	return;
}

//将指定地图id的存档文件中的数据载入内存
void maps::read_file(int id)
{
	//调用map对象中函数
	my_maps[id]->read_file();
}

//将当前选择的地图载入存档文件
void maps::write_file()
{
	//调用map对象中函数
	my_maps[selected_map_id]->write_file();
}

//返回当前选择的地图id
int maps::now_selected_map_id()
{
	return selected_map_id;
}

//更改当前选择的地图
void maps::set_selected_map_id(int id)
{
	selected_map_id = id;
}

//绘制指定id的地图
void maps::draw(int width, int height, int x, int y, int id) 
{
	my_maps[id]->draw(width, height, x,y);
}

//绘制当前选择的地图
//调用draw方法，传入selected_map_id
void maps::draw_selected(int width, int height, int x, int y)
{
	draw(width, height, x, y, selected_map_id);
}



//下面三个函数都作用于selected_map_id
//增加东西(如果已经有了就替代
//给定坐标和房子id(road id 为0）
void maps::add_building(int x, int y, int house_type) 
{
	my_maps[selected_map_id]->add_building(x, y, house_type);

}

//给定坐标
//删除东西
// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
void maps::delete_build(int x, int y) 
{
	my_maps[selected_map_id]->delete_build(x, y);

}

//给出用户选择的两个建筑的导航
bool maps::connect_houses(int house_type1, int house_type2)
{
	return my_maps[selected_map_id]->connect_houses(house_type1, house_type2);
}

//清除导航路线
void maps::clear_connnect_houses() 
{
	my_maps[selected_map_id]->clear_connect_houses();
}

//返回给定的地图id是否被编辑过
bool maps::is_edited(int page_id) 
{
	return my_maps[page_id]->is_edited();
}


//绘制辅助线，帮助用户放置建筑
//给出当前鼠标的坐标，在选择的地图上绘制出放置建筑的辅助线
void maps::draw_dashed_line(int x, int y)
{
	my_maps[selected_map_id]->draw_dashed_line(x, y);
}

//析构函数
maps::~maps() {
	//先向磁盘中写入用户选择的地图id
	write_select_map_id();

	//释放map对象
	delete[] my_maps;
}
