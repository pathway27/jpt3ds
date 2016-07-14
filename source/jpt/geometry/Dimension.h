#ifndef __DIMENSION_H__
#define __DIMENSION_H__

namespace jlpt {

	class Dimension {
		public:
			Dimension(int width, int height);
			~Dimension();
			void setSize(int width, int height);
			int getWidth();
			int getHeight();

		private:
			int m_width;
			int m_height;
	};
}

#endif // __DIMENSION_H__
