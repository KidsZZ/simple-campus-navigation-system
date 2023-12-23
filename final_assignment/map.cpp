#include"map.h"
//单个map，使用maps进行管理
// 逻辑判断在此实现
//具体存储单张地图数据

//传入存档路径，houses

map::map(std::wstring path, houses& my_house, roads& my_roads, 
	int column, int row)
	:my_houses(my_house), my_roads(my_roads), path(path)
{
	//先初始化mapDate数组
	this->column = column;
	this->row = row;
	for (int i = 0; i < 2; i++)real_coord[i] = 0;
	Building_num = 0;
	if (is_edited())
	{
		mapData.clear();
		read_file();
	}	
}



void map::read_file()
{
	//传入地图路径
	std::ifstream file(path); 
	// 判断文件是否成功打开
	if (file.is_open())
	{
		// 定位到文件末尾
		file.seekg(0, std::ios::end);
		// 判断文件大小是否为0
		if (file.tellg() == 0)
		{
			//对mapData进行初始化操作
			//即全部用占位符来替代
			std::vector<std::vector<char>> mapData_temp((row), std::vector<char>(column, '-'));
			mapData = mapData_temp;
		}

		else
		{
			//先读取第一行，检查row与column是否异常
			std::string line1;
			std::vector<char>rows1;
			std::getline(file, line1);

			for (char c : line1)
			{
				//如果不是空格则暂时存入rows当中
				if (c != ' ')
				{
					rows1.push_back(c);
				}
			}

			//下面是对于数据是否异常的判断
			//即如果文件中记录的单元格行数和单元格列数，与传入参数不同则报错
			if (rows1[0] != char(row) || rows1[1] != char(column))
			{
				std::cout << "Error" << std::endl;
				return;
			}

			std::string line2;
			//逐行读取数据
			while (std::getline(file, line2))
			{
				std::vector<char>rows2;
				int lineNumber = 0;
				for (char c : line2)
				{
					//如果不是空格则存入二维数组当中
					if (c != ' ')
					{
						rows2.push_back(c);
					}
				}

				//实现了从文件第二行开始读入数据，计入mapData当中
				if (lineNumber > 1)
				{
					//将row2数组压入mapData当中
					mapData.push_back(rows2);
				}
			}

		}
		file.close(); // 关闭文件
	}

	else 
	{
		std::cout << "无法打开指定文件" << std::endl;
	}

	//进行当前地图建筑数量初始化的操作
	//读取二维数组中的数据判断是否为房屋类型，若是，则Building_num++
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (mapData[i][j] != '-' || mapData[i][j] != '0')
			{
				Building_num++;
			}
		}
	}
	
}


void map::write_file()
{
	//初始化构造函数	  读取file文件所在的位置
	std::ofstream file(path);
	file << row << " " << column << " " ;
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
	if (j == 0 && i != 0 && i != row)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(4, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		//此坐标左侧为地图边界，默认为false

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(2, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(1, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == 0 && j != 0 && j != column)
	{
		//此坐标上侧为地图边界，默认为false

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(3, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(2, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(1, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (j == column && i != 0 && i != row)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(4, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(3, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		//此坐标右侧为地图边界，默认为false

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(1, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == row && j != 0 && j != column)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(4, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(3, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(2, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		//此坐标下侧为地图边界，默认为false
	}

	if (i == 0 && j == 0)
	{
		//利用||短路的性质，进行逻辑运算
		//此坐标上侧为地图边界，默认为false

		//此坐标左侧为地图边界，默认为false

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(2, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(1, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == 0 && j == column)
	{
		//利用||短路的性质，进行逻辑运算
		//此坐标上侧为地图边界，默认为false

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(3, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		//此坐标右侧为地图边界，默认为false

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(1, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == row && j == 0)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(4, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		//此坐标左侧为地图边界，默认为false

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(2, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		//此坐标下侧为地图边界，默认为false
	}

	if (i == row && j == column)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(4, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(3, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		//此坐标右侧为地图边界，默认为false

		//此坐标下侧为地图边界，默认为false
	}

	if((i>0&&i<row)&&(j>0&&j<column))
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(4, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(3, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(2, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(1, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
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
	length = (width / 15);

	for (int i =0; i <width; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (mapData[i][j] != '0' && mapData[i][j] != '-')
			{
				my_houses.draw(length, (x+(i  * length)), (y+(j * length)), (mapData[i][j] - '0'));
			}
			if (mapData[i][j] == '0')
			{
				my_roads.draw(length, (x + (i  * length)), (y + (j * length)), select_road_type(i, j));
			}
			else break;
		}
	}


}


//给定坐标和房子id(road id 为0）
void map::add_building(int x, int y, int house_type)
{

	//首先计算此时鼠标的位置信息；
	tranlate_xy(real_coord, x, y);

	//因为第一行储存的是地图行数，列数以及是否被更改的bool变量，第二行开始才存储地图地标数据
	mapData[real_coord[0]][real_coord[1]] = house_type;
	//该地图房屋数+1
	Building_num++;
	//记录房屋坐标
	position_array[house_type][0] = x;
	position_array[house_type][1] = y;
}

// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
void map::delete_build(int x, int y,int house_type)
{
	//首先计算此时鼠标的位置信息；
	tranlate_xy(real_coord, x, y);
	//重置数据为‘-’
	mapData[real_coord[0]][real_coord[1]] = '-';
	//房屋数-1
	Building_num--;
	//防止误操作
	if (Building_num < 0)Building_num = 0;
	//重置房屋坐标
	position_array[house_type][0] = -1;
	position_array[house_type][1] = -1;

}

//返回给定的地图id是否被编辑过
bool map::is_edited()
{
	if (Building_num == 0)
		return false;
	else
	{
		return true;
	}
}

//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
void map::tranlate_xy(int* ans, int x, int y)
{
	int length = height/ row;
	ans[0] = (x / length);
	ans[0] = y / length;
}


//用来记录两地在二维数组当中的具体位置
void map::get_position(int* ans, int house_type1, int house_type2)
{
	for (int i = 1; i <= row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if ((mapData[i][j] - '0') == house_type1)
			{
				position[0] = i;

				position[1] = j;
			}
			if ((mapData[i][j] - '0') == house_type2)
			{
				position[2] = i;
				position[3] = j;
			}
		}
	}
}


//显示鼠标所停放地标图标所代表的房屋类型
void map::show_house_type(std::string& name,int x, int y)
{
	tranlate_xy(real_coord, x, y);
	int indexX = real_coord[0];
	int indexY = real_coord[1];
	int house_type = mapData[indexX][indexY]-'0';

	switch (house_type)
	{
	case 1:
		name = "library";
		break;
	case 2:
		name = "dormitory";
		break;
	case 3:
		name = "teaching_building";
		break;
	case 4:
		name = "canteen";
		break;
	default:
		break;
	}
}







//连接两地（最短路）(用于之后扩展)
//bool map::connect_houses(int house_type1, int house_type2){}

//清除导航路线(用于之后扩展)
//void clear_connnect_houses(){}

