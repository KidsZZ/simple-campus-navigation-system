#pragma once
//这是主页面窗口，管理不同页面（*因为easyx不支持多窗口，所以通过对不同窗口记录index值来切换不同窗口


class Widget {
public:
	void init();//对主页面进行初始化，进入选择（1.编辑地图 2.地图导航）
	void run();
	void close();
private:

};