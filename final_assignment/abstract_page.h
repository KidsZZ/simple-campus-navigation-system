#pragma once
//此类为抽象类，为三个页面类提供接口函数
//这是窗口的基类，在Widget.h中通过调用三个页面具体实现的函数实现页面间的切换
class abstract_page {
protected:
	//用于设置页面的长宽比
	virtual void init() = 0;
	//绘制画面
	virtual void draw() = 0;
	//返回下一个页面序号
	virtual int return_page_id() = 0;
	//析构函数（虚函数）
	virtual ~abstract_page() = 0;
};