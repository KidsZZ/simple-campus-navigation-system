#include"lines.h"


//构造函数，初始化数据
lines::lines(int length, int width, int row, int column, int fixed_length)
{
    //对于lines类中数据成员进行初始化操作
	this->length = length;
	this->width = width;
	this->row = row;
    this->column = column;
    this->fixed_length = fixed_length;
}
//析构函数
lines::~lines()
{
    //重置数据内存
    this->length = 0;
    this->width = 0;
    this->row = 0;
    this->column = 0;
    this->fixed_length = 0;

}
//绘制函数，绘制分割线（x,y）为地图左上角的点
void lines::draw(int x, int y)
{
   
    // 计算单元格宽度和高度,因为是正方形所以计算一次
    int cellLength = length / column;


    // 绘制界线
    for (int i = 0; i <= column; i++)
    {
        line(x, (y+i * cellLength), width, (y+i * cellLength));
    }
    for (int i = 0; i <= row; i++)
    {
        line((x+i * cellLength), y, (x + i * cellLength), length);
    }
}
