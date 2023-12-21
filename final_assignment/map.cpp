//单个map，使用maps进行管理
//具体存储单张地图数据，并
#include"map.h"


//读取path文件路径中的数据，并创建houses与roads对象存入相对应的数据
map::map(std::string path, const houses& my_houses, const roads& my_roads):my_houses(my_houses),my_roads(my_roads)
{

	std::ifstream file(path);
	if (file.is_open())
	{
		//创建string临时变量line
		std::string line;
		//在文件中读取每一行数据并且存入mapData中
		while (std::getline(file, line))
		{
			mapData.push_back(line);
		}
		file.close();
	}

};

//实现绘图操作
void map::draw(int length, int x, int y)
{
	//i用于便利每一行数据
	for (int i = 0; i < mapData.size(); i++)
	{
		std::string row = mapData[i];
		//j用于遍历i行的每一位数据
		for (int j = 0; i < row.size(); j++)
		{
				
			if(row[i] == '0')
			{
				my_roads.draw(length, (x + j * length), (y + i * length), 1);
			}
			else if (row[j] == '1')
			{
				my_houses.draw(length, (x + j * length), (y + i * length), 1);
			}
			else if (row[j] == '2')
			{
				my_houses.draw(length, (x + j * length), (y + i * length), 1);
			}
			else if (row[j] == '3')
			{
				my_houses.draw(length, (x + j * length), (y + i * length), 1);
			}
			else if (row[j] == '4')
			{
				my_houses.draw(length, (x + j * length), (y + i * length), 1);
			}

		}
	}
};
