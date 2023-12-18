#include"houses.h"

//构造函数，初始化img对象(传入对象地址的通配形式，如img/img*.png，使用实际照片序号替换*标记）
houses::houses(std::wstring path, int n) 
{
	house_orientation=
	{
		//后期需要进行扩展
		{true, true, true, true, },//library
		{ true,true,true,true, },//dorminory
		{ true,true,true,true, },//teaching_building
		{ true,true,true,true, },//canteen
		{ true,true,true,true, },
	};

	for (int i = 1; i <= n; i++)
	{
		std::wstring filename = path + std::to_wstring(n) + L".png";//拼接图片完整文件路径，具有普遍扩展性
		IMAGE* img = new IMAGE;//使用new在堆区创建IMAGE类型地址
		loadimage(img, filename.c_str());//加载图片
		house_img.push_back(img);//将只想图片地址的指针数据存放到house_img中保存
	}
	
};

//绘制函数:传入当前地图数据，并将房屋绘制上
void houses::draw(int width, int height, int x, int y)
{
	putimage(x, y, width, height,house_img[0],x,y);//渲染绘制图片
};

//为绘制道路提供此种类的房子是否在这个方向开门
bool houses::is_door(int direction, int house_type) 
{
	return (house_orientation[house_type][direction]);//后期可拓展
};

	//析构函数，析构img对象
	//不用设为虚函数，在子类中没有新的数据成员
houses::~houses()
{
	for (auto img:house_img)
	{
		delete(img);
	}
};
