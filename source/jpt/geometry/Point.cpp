#include "Point.h"

using namespace jlpt;

Point::Point(signed short x, signed short y) {
	m_x = x;
	m_y = y;
}

Point::~Point() {

}

void Point::setLocation(signed short x, signed short y) {
	m_x = x;
	m_y = y;
}

void Point::setX(signed short x) {
	m_x = x;
}   

void Point::setY(signed short y) {
	m_y = y;
}

signed short Point::getX() {
	return m_x;
}

signed short Point::getY() {
	return m_y;
}
