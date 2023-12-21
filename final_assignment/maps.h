#pragma once
//class maps 用于管理map类，处理多地图存档及其文档写入
//实现的地图为15列10行
#include <string>
#include "map.h"
#include "houses.h"
#include "roads.h"

class maps {
public:
	friend class map;
	//将地图存档数据全都放在一个文件夹中，并将该文件夹的路径传入path
	//构造函数，给出数据文件位置，调用read_file载入地图数据
	maps(std::wstring path);//初始化列表
	//将指定地图id的存档文件中的数据载入内存
	void read_file(int id);
	//返回当前选择的地图id
	int now_selected_map_id();
	//更改当前选择的地图
	void set_selected_map_id(int n);
	//将当前选择的地图载入存档文件
	void write_file();
	//绘制指定id的地图
	void draw(int width,int height, int x, int y, int id);
	//绘制当前选择的地图
	void draw_selected(int width,int height, int x, int y);

	//下面三个函数都作用于selected_map_id
	//增加东西(如果已经有了就替代
	//给定坐标和房子id(road id 为0）
	void add_building(int x, int y, int house_type);
	//给定坐标
	//删除东西
	// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
	void delete_build(int x, int y);


	//连接两地（最短路）
	bool connect_houses(int house_type1, int house_type2);
	//清除导航路线
	void clear_connnect_houses();
	//返回给定的地图id是否被编辑过
	bool is_edited(int page_id);
private:
	const static int NUM = 4;
	
	int selected_map_id;
	//存放地图数据的文件夹位置
	std::wstring path;
	map* my_map[NUM];
	roads my_roads;
	houses my_houses;
	//每个地图15列，10行
	const static int column = 15;
	const static int row = 10;
};