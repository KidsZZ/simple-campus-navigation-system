#include"map.h"
//单个map，使用maps进行管理
// 逻辑判断在此实现
//具体存储单张地图数据

	//传入存档路径，houses
map::map (std::wstring path, const houses& my_house, const roads& my_roads,  lines& my_lines,
	int column, int row,int width,int height)
	:my_houses(my_house), my_roads(my_roads),my_lines(my_lines),column(column),row(row),path(path), 
     mapData((row + 1), std::vector<char>(column, '-'))
{
	//先初始化mapDate数组
	this->height = height;
	this->width = width;
		
}

map::map(std::wstring path, const houses& my_house, const roads& my_roads, lines& my_lines, int column, int row)
	:my_houses(my_house), my_roads(my_roads),my_lines(my_lines)
{
	map(path, my_house, my_roads, my_lines, column, row, 0, 0);
}


void map::read_file()
{
	mapData.clear();
	std::ifstream file(path);
	if (file.is_open())//检查文件是否能成功打开
	{
		std::string line;
		std::getline(file ,line);
		//先读取第一行，检查row与column是否异常
		std::vector<char>rows;
		for (char c : line)
		{
			//如果不是空格则存入二维数组当中
			if (c != ' ')
			{
				rows.push_back(c);
			}
		}
		mapData.push_back(rows);
		//下面是对于数据是否异常的判断
		if (mapData[0][1] != char(column) || mapData[0][0] != char(row))
		{
			std::cout << "Error" << std::endl;
		}

		while (std::getline(file, line))//逐行读取数据
		{
			std::vector<char>rows;
			for (char c : line)
			{
				if (c != ' ')//如果不是空格则存入二维数组当中
				{
					rows.push_back(c);
				}
			}
			mapData.push_back(rows);
		}
		file.close();
	}
	else
	{
		std::cout << "无法打开文件" << std::endl;
	}
}


void map::write_file()
{
	std::ofstream file(path);
	file << row << " " << column << " " << char(1);
	if (file.is_open())
	{
		for (const auto& row : mapData)
		{
			for (const auto& ch : row)
			{
				file << ch << " ";
			}
			file << "\n";
		}
		file.close();
		std::cout << "文件写入成功" << std::endl;
	}
	else
	{
		//向标准错误设备发送错误信息，立即显示错误信息的情况
		std::cerr << "无法打开文件" << std::endl;
	}

}


//判断若绘制道路的话属于哪种道路类型
int map::select_road_type(int i,int j)
{
	//首先创建一个bool类型的vector数组来存储此道路上下左右四个方向的信息
	std::vector<bool>road_type(4, false);
	if (j == 0)
	{
		if (mapData[i - 1][j] == '0' && (my_houses.house_orientation[(int)mapData[i - 1][j]][4]))
			road_type[0] = true;
		//此坐标左侧为地图边界，默认为false
		if (mapData[i][j + 1] == '0' && (my_houses.house_orientation[(int)mapData[i][j + 1]][2]))
			road_type[2] = true;
		if (mapData[i + 1][j] == '0' && (my_houses.house_orientation[(int)mapData[i + 1][j]][4]))
			road_type[3] = true;
	}
	else
	{
		if (mapData[i - 1][j] == '0' && (my_houses.house_orientation[(int)mapData[i - 1][j]][4]))
			road_type[0] = true;
		if (mapData[i][j - 1] == '0' && (my_houses.house_orientation[(int)mapData[i][j - 1]][3]))
			road_type[1] = true;
		if (mapData[i][j + 1] == '0' && (my_houses.house_orientation[(int)mapData[i][j + 1]][2]))
			road_type[2] = true;
		if (mapData[i + 1][j] == '0' && (my_houses.house_orientation[(int)mapData[i + 1][j]][4]))
			road_type[3] = true;
		
	}
	if (road_type[0] == 1 && road_type[1] == 1 && road_type[2] == 0 && road_type[3] == 0) {
		return 1;
	}
	if (road_type[0] == 1 && road_type[1] == 0 && road_type[2] == 1 && road_type[3] == 0) {
		return 2;
	}
	if (road_type[0] == 1 && road_type[1] == 0 && road_type[2] == 0 && road_type[3] == 1) {
		return 3;
	}
	if (road_type[0] == 0 && road_type[1] == 1 && road_type[2] == 1 && road_type[3] == 0) {
		return 4;
	}
	if (road_type[0] == 0 && road_type[1] == 1 && road_type[2] == 0 && road_type[3] == 1) {
		return 5;
	}
	if (road_type[0] == 0 && road_type[1] == 0 && road_type[2] == 1 && road_type[3] == 1) {
		return 6;
	}
	if (road_type[0] == 0 && road_type[1] == 1 && road_type[2] == 1 && road_type[3] == 1) {
		return 7;
	}
	if (road_type[0] == 1 && road_type[1] == 0 && road_type[2] == 1 && road_type[3] == 1) {
		return 8;
	}
	if (road_type[0] == 1 && road_type[1] == 1 && road_type[2] == 0 && road_type[3] == 1) {
		return 9;
	}
	if (road_type[0] == 1 && road_type[1] == 1 && road_type[2] == 1 && road_type[3] == 0) {
		return 10;
	}
	if (road_type[0] == 1 && road_type[1] == 1 && road_type[2] == 1 && road_type[3] == 1) {
		return 11;
	}
}
void map::draw(int width, int height, int x, int y)
{
	//计算每格的边长
	int length = (width / 15);

	for (int i = 1; i <= row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (mapData[i][j] != '0' && mapData[i][j] != '-')
			{
				my_houses.draw(length, (x+((i - 1) * length)), (y+(j * length)), (mapData[i][j] - '0'));
			}
			if (mapData[i][j] == '0')
			{
				my_roads.draw(length, (x + ((i - 1) * length)), (y + (j * length)), select_road_type(i, j));
			}
			else break;
		}
	}
	my_lines.draw(x, y);
}


//给定坐标和房子id(road id 为0）
void map::add_building(int x, int y, int house_type)
{
	//首先计算此时鼠标的位置信息；
	tranlate_xy(real_coord, x, y);
	//因为第一行储存的是地图行数，列数以及是否被更改的bool变量，第二行开始才存储地图地标数据
	mapData[real_coord[0]][real_coord[1]] = house_type;
}

// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
void map::delete_build(int x, int y)
{
	//首先计算此时鼠标的位置信息；
	tranlate_xy(real_coord, x, y);
	//因为第一行储存的是地图行数，列数以及是否被更改的bool变量，第二行开始才存储地图地标数据
	mapData[real_coord[0]][real_coord[1]] = '-';
}

//返回给定的地图id是否被编辑过
bool map::is_edited(int page_id)
{
	bool is_change = (bool)mapData[0][2];
	return is_change;
}

//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
void map::tranlate_xy(int* ans, int x, int y)
{
	int length = height/ row;
	ans[0] = (x / length) + 1;
	ans[0] = y / length;
}
