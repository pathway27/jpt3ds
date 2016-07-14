#ifndef __IMAGE_H__
#define __IMAGE_H__

namespace jlpt {

	class Image : public Component {
		public:
			Image(Component* parent, char* txt);
			~Image();
	};
}

#endif // __IMAGE_H__
