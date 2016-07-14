#include "Rectangle.h"

using namespace jlpt;

Rectangle::Rectangle() {
	setRect(DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

Rectangle::Rectangle(signed short x, signed short y, int width, int height) {
	setRect(x, y, width, height);
}

int Rectangle::getWidth() {
	return width;
}

int Rectangle::getHeight() {
	return height;
}

signed short Rectangle::getX() {
	return x;
}

signed short Rectangle::getY()	{
	return y;
}

void Rectangle::setWidth(int width) {
	this->width = width;
}

void Rectangle::setHeight(int height) {
	this->height = height;
}

void Rectangle::setX(signed short x) {
	this->x = x;
}

void Rectangle::setY(signed short y) {
	this->y = y;
}

void Rectangle::setPosition(signed short x, signed short y) {
	setX(x);
	setY(y);
}

void Rectangle::setSize(int width, int height)	{
	setWidth(width);
	setHeight(height);
}

void Rectangle::setRect(signed short x, signed short y, int width, int height)	{
	setPosition(x, y);
	setSize(width, height);
}

signed short Rectangle::getMaxX()	{
	return this->x + this->width;
}

signed short Rectangle::getMaxY()	{
	return this->y + this->height;
}

signed short Rectangle::getMidX()	{
	return this->x + this->width/2;
}

signed short Rectangle::getMidY()	{
	return this->y + this->height/2;
}

bool Rectangle::contains(signed short x, signed short y) {
	if (x >= getX() && x <= getMaxX() && y >= getY() && y <= getMaxY()) {
		return true;
	}
	return false;
}
