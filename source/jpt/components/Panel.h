#ifndef __PANEL_H__
#define __PANEL_H__

namespace jlpt {
	
	class Panel : public Component {

		public:
			Panel(Component* parent);
			Panel(Component* parent, char* title);
			virtual ~Panel();
			char* getTitle();
			void setTabImage(UL_IMAGE* image);
			void loadTabImage(char* imageName, int pixelFormat);			
			UL_IMAGE* getTabImage();

		private:
		   char* m_title;
		   UL_IMAGE* imgTab;
	};
}

#endif // __PANEL_H__
