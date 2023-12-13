#pragma once
#include "abstract_house.h"
class dorminory :public abstract_house {
public:
	dorminory();
	virtual int get_id() override;
	virtual void draw(int x, int y) override;


};