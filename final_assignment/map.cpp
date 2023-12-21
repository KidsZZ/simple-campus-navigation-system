#include"map.h"
//单个map，使用maps进行管理
// 逻辑判断在此实现
//具体存储单张地图数据

	//传入存档路径，houses
map::map (std::wstring path, const houses& my_house, const roads& my_roads, int column, int row)
	:my_houses(my_house), my_roads(my_roads),column(column),row(row),path(path), 
     mapData((row + 1), std::vector<char>(column, '-'))
{
	//先初始化mapDate数组
		
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
		//向标准错误设备发送错误信息，
		std::cerr << "无法打开文件" << std::endl;
	}

}
void map::draw(int width, int height, int x, int y)
{

}


//给定坐标和房子id(road id 为0）
void map::add_building(int x, int y, int house_type)
{

}

// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
void map::delete_build(int x, int y)
{

}

//返回给定的地图id是否被编辑过
bool map::is_edited(int page_id)
{

}
