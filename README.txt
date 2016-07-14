--------------------------------------------------
Japanese Training - Learning Japanese in a fun way
--------------------------------------------------

Installation instructions :
---------------------------
  * Unzip jptraining_vX.X.tar.gz at the ROOT of your nintendo DS file-system
  * You should have something like this :

ROOT
 |_JLPT4
     |_Japanese_Training.nds
     |_Japanese_Training.ds.gba
     |_Japanese_Training.sc.nds
     |_DRAWINGS.DB
     |_EN
       |_hiragana.txt
       |_katakana.txt
       |_kanji.txt
       |_vocabulary_simple.txt
       |_vocabulary_index.txt
       |_game_kanji.txt
     |_FR
       |_hiragana.txt
       |_katakana.txt
       |_kanji.txt
       |_vocabulary_simple.txt
       |_vocabulary_index.txt
       |_game_kanji.txt        

  * Your DS is now ready to play the game
  * Once you launched the game, another file with profiles informations will be created:
    RECORDS.TXT
  * If you update from one version to another : RECORDS.TXT may have a different structure, delete it before playing
  * If you get this error : "Error:Could not initialize libfat!", you may need to patch the ROM with DLDI patcher.
  * The file DRAWINGS.DB contains all the drawings that you can try to draw and match
  * You can add your own drawings to this file.

Version 0.8 (2008 May 13):
------------
  * Vocabulary training is operational

Version 0.7b (2008 April 20):
------------
  * Small modifications to place custom vocabulary in custom slots

Version 0.7a (2008 April 16):
------------
  * Added vocabulary_index.txt, allowing you to add your own vocabulary
  * Started numbers game, but nothing to play with yet

Version 0.7 (2008 March 21):
------------
  * Handwriting recognition :
    - more stable (less freezes)
    - 245 ideograms stored in the database, need to improve my drawing though :-)
    - use append/replace to modify the database
    - use LEFT, RIGHT, L, R to navigate
    - use compare to practice your handwriting

Version 0.6 (2008 February 24):
------------
  * English support thanks to Jason W. Thompson
  * Translation pack (python script) added for other languages support
  * Project updated to devkitpro r21 + latest PALIB + latest uLib

Version 0.5a (2008 January 14):
------------
  * Renamed Japanese Training.txt --> README.txt
  * Fixed bug for hard difficulty
  * Sound is now ok on R4 and M3

Version 0.5 (2008 January 09):
------------
  * Bug correction : was not working on R4 and M3
  * Handwriting recognition : 
    - drawing an ideogram
    - comparing two ideograms
    - adding new drawings
    - replacing existing drawings
    - browsing drawings
    - Need to finish this module though (lots of bugs)
  * Error message on start menu for bad libfat initialization
  * Corrected Kanji 'Sen' (1000)

Version 0.4 (2007 December 20):
------------
  * Kanji game working
  * Sounds added
  * Options menu working
  * Game statistics added
  * Level up after making a perfect
  * Profile management added
  * Pad handling improved
  * Joker function added
  * List and CheckBox added
  * ProgressBar added
  * Pressing start DOES start the game ;-)
  * Graphics improved
  * Makefile improved
  * ROM Header modified with project content
  * Using Eclipse IDE now
  * sources reorganized
  * resources reorganized

Version 0.3 (2007 November 16):
------------
  * Ideograms graphics improved by altarfinch
  * Hiragana game working
  * Katakana game working
  * Profile creation added
  * Difficulty level added
  * Speed level added
  * Options menu (not working yet) added
  * Vocabulary tab enhanced

Version 0.2 (2007 October 18):
------------
  * Graphics designed by olimin added
  * Small animations added
  * Keyboard handling added
  * Vocabulary file added

Version 0.1 (2007 September 20):
------------
First version with a few features:
  * µLibrary Project including PALib
  * learning section implemented
  * 4 tabs : Hiragana, Katakana, Kanji and Vocabulary
  * displaying information on the selected ideogram