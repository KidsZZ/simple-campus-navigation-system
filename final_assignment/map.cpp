#include"map.h"
//单个map，使用maps进行管理
// 逻辑判断在此实现
//具体存储单张地图数据

//传入存档路径，houses

map::map(std::string path, houses& my_house, roads& my_roads,
	int column, int row)
	:my_houses(my_house), my_roads(my_roads), path(path),
	//因为还没有绘制地图，所以将width,height,x,y都设置为-1
	height(-1), width(-1), x(-1), y(-1),
	//将记录鼠标当前抽象位置的变量记录为-1，不绘制辅助线
	mouse_now_abstract_x(-1),mouse_now_abstract_y(-1)
{	
	//先初始化mapDate数组
	this->column = column;
	this->row = row;

	for (int i = 0; i < 2; i++)real_coord[i] = -1;

	//初始化设置building_num为0
	building_num = 0;

	for (int i = 0; i < 5; i++) {
		//初始化将建筑都设为不存在
		is_building_present[i] = false;
	}

	//使用path找到并读入磁盘中的存档文件
	read_file();
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
		// 判断文件大小是否为0,及文件是否为空文件
		if (file.tellg() == 0)//是空文件
		{
			//对mapData进行初始化操作
			//即全部用占位符来替代
			std::vector<std::vector<char>> mapData_temp((row), std::vector<char>(column, '-'));
			mapData = mapData_temp;
		}

		else
		{
			//先读取第一行，检查row与column是否异常
			std::string line;
			std::vector<char>rows;
			std::getline(file, line);

			for (char c : line)
			{
				//如果不是空格则暂时存入rows当中
				if (c != ' ')
				{
					rows.push_back(c);
				}
			}

			//下面是对于数据是否异常的判断
			//即如果文件中记录的单元格行数和单元格列数，与传入参数不同则报错
			if (int(rows[0]) != (row+'0') || int(rows[1]) != (column+'0'))
			{
				std::cout << "Error the row or column is erroneous" << std::endl;
				return;
			}

			//清空string
			line.clear();
			//清空vector
			rows.clear();

			//逐行读取数据
			while (std::getline(file, line))
			{
				for (char c : line)
				{
					//如果不是空格则存入二维数组当中
					if (c != ' ')
					{
						rows.push_back(c);
					}
				}

				//实现了从文件第二行开始读入数据，计入mapData当中
				//将row2数组压入mapData当中
				mapData.push_back(rows);
				rows.clear();
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
				building_num++;
				is_building_present[(mapData[i][j] - '0')] = true;
				building_position[(mapData[i][j] - '0')][0] = i;
				building_position[(mapData[i][j] - '0')][1] = j;
			}
		}
	}
	
}


void map::write_file()
{
	//初始化构造函数	  读取file文件所在的位置
	std::ofstream file(path,std::ios::trunc);
	//第一排放置第一的行数和列数
	file << row << ' ' << column << ' ' << building_num<<std::endl;
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

	//通过打表判断数组后，找到对应的图片
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


//draw函数绘制顺序
//0.储存当前绘制地图的数据
//1.绘制地图背景
//2.绘制当前鼠标选择辅助线
//3.绘制地图辅助线
//4.绘制建筑
//5.绘制道路
void map::draw(int width, int height, int x, int y)
{
	//计算每格的边长
	length = (width / column);

	//保存最近一次绘制地图的长宽，供translate_xy使用
	this->width = width;
	this->height = height;

	//保存最近一次绘制地图的坐标，供translate_xy使用
	this->x = x;
	this->y = y;

	//在地图后面绘制背景，防止看不清
	setfillcolor(0xb4e014);
	rectangle(x, y, x + width, y + height);

	//绘制鼠标选择辅助线
	//当鼠标在地图上
	if (mouse_now_abstract_x != -1 && mouse_now_abstract_y != -1) {
		//绘制column上的标记
		rectangle(x + mouse_now_abstract_x * length, y, x + (mouse_now_abstract_x + 1) * length, y + height);
		//绘制row上的标记
		rectangle(x, y + mouse_now_abstract_y * length, x + width, y + (mouse_now_abstract_y + 1));
	}

	//绘制格子间的线
	draw_subline();
	
	//通过检索数组中的数据项，分别调用roads和houses绘制地图
	for (int i =0; i <row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (mapData[i][j] != '0' && mapData[i][j] != '-')
			{
				my_houses.draw(length, (x+(i  * length)), (y+(j * length)), (mapData[i][j] - '0'));
			}
			else if (mapData[i][j] == '0')
			{
				//在绘制道路的时候，需要调用select_road_type得知道路种类
				my_roads.draw(length, (x + (i  * length)), (y + (j * length)), select_road_type(i, j));
			}
		}
	}


}


//给定坐标和房子id(road id 为0）
void map::add_building(int x, int y, int house_type)
{

	//首先计算此时鼠标的位置信息；
	translate_xy(real_coord, x, y);
	
	//当当前种类建筑没有被放置时，允许放置建筑
	if (!is_building_present[house_type]) {
		mapData[real_coord[0]][real_coord[1]] = house_type;
		//该地图房屋数+1
		building_num++;

		//记录房屋坐标
		building_position[house_type][0] = x;
		building_position[house_type][1] = y;
	}
}

// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
void map::delete_build(int x, int y)
{
	//首先计算此时鼠标的位置信息；
	translate_xy(real_coord, x, y);
	
	//如果不为占位符，则删除该位置建筑
	if (mapData[real_coord[0]][real_coord[1]] != '-') {
		//如果不为道路，则清楚相关标记
		if (mapData[real_coord[0]][real_coord[1]] != '0') {
			int house_type = mapData[real_coord[0]][real_coord[1]] - '0';
			is_building_present[house_type] = false;
			building_position[house_type][0] = -1;
			building_position[house_type][1] = -1;
			//房屋数-1
			building_num--;
		}
		//重置数据为‘-’
		mapData[real_coord[0]][real_coord[1]] = '-';
	}

}

//返回给定的地图id是否被编辑过
bool map::is_edited()
{
	if (building_num == 0) {
		return false;
	}
	else
	{
		return true;
	}
}

//计算给定的x，y所对应的格子(传入一个数组保存算出来的值)
bool map::translate_xy(int* ans, int x, int y)
{
	//当没有绘制地图的时候
	if (this->x == -1 && this->y == -1 && width == -1 && height == -1) {
		return false;
	}
	//当给出的点在地图上的时候
	if (x > this->x && x<(this->x + width) && y>this->y && (y < this->y + height)) {
		
		//计算逻辑值
		ans[0] = (x - this->x) / length;
		ans[1] = (y - this->y) / length;

		//在地图上，true
		return true;

	}else {

		//如果不在地图上，则false
		return false;
	}
}


//显示鼠标所停放地标图标所代表的房屋类型
void map::show_house_type(std::string& name,int x, int y)
{
	translate_xy(real_coord, x, y);
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

//绘制虚线辅助线函数的辅助函数
//此函数与鼠标是否在按钮上的函数相似，接收鼠标位置判断是否需要绘制及绘制在哪里
void map::draw_dashed_line(int x,int y)
{
	if (!translate_xy(real_coord, x, y)) {
		//如果不在地图上
		mouse_now_abstract_x = -1;
		mouse_now_abstract_y = -1;
	}
	else {
		//将当前鼠标的位置记录下来，用于draw函数中绘制
		mouse_now_abstract_x = real_coord[0];
		mouse_now_abstract_y = real_coord[1];
	}

}

//绘制辅助线，帮助用户放置建筑
//(x,y)为绘制地图的的左上角，后两位参数为地图的宽度和长度
void map::draw_subline()
{
	//利用for循环绘制竖线
	for (int i = 0; i <= column;i++)
	{
		line(x + i * length, y, x + i * length, y + height);
	}
	//利用for循环绘制横线
	for (int j = 0; j <= row; j++)
	{
		line(x, y + length * j, x + width, y + length * j);
	}
}





//连接两地（最短路）(用于之后扩展)
bool map::connect_houses(int house_type1, int house_type2){

}

//清除导航路线(用于之后扩展)
void clear_connnect_houses(){}

