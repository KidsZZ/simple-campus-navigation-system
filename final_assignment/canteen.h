#pragma once
#include "abstract_house.h"
class canteen :public abstract_house {
public:
	canteen();
	virtual int get_id() override;
	virtual void draw(int x, int y) override;
};