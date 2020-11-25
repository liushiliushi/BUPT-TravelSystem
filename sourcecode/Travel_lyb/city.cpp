#include "city.h"
City::City()
{

}

City::City(QString name, int x, int y, int risk)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->risk = risk;
}

City::~City()
{

}