#pragma once
//class maps 用于管理map类，处理多地图存档及其文档写入
//实现的地图为15列10行
#include"maps.h"


//将地图存档数据全都放在一个文件夹中，并将该文件夹的路径传入path
//构造函数，给出数据文件位置，调用read_file载入地图数据
//初始化列表
maps::maps(std::wstring path)
	:selected_map_id(0), my_houses(L"picture_hub/", 5), my_roads(L"picture_hub/", 11)
{
	my_map[selected_map_id] = new map(path,my_houses,my_roads,column,row);

}

//将指定地图id的存档文件中的数据载入内存
void maps::read_file(int id)
{
	my_map[id]->read_file();
}

//返回当前选择的地图id
int maps::now_selected_map_id()
{

};

//更改当前选择的地图
void maps::set_selected_map_id(int n)
{

};

//将当前选择的地图载入存档文件
void maps::write_file() 
{

};

//绘制指定id的地图
void maps::draw(int width, int height, int x, int y, int id) 
{

};

//绘制当前选择的地图
void maps::draw_selected(int width, int height, int x, int y)
{
	draw( width,  height,  x,  y,  selected_map_id);
}



//下面三个函数都作用于selected_map_id
//增加东西(如果已经有了就替代
//给定坐标和房子id(road id 为0）
void add_building(int x, int y, int house_type) 
{

};
//给定坐标
//删除东西
// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
void maps::delete_build(int x, int y) 
{

};

//连接两地（最短路）
bool maps::connect_houses(int house_type1, int house_type2) 
{

};

//清除导航路线
void maps::clear_connnect_houses() 
{

};

//返回给定的地图id是否被编辑过
bool maps::is_edited(int page_id) 
{

};

