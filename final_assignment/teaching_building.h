#pragma once
#include "abstract_house.h"
class teaching_building :public abstract_house {
public:
	teaching_building();
	virtual int get_id() override;
	virtual void draw(int x, int y) override;


};