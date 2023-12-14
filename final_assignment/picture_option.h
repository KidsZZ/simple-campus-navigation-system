#pragma once
//class picture_option用于放置有图片的选择框（用于地图选择页的存档绘制及地图编辑页的选项绘制）
#include "option.h"
#include <graphics.h>
#include <string>
class picture_option :public option {
public:
	picture_option(std::string path,std::string exp);
	picture_option(int width,int length,int x,int y,std::string path,std::string exp);
	void draw(int width, int length, int x, int y);
private:
	//保存图片
	IMAGE* opt_img;
	//保存图片说明
	std::string exp；
};
