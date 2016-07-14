#ifndef __VOCABULARY_LIST_H__
#define __VOCABULARY_LIST_H__

namespace jlpt {

  class VocabularyList : public Component {

    public:
      VocabularyList(Component* parent);
      ~VocabularyList();
      void display(SCREEN scr);
      int dealEvent(SCREEN scr);
      void hide();
      void show();
      void setScoreManager(ScoreManager* s);

    private:
      void drawScroller();
      void readIndex();
      void readDictionnary(int index);
      void displayDictionnaryEntry(bool firstTime);
      void drawHand(int sel);
      bool isScrollerVisible();

    private:
      UL_IMAGE *imgTiles;
      UL_IMAGE* imgKey;
      UL_IMAGE* imgHand;
      Button* buttonUp;
      Button* buttonDown;
      char* imageName;
      char* imageKeyName;
      int offsetX;
      unsigned int offsetY;
      std::vector<std::string> vocabEntries;
      std::vector<std::string> meaningEntries;
      std::vector<u16*> kanaEntries;
      int selectedKana;
      u8 selectedEntry;
      ScoreManager* scoreManager;
      Jis* jis;
      int kanaIndex[51];
  };

}

#endif // __VOCABULARY_LIST_H__
