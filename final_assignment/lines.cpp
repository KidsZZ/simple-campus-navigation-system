#include"lines.h"


//构造函数，初始化数据
lines::lines(int length, int width, int row, int column, int fixed_length)
{
	this->length = length;
	this->width = width;
	this->row = row;
	this->column;
    this->fixed_length;


}
//析构函数
lines::~lines()
{

}
//绘制函数，绘制分割线（x,y）为地图左上角的点
void lines::draw(int x, int y)
{
   
    // 计算单元格宽度和高度,因为是正方形所以计算一次
    int cellLength = length / column;


    // 绘制界面
    for (int i = 0; i <= column; i++) {
        line(x, (y+i * cellLength), width, (y+i * cellLength));
    }
    for (int i = 0; i <= row; i++) {
        line((x+i * cellLength), y, (x + i * cellLength), length);
        
    }
}
