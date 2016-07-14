#ifndef __MENULEARN_H__
#define __MENULEARN_H__

namespace jlpt {

	class MenuLearn : public Menu {

		public:
			MenuLearn(Component* parent, ScoreManager* s);
			~MenuLearn();
		
		private:
		  GridHiragana* hiraganaGrid;
		  GridKatakana* katakanaGrid;
		  GridKanji* kanjiGrid;
		  VocabularyList* vocabList;
	};
}

#endif // __MENULEARN_H__
