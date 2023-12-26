#include"map.h"
#include <iostream>
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

	//对mapData进行初始化操作
	//即全部用占位符来替代
	std::vector<std::vector<char>> mapData_temp(row, std::vector<char>(column, '-'));
	mapData = mapData_temp;

	//使用path找到并读入磁盘中的存档文件
	read_file();

	//初始设为不要导航
	is_navigation = false;

	//将初始导航路径全设为false
	std::vector<std::vector<bool>> mapNavigation_temp(row, std::vector<bool>(column, false));
	mapNavigation = mapNavigation_temp;
}


//在文件开头放一行空行（一个换行符），用来判断文件是否是空文件
void map::read_file()
{
	//传入地图路径
	std::ifstream file(path); 
	// 判断文件是否成功打开
	if (file.is_open())
	{
		// 定位到文件末尾
		char temp_c;
		file >> temp_c;
		// 判断文件大小是否为0,及文件是否为空文件
		if (file.eof())//是空文件
		{
			//不进行处理
		}

		else
		{
			//先读取第一行，检查row与column是否异常
			int fileRow, fileColumn;
			file >> fileRow >> fileColumn;

			//下面是对于数据是否异常的判断
			//即如果文件中记录的单元格行数和单元格列数，与传入参数不同则报错
			if (fileRow != row || fileColumn != column)
			{
				std::cout << "Error the row or column is erroneous" << std::endl;
				return;
			}
			char tempc;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					file >> tempc;
					if (tempc != '-') {
						mapData[i][j] = tempc;
					}
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
			if (mapData[i][j] != '-' && mapData[i][j] != '0')
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
	//第一行放一个0
	file << '0' << std::endl;
	//第二排放置行数和列数
	file << row << ' ' << column <<std::endl;
	//接下来放置地图数据
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
	//printf("select_road_type init!\n");
	//首先创建一个bool类型的vector数组来存储此道路上下左右四个方向的信息
	std::vector<bool>road_type(4, false);
	if (j == 0 && i != 0 && i != row-1)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(direction::down, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		//此坐标左侧为地图边界，默认为false

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(direction::left, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(direction::up, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == 0 && j != 0 && j != column-1)
	{
		//此坐标上侧为地图边界，默认为false

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(direction::right, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(direction::left, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(direction::up, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (j == column-1 && i != 0 && i != row-1)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(direction::down, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(direction::right, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		//此坐标右侧为地图边界，默认为false

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(direction::up, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == row-1 && j != 0 && j != column-1)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(direction::down, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(direction::right, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(direction::left, mapData[i][j + 1]))))
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
			((mapData[i][j + 1] != '-' && my_houses.is_door(direction::left, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(direction::up, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == 0 && j == column-1)
	{
		//利用||短路的性质，进行逻辑运算
		//此坐标上侧为地图边界，默认为false

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(direction::right, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		//此坐标右侧为地图边界，默认为false

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(direction::up, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	if (i == row-1 && j == 0)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(direction::down, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		//此坐标左侧为地图边界，默认为false

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(direction::left, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		//此坐标下侧为地图边界，默认为false
	}

	if (i == row-1 && j == column-1)
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(direction::down, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(direction::right, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		//此坐标右侧为地图边界，默认为false

		//此坐标下侧为地图边界，默认为false
	}

	if((i>0&&i<row-1)&&(j>0&&j<column-1))
	{
		//利用||短路的性质，进行逻辑运算
		if (mapData[i - 1][j] == '0' ||
			((mapData[i - 1][j] != '-' && my_houses.is_door(direction::down, mapData[i - 1][j]))))
		{
			road_type[0] = true;
		}

		if (mapData[i][j - 1] == '0' ||
			((mapData[i][j - 1] != '-' && my_houses.is_door(direction::right, mapData[i][j - 1]))))
		{
			road_type[1] = true;
		}

		if (mapData[i][j + 1] == '0' ||
			((mapData[i][j + 1] != '-' && my_houses.is_door(direction::left, mapData[i][j + 1]))))
		{
			road_type[2] = true;
		}

		if (mapData[i + 1][j] == '0' ||
			((mapData[i + 1][j] != '-' && my_houses.is_door(direction::up, mapData[i + 1][j]))))
		{
			road_type[3] = true;
		}
	}

	//没有true，默认up_down
	if (road_type[0] == 0 && road_type[1] == 0 && road_type[2] == 0 && road_type[3] == 0) {
		return 3;
	}

	//一个true
	if (road_type[0] == 1 && road_type[1] == 0 && road_type[2] == 0 && road_type[3] == 0) {
		return 3;
	}
	if (road_type[0] == 0 && road_type[1] == 1 && road_type[2] == 0 && road_type[3] == 0) {
		return 4;
	}
	if (road_type[0] == 0 && road_type[1] == 0 && road_type[2] == 1 && road_type[3] == 0) {
		return 4;
	}
	if (road_type[0] == 0 && road_type[1] == 0 && road_type[2] == 0 && road_type[3] == 1) {
		return 3;
	}

	//通过打表判断数组后，找到对应的图片
	//两个true
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

	//三个true
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

	//四个true
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
//6.绘制导航（如果需要）
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
	setfillcolor(0xcbe2ea);
	solidrectangle(x, y, x + width, y + height);

	//绘制鼠标选择辅助线
	//当鼠标在地图上
	if (mouse_now_abstract_x != -1 && mouse_now_abstract_y != -1) {
		//printf("dashed_line draw\nmouse_x:%d mouse_y:%d\n", mouse_now_abstract_x, mouse_now_abstract_y);
		//绘制column上的标记
		//printf("x:%d y:%d width:%d height:%d\n", x, y, width, height);
		//printf("draw solidrectangle\n left:%d top:%d right:%d bottom:%d\n", x + mouse_now_abstract_x * length, y, x + (mouse_now_abstract_x + 1) * length, y + height);
		setfillcolor(0xAAAA00);
		solidrectangle(x + mouse_now_abstract_x * length, y, x + (mouse_now_abstract_x + 1) * length, y + height);
		//绘制row上的标记
		//printf("draw solidrectangle\n left:%d top:%d right:%d bottom:%d\n", x, y + mouse_now_abstract_y * length, x + width, y + (mouse_now_abstract_y + 1));
		solidrectangle(x, y + mouse_now_abstract_y * length, x + width, y + (mouse_now_abstract_y + 1)*length);
	}

	//绘制格子间的线
	draw_subline();
	
	//static int times = 0;
	//printf("building draw init no.%d\n",times++);

	//通过检索数组中的数据项，分别调用roads和houses绘制地图
	for (int i =0; i <row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (mapData[i][j] != '0' && mapData[i][j] != '-')
			{
				//printf("draw house init\n");
				my_houses.draw(length, (x + (j * length)), (y + (i * length)), (mapData[i][j] - '0'));
				//printf("draw house success\n");
			}
			else if (mapData[i][j] == '0')
			{
				//在绘制道路的时候，需要调用select_road_type得知道路种类
				//printf("draw road init\n");
				my_roads.draw(length, (x + (j  * length)), (y + (i * length)), select_road_type(i, j));
				//printf("draw road success\n");
			}
		}
	}

	//当is_navigation == true 时根据mapNavigation绘制导航
	if (is_navigation) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (mapNavigation[i][j]) {
					setfillcolor(GREEN);
					//在路径中心绘制圆圈
					solidcircle(x + j * length + length * 0.5, y + i * length + 0.5 * length, length * 0.1);
				}
			}
		}
	}

}


//给定坐标和房子id(road id 为0）
void map::add_building(int x, int y, int house_type)
{
	//printf("add_builiding active\n");
	//首先计算此时鼠标的位置信息；
	translate_xy(real_coord, x, y);
	
	//当当前种类建筑没有被放置时，允许放置建筑
	if (!is_building_present[house_type]) {
		//printf("add house no.%d at x:%d y:%d\n", house_type, real_coord[1], real_coord[0]);
		mapData[real_coord[0]][real_coord[1]] = char(house_type+'0');
		//printf("%c\n", mapData[real_coord[0]][real_coord[1]]);
		
		//如果放置的建筑不是道路，则更新标记
		if (house_type != 0) {
			//该地图房屋数+1
			building_num++;

			//记录房屋坐标
			building_position[house_type][0] = real_coord[0];
			building_position[house_type][1] = real_coord[1];

			//记录当前种类房屋已被放置
			is_building_present[house_type] = true;
			//printf("add house complete");
		}
	}
}

// 给定坐标(删除房子和道路用一个函数，如果本来就没有东西就不变）
void map::delete_build(int x, int y)
{
	//首先计算此时鼠标的位置信息；
	translate_xy(real_coord, x, y);
	
	//如果不为占位符，则删除该位置建筑
	if (mapData[real_coord[0]][real_coord[1]] != '-') {

		//如果不为道路，则清除相关标记
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
	/*printf("\nnowx: %d", x);
	printf(" nowy: %d\n", y);
	printf("mapx:%d", this->x);
	printf("mapy:%d\n", this->y);*/
	//当没有绘制地图的时候
	if (this->x == -1 && this->y == -1 && width == -1 && height == -1) {
		return false;
	}
	//当给出的点在地图上的时候
	if (x > this->x && x<(this->x + width) && y>this->y && (y < this->y + height)) {
		
		//计算逻辑值
		//按先行数再列数存储
		ans[1] = (x - this->x) / length;
		ans[0] = (y - this->y) / length;
		/*printf("ax:%d", ans[0]);
		printf(" ay:%d\n", ans[1]);*/

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
		mouse_now_abstract_x = real_coord[1];
		mouse_now_abstract_y = real_coord[0];
	}

}

//绘制辅助线，帮助用户放置建筑
//(x,y)为绘制地图的的左上角，后两位参数为地图的宽度和长度
void map::draw_subline()
{
	setlinecolor(RGB(225, 225, 225));
	setfillcolor(RGB(225, 225, 225));
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





//连接两地（最短路）
//使用宽度优先搜索
bool map::connect_houses(int house_type1, int house_type2){
	printf("house_type1:%d house_type2:%d\n", house_type1, house_type2);

	//重置mapNavigation
	std::vector<std::vector<bool>> mapNavigation_temp(row, std::vector<bool>(column, false));
	mapNavigation = mapNavigation_temp;

	//如果这两个建筑还没有放置，则返回false,表示导航失败
	if (!is_building_present[house_type1] || !is_building_present[house_type2]) {
		is_navigation = false;
		return false;
	}

	//标记当前点是否已经被搜索过了
	//如果已经被搜索过了，设为true
	bool flag[30][30] = { false };

	

	//这两个数组保存搜索的方向
	static int move_x[4] = { 0,1,-1,0 };
	static int move_y[4] = { 1,0,0,-1 };

	//保存接下来要寻找的一系列点的坐标
	//不使用deque模拟队列的原因是之后还要回溯
	//qy中保存二维数组第一项，qx保存二维数组第二项
	int qx[1000] = { 0 };
	int qy[1000] = { 0 };

	//队头队尾都先使用后加1
	//对头用于去除元素，队尾用于判断队列是否为空
	int head = 0;
	int tail = 0;

	//设置回溯队列
	int memory[1000] = { 0 };

	//将起点的坐标入队
	qy[tail] = building_position[house_type1][0];
	qx[tail] = building_position[house_type1][1];

	//将起点的回溯下标设为-1，表示根节点
	memory[tail] = -1;

	//设置起点的坐标已被搜索
	flag[qy[tail]][qx[tail]] = true;

	++tail;



	//只要队列不空，就一直查找
	int times=0;
	while (head != tail) {
		//printf("\n\ntimes:%d\n", times++);
		//取出对头坐标
		int tempx = qx[head];
		int tempy = qy[head];
		//printf("headx:%d heady:%d\n",tempx,tempy);
		++head;

		//下面算的点的父亲节点
		int fIndex = head - 1;

		for (int i = 0; i < 4; i++) {
			//算出下一个点
			int nextx = tempx + move_x[i];
			int nexty = tempy + move_y[i];

			//如果当前点在地图上
			if (nextx >= 0 && nextx < column && nexty >= 0 && nexty < row &&
				//是道路
				(mapData[nexty][nextx]=='0'||
				//或者是建筑且此路通
				(mapData[nexty][nextx]>'0'&&mapData[nexty][nextx] <= building_num+'0')&&
				my_houses.is_door(i,mapData[nexty][nextx])) &&
				//当前点还没有被搜索过
				!flag[nexty][nextx]
				) {

				//printf("nextx:%d nexty:%d\n", nextx, nexty);
				//printf("now mapData:%c\n", mapData[nexty][nextx]);

				/*for (int i = 0; i < row; i++) {
					for (int j = 0; j < column; j++) {
						printf("%c", mapData[i][j]);
					}
					printf("\n");
				}*/

				//表示当前点已经被搜索过了
				flag[nexty][nextx] = true;

				
				//如果找到了目的地
				if (mapData[nexty][nextx] == house_type2 + '0') {
					printf("find success1\n");
					is_navigation = true;
					while (memory[fIndex] != -1) {
						//printf("y:%d x:%d\n", qy[fIndex], qx[fIndex]);
						mapNavigation[qy[fIndex]][qx[fIndex]] = true;
						fIndex = memory[fIndex];
					}
					printf("find success2\n");
					return true;
				}

				//不是目的地
				qy[tail] = nexty;
				qx[tail] = nextx;
				memory[tail] = fIndex;
				tail++;
			}
		}
	}
	//没有找到
	is_navigation = false;
	return false;

}

//清除导航路线(用于之后扩展)
void map::clear_connect_houses(){
	is_navigation = false;
	printf("clear_connect_house success!\n");
}

