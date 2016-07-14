#include <ulib/ulib.h>
#include "../Tools.h"
#include "../files/File.h"
#include "../files/FileWriter.h"
#include "../files/FileReader.h"
#include "ScoreManager.h"

using namespace jlpt;

ScoreManager::ScoreManager() {
  selectedProfile = -1;
}

ScoreManager::~ScoreManager() {
  // NOTHING TO DO
}

void ScoreManager::setSelectedProfile(int profile) {
  selectedProfile = profile;
}

void ScoreManager::reset() {
  resetScores(selectedProfile);
}

void ScoreManager::resetScores(int profile) {
  if (profile > -1) {
    for (int j = 0; j < 8; j++) {
      records[profile].nbGames[j] = 0;
      records[profile].level[j] = 0;
      records[profile].perfects[j] = 0;
      records[profile].goodAnswers[j] = 0;
      records[profile].badAnswers[j] = 0;
      records[profile].nbPassed[j] = 0;
      records[profile].nbEndOfTime[j] = 0;
      records[profile].nbAbortions[j] = 0;
    }
  }
}

void ScoreManager::resetScore(int scoreIndex) {
  records[selectedProfile].nbGames[scoreIndex] = 0;
  records[selectedProfile].level[scoreIndex] = 0;
  records[selectedProfile].perfects[scoreIndex] = 0;
  records[selectedProfile].goodAnswers[scoreIndex] = 0;
  records[selectedProfile].badAnswers[scoreIndex] = 0;
  records[selectedProfile].nbPassed[scoreIndex] = 0;
  records[selectedProfile].nbEndOfTime[scoreIndex] = 0;
  records[selectedProfile].nbAbortions[scoreIndex] = 0;
}

void ScoreManager::deleteProfile() {
  if (selectedProfile > -1) {
    records[selectedProfile].isNew = true;
    sprintf(records[selectedProfile].name, "%s", "\0");
    resetScores(selectedProfile);
    records[selectedProfile].defaultDifficulty = 0;
    records[selectedProfile].defaultSpeed = 0;
    records[selectedProfile].defaultJoker = true;
    records[selectedProfile].language = 1; // English par defaut
  }

  writeProfiles();
}

void ScoreManager::createEmptyRecordsFile() {
  // Initialisation des donnees
  for (int i = 0; i < 3; i++) {
    records[i].isNew = true;
    sprintf(records[i].name, "%s", "\0");
    resetScores(i);
    records[i].defaultDifficulty = 0;
    records[i].defaultSpeed = 0;
    records[i].defaultJoker = true;
    records[i].language = 1; // English par defaut
  }

  // Ecriture des donnees
  writeProfiles();
}

int ScoreManager::getLanguage() {
  return records[selectedProfile].language;
}

RECORDS ScoreManager::getSelectedRecord() {
  return records[selectedProfile];
}

RECORDS* ScoreManager::getRecords() {
  return &records[0];
}

void ScoreManager::readProfiles() {
  // Lecture du profile
  FileReader* fileReader = new FileReader("/JLPT4/records.txt", ASCII);
  fileReader->open("rb");
  if (fileReader->exists()) {
    fileReader->read(&records, sizeof(records), 1);
    fileReader->close();
  } else {
    createEmptyRecordsFile();
  }
}

void ScoreManager::writeProfiles() {
  // Ecriture du profile
  FileWriter* fileWriter = new FileWriter("/JLPT4/records.txt", ASCII);
  fileWriter->open("wb");
  fileWriter->write(&records, sizeof(records), 1);
  fileWriter->close();
}

void ScoreManager::incNbGames(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    records[selectedProfile].nbGames[gameId]++;
  }
}

void ScoreManager::incPerfects(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    records[selectedProfile].perfects[gameId]++;
  }
}

void ScoreManager::incGoodAnswers(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    records[selectedProfile].goodAnswers[gameId]++;
  }
}

void ScoreManager::incBadAnswers(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    records[selectedProfile].badAnswers[gameId]++;
  }
}

void ScoreManager::incNbPassed(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    records[selectedProfile].nbPassed[gameId]++;
  }
}

void ScoreManager::incNbEndOfTime(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    records[selectedProfile].nbEndOfTime[gameId]++;
  }
}

void ScoreManager::incAbortions(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    records[selectedProfile].nbAbortions[gameId]++;
  }
}

void ScoreManager::incLevel(int gameId, int maxLevels) {
  if (selectedProfile > -1 && gameId > -1) {
    int lvl = records[selectedProfile].level[gameId];
    lvl++;
    if (lvl > maxLevels) {
      lvl = maxLevels;
    }
    records[selectedProfile].level[gameId] = lvl;
  }
}

int ScoreManager::getLevel(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    return records[selectedProfile].level[gameId];
  }
  return -1;
}

char* ScoreManager::getGameLevel(int gameId) {
  if (selectedProfile > -1 && gameId > -1) {
    int level = records[selectedProfile].level[gameId];
    // HIRAGANA ou KATAKANA
    if (gameId == 0 || gameId == 1) {
      switch (level) {
        case 0:
          return "Jedi Initiate 1";
        case 1:
          return "Jedi Initiate 2";
        case 2:
          return "Jedi Initiate 3";
        case 3:
          return "Jedi Initiate 4";
        case 4:
          return "Jedi Padawan 1";
        case 5:
          return "Jedi Padawan 2";
        case 6:
          return "Jedi Padawan 3";
        case 7:
          return "Jedi Padawan 4";
        case 8:
          return "Jedi Knight 1";
        case 9:
          return "Jedi Knight 2";
        case 10:
          return "Jedi Knight 3";
        case 11:
          return "Jedi Knight 4";
        case 12:
          return "Jedi Master 1";
        case 13:
          return "Jedi Master 2";
        case 14:
          return "Jedi Master 3";
        case 15:
          return "Jedi Master 4";
        case 16:
          return "Grand Master";
      }
    }
    // GAME KANJI
    if (gameId == 2) {
      switch (level) {        
        case 0:
          return "Jedi Initiate 1";
        case 1:
          return "Jedi Initiate 2";
        case 2:
          return "Jedi Initiate 3";
        case 3:
          return "Jedi Initiate 4";
        case 4:
          return "Jedi Initiate 5";
        case 5:
          return "Jedi Initiate 6";
        case 6:
          return "Jedi Initiate 7";
        case 7:
          return "Jedi Initiate 8";          
        case 8:
          return "Jedi Padawan 1";
        case 9:
          return "Jedi Padawan 2";
        case 10:
          return "Jedi Padawan 3";
        case 11:
          return "Jedi Padawan 4";
        case 12:
          return "Jedi Padawan 5";
        case 13:
          return "Jedi Padawan 6";
        case 14:
          return "Jedi Padawan 7";
        case 15:
          return "Jedi Padawan 8";          
        case 16:
          return "Jedi Knight 1";
        case 17:
          return "Jedi Knight 2";
        case 18:
          return "Jedi Knight 3";
        case 19:
          return "Jedi Knight 4";
        case 20:
          return "Jedi Knight 5";
        case 21:
          return "Jedi Knight 6";
        case 22:
          return "Jedi Knight 7";
        case 23:
          return "Jedi Knight 8";          
        case 24:
          return "Jedi Master 1";
        case 25:
          return "Jedi Master 2";
        case 26:
          return "Jedi Master 3";
        case 27:
          return "Jedi Master 4";
        case 28:
          return "Jedi Master 5";
        case 29:
          return "Jedi Master 6";          
        case 30:
          return "Grand Master";
      }
    }
    // GAME VOCAB
    if (gameId == 3) {
      switch (level) {        
        case 0:
          return "White belt 1";
        case 1:
          return "White belt 2";
        case 2:
          return "White belt 3";
        case 3:
          return "White belt 4";
        case 4:
          return "White belt 5";
        case 5:
          return "Yellow belt 1";
        case 6:
          return "Yellow belt 2";
        case 7:
          return "Yellow belt 3";          
        case 8:
          return "Yellow belt 4";
        case 9:
          return "Yellow belt 5";
        case 10:
          return "Orange belt 1";
        case 11:
          return "Orange belt 2";
        case 12:
          return "Orange belt 3";
        case 13:
          return "Orange belt 4";
        case 14:
          return "Orange belt 5";
        case 15:
          return "Red belt 1";          
        case 16:
          return "Red belt 2";
        case 17:
          return "Red belt 3";
        case 18:
          return "Red belt 4";
        case 19:
          return "Red belt 5";
        case 20:
          return "Green belt 1";
        case 21:
          return "Green belt 2";
        case 22:
          return "Green belt 3";
        case 23:
          return "Green belt 4";          
        case 24:
          return "Green belt 5";
        case 25:
          return "Purple belt 1";
        case 26:
          return "Purple belt 2";
        case 27:
          return "Purple belt 3";
        case 28:
          return "Purple belt 4";
        case 29:
          return "Purple belt 5";          
        case 30:
          return "Brown belt 1";
        case 31:
          return "Brown belt 2";
        case 32:
          return "Brown belt 3";
        case 33:
          return "Brown belt 4";
        case 34:
          return "Brown belt 5";
        case 35:
          return "Black belt 1";
        case 36:
          return "Black belt 2";
        case 37:
          return "Black belt 3";
        case 38:
          return "Black belt 4";
        case 39:
          return "Black belt 5";  
        case 40:
          return "Little master";
        case 41:
          return "Master";
        case 42:
          return "Grand master";   
        case 43:
          return "Grand master"; 
        case 44:
          return "Grand master"; 
        case 45:
          return "Grand master"; 
        case 46:
          return "Grand master"; 
        case 47:
          return "Grand master"; 
        case 48:
          return "Grand master"; 
        case 49:
          return "Grand master"; 
      }
    }    
  }
  return "none";
}

void ScoreManager::setDefaultDifficulty(int difficulty) {
  if (selectedProfile > -1) {
    records[selectedProfile].defaultDifficulty = difficulty;
  }
}

void ScoreManager::setDefaultSpeed(int speed) {
  if (selectedProfile > -1) {
    records[selectedProfile].defaultSpeed = speed;
  }
}

void ScoreManager::setDefaultJoker(bool joker) {
  if (selectedProfile > -1) {
    records[selectedProfile].defaultJoker = joker;
  }
}

void ScoreManager::setLanguage(int lang) {
  if (selectedProfile > -1) {
    records[selectedProfile].language = lang;
  }
}
