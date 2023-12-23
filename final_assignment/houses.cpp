#include"houses.h"

//构造函数，初始化img对象(传入对象地址的通配形式，如img/img*.png，使用实际照片序号替换*标记）
//**************************  0索引用于给道路占位（道路索引为0）  ************************************
houses::houses(std::wstring path, int n) 
{	
	//先全设为true，注意vector不能直接放值，要push进去
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			house_orientation[i][j] = true;
		}
		
	}

	house_img.push_back(nullptr);

	//加载图片
	IMAGE* img;//使用new在堆区创建IMAGE类型地址
	for (int i = 1; i <= n; i++)
	{	
		//拼接图片完整文件路径，具有普遍扩展性
		//注意这里的图片顺序要和enum.lib中的一一对应，从1开始标号
		std::wstring filename = path + std::to_wstring(i) + L".png";
		img = new IMAGE();
		loadimage(img, filename.c_str());//加载图片
		house_img.push_back(img);//将图片地址的指针数据存放到house_img中保存
	}
}

//绘制函数:传入当前地图数据，并将房屋绘制上
void houses::draw(int length, int x, int y,int house_type)const
{	//渲染绘制图片
	putimage(x, y, length,length,house_img[house_type],0,0);//最后两个值是偏移量
}

//为绘制道路提供此种类的房子是否在这个方向开门
bool houses::is_door(int direction, char c) const
{
	int house_type = c - '0';
	return house_orientation[house_type][direction];//后期可拓展
}


//析构函数，析构img对象
//不用设为虚函数，在子类中没有新的数据成员
houses::~houses()
{
	while (!house_img.empty()) {
		delete house_img.back();
		house_img.pop_back();
	}
}
