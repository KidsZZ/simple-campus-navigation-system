#include"roads.h"


//不绘制png的透明部分
#pragma comment (lib, "MSIMG32.lib")
void putimage_alpha(IMAGE& image, int x, int y, int w = -1, int h = -1)
{
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	int width = image.getwidth();
	int height = image.getheight();
	if (w == -1)w = width;
	if (h == -1)h = height;
	AlphaBlend(GetImageHDC(), x, y, w, h, GetImageHDC(&image), 0, 0, width, height, blendfunc);
}

//构造函数，载入道路图片
roads::	roads(std::wstring path, int n) 
{
	road_img.push_back(nullptr);
	//加载图片
	IMAGE* img;//使用new在堆区创建IMAGE类型地址
	for (int i = 1; i <= n; i++)
	{
		//拼接图片完整文件路径，具有普遍扩展性
		//注意这里的图片顺序要和enum.lib中的一一对应，从1开始标号
		std::wstring filename = path + L"road"+std::to_wstring(i) + L".png";
		img = new IMAGE();
		loadimage(img, filename.c_str());//加载图片
		road_img.push_back(img);//将图片地址的指针数据存放到house_img中保存
	}

}

//绘制函数，传入存放地图信息的结构体进行绘制
void roads:: draw(int length, int x, int y, int direction)const
{
	putimage_alpha(*road_img[direction], x, y, length, length);//最后两个值是偏移量
}

//析构函数，释放道路图片
roads::	~roads() 
{
	while (!road_img.empty()) {
		delete road_img.back();
		road_img.pop_back();
	}
}



