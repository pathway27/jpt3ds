#include "Dimension.h"

using namespace jlpt;

Dimension::Dimension(int width, int height) {
	m_width = width;
	m_height = height;
}

Dimension::~Dimension() {

}

void Dimension::setSize(int width, int height) {
	m_width = width;
	m_height = height;
}

int Dimension::getWidth() {
	return m_width;
}

int Dimension::getHeight() {
	return m_height;
}
