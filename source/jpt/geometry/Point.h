#ifndef __POINT_H__
#define __POINT_H__

namespace jlpt {

	class Point {
		public:
			Point(signed short x, signed short y);
			~Point();
			void setLocation(signed short x, signed short y);
			void setX(signed short x);
			void setY(signed short y);
			signed short getX();
			signed short getY();

		private:
			signed short m_x;
			signed short m_y;
	};
}

#endif // __POINT_H__
