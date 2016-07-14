#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

namespace jlpt {

	typedef enum {
		DEFAULT_X = 0,
		DEFAULT_Y = 0,
		DEFAULT_WIDTH = 0,
		DEFAULT_HEIGHT = 0
	};
	
	class Rectangle {
	   public:
			Rectangle();		
			Rectangle(signed short x, signed short y, int width, int height);		
			int getWidth();		
			int getHeight();		
			signed short getX();		
			signed short getY();		
			void setWidth(int width);		
			void setHeight(int height);		
			void setX(signed short x);		
			void setY(signed short y);		
			void setPosition(signed short x, signed short y);		
			void setSize(int width, int height);		
			void setRect(signed short x, signed short y, int width, int height);		
			signed short getMaxX();		
			signed short getMaxY();		
			signed short getMidX();		
			signed short getMidY();		
			bool contains(signed short x, signed short y);
		private:
			signed short x;
			signed short y;
			int width;
			int height;
	};		
}	

#endif // __RECTANGLE_H__
