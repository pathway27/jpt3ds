#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__

namespace jlpt {

  typedef struct _RECORDS_ {
      bool isNew;
      char name[20];
      int nbGames[8];
      int level[8];
      int perfects[8];
      int goodAnswers[8];
      int badAnswers[8];
      int nbPassed[8];
      int nbEndOfTime[8];
      int nbAbortions[8];
      int defaultDifficulty;
      int defaultSpeed;
      bool defaultJoker;
      int language;
  } RECORDS, *pRECORDS;

  class ScoreManager {
    public:
      ScoreManager();
      ~ScoreManager();
      void readProfiles();
      void writeProfiles();
      void incNbGames(int gameId);
      void incPerfects(int gameId);
      void incGoodAnswers(int gameId);
      void incBadAnswers(int gameId);
      void incNbPassed(int gameId);
      void incNbEndOfTime(int gameId);
      void incAbortions(int gameId);
      void incLevel(int gameId, int maxLevels);
      void setDefaultDifficulty(int difficulty);
      void setDefaultSpeed(int speed);
      void setDefaultJoker(bool joker);
      void setSelectedProfile(int profile);
      void setLanguage(int language);
      int getLanguage();
      RECORDS* getRecords();      
      RECORDS getSelectedRecord();
      int getLevel(int gameId);
      char* getGameLevel(int gameId);
      void reset();
      void resetScore(int scoreIndex);
      void deleteProfile();
    private:
      void createEmptyRecordsFile();
      void resetScores(int profile);
      
    private:
      int selectedProfile;
      RECORDS records[3];
  };
}

#endif // __SCORE_MANAGER_H__
