//单个map，使用maps进行管理
//具体存储单张地图数据，并
#include"map.h"

class map {
public:
	//读取path文件路径中的数据，并创建houses与roads对象存入相对应的数据
	map(std::string path, const houses& my_houses, const roads& my_roads):my_houses(my_houses),my_roads(my_roads)
	{

		std::ifstream file(path);
		if (file.is_open())
		{
			//budong
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
	void draw(int length, int x, int y)
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
				else if (row[j] == 'h')
				{
					my_houses.draw(length, (x + j * length), (y + i * length), 1);
				}
			}
	    }
	};
private:
	const houses& my_houses;
	const roads& my_roads;
	std::vector<std::string>mapData;

};