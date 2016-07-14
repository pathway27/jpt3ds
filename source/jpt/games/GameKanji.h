#ifndef __GAMEKANJI_H__
#define __GAMEKANJI_H__

namespace jlpt {

	class GameKanji : public GameIdeogram {

		public:
			GameKanji(Component* parent, ScoreManager* s);
			~GameKanji();
			std::string readSolution(int rndX, int rndY);
			void* getPalette(int x, int y);
			void* getSprite(int x, int y);
			bool isPaletteOk();
	};
}

#endif // __GAMEKANJI_H__
