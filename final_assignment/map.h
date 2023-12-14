#pragma once
//单个map，使用maps进行管理
#include <string>
class map {
public:
	map(std::string path);
	void draw(int w, int h, int x, int y);
};