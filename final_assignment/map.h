#pragma once
//单个map，使用maps进行管理
// 逻辑判断在此实现
//具体存储单张地图数据
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include "houses.h"
#include "roads.h"
#include "lines.h"
#include "enum_lib.h"
class map 
{
public:

	//在maps初始化时调用下方此函数
	//传入存档路径，my_houses,与my_roads在此初始化
	map(std::string path, houses& my_house, roads& my_roads, int column, int row);

	//读入数据传入mapData二维数组
	// 此外对于文件的数据也进行了一次判断是否匹配
	//由于有maps进行了地图管理所以读进数据时更加准确
	void read_file();
	
	//首先写入该张地图的row和column
	//其次再写入相对于的map.txt文件
	void write_file();
	
	//渲染地图，调用roads与maps类中的draw函数，进行逻辑判断后绘图
	void draw(int width, int height, int x, int y);

	//给定坐标和房子id(road id 为0）
	void add_building(int x, int y, int house_type);

	// 给定坐标(删除房子和道路用一个函数）
	void delete_build(int x, int y);

	//返回给定的地图id是否被编辑过
	bool is_edited();

	//判断若绘制道路的话属于哪种道路类型
	int select_road_type(int i,int j);

	//连接两地（最短路）(用于之后扩展)
	bool connect_houses(int house_type1, int house_type2);

	//清除导航路线(用于之后扩展)
	void clear_connnect_houses();

	//显示鼠标所停放地标图标所代表的房屋类型
	void show_house_type(std::string& name, int x, int y);

	//绘制虚线辅助线，帮助用户放置建筑
    //(x,y)为绘制地图的的左上角，后两位参数为地图的宽度和长度
	void draw_subline();

	//绘制虚线辅助线函数的辅助函数
	void draw_dashed_line(int x,int y);
private:
	//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
	bool translate_xy(int *ans, int x, int y);

	//记录(x,y)所对应的格子（二维数组中的准确位置）
	int real_coord[2];


	//通过my_houses、my_roads对象来调用其中函数对象
	houses my_houses;
	roads my_roads;

	//lines my_lines;
	//暂时可能不使用,后期用于绘制辅助线
	
	//用来存储当前地图的数据
	//使用char存储
	//-是占位符，0为道路，其余数字为建筑
	std::vector<std::vector<char>>mapData;

	//地图单元格列数
	int column;
	//地图单元格行数
	int row;

	//保存最近一次绘制地图时的地图长宽和坐标，供后续算出地图中格子的坐标使用
	int height,width;
	int x, y;

	//存档文件的路径
	std::string path;


	//以动态string来储存当前选中建筑的类型
	static std::string house_name;

	//用building_num变量来对于此地图进行计数操作
	int building_num;

	//用building_position二维数组来存储每个房屋的横纵坐标
	//从1开始算一直到4，与enum.lib中设定相同，方便应用
	int building_position[5][2];
	//储存每个建筑是否都被放置，便于查找
	bool is_building_present[5];
	
	//以length来储存每格的边长
	int length;

	//鼠标当前所在的逻辑坐标（全为-1代表不在地图上）
	// 用于辅助绘制鼠标选择辅助线
	//初始化为-1，当不调用draw_dashed_line更新值时永远不会绘制辅助线
	int mouse_now_abstract_x;
	int mouse_now_abstract_y;
};