#pragma once
//单个map，使用maps进行管理
//具体存储单张地图数据，并
#include <string>
#include "houses.h"
#include "roads.h"
#include "enum_lib.h"
#include<fstream>
class map {
public:
	map(std::string path,const houses &my_house,const roads& my_roads);
	void draw(int length, int x, int y);
private:
	const houses& my_house;
	const roads& my_roads;

};