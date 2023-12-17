#include"houses.h"
using namespace std;

class houses {
public:
	//构造函数，初始化img对象(传入对象地址的通配形式，如img/img*.png，使用实际照片序号替换*标记）
	houses(std::string path, int n) 
	{
		//创建字符串用于接受图像的相对路径
		string img_path = path;
		//首先用int类型的数据接收房屋的index号
		int enum_num = n;
	};
	//绘制函数:传入当前地图数据，并将房屋绘制上
	void draw(int width, int height, int x, int y)
	{
		int width = width;
		int height = height;
		int origin_x = x;
		int origin_y = y;

		//创建保存图像的IMAGE的对象指针
		IMAGE img;
	
	}
	//为绘制道路提供此种类的房子是否在这个方向开门
	bool is_door(int direction, int house_type);
	//析构函数，析构img对象
	//不用设为虚函数，在子类中没有新的数据成员
	~houses();

private:
	//使用枚举类记录房子编号
	house_type my_house_type;
	//储存房子的图片
	std::vector<IMAGE*> house_img;
	//储存大门的朝向，使用上左右下的顺序存储
	direction house_direction;
	//开门为true，不开门为false
	std::vector<bool[4]> house_orientation;
};