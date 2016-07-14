#include <PA9.h>
#include <ulib/ulib.h>
#include <vector>
#include "../gfx/all_gfx.h"
#include "geometry/Point.h"
#include "geometry/Dimension.h"
#include "geometry/Rectangle.h"
#include "fonts/Ascii.h"
#include "fonts/Jis.h"
#include "components/ProgressBar.h"
#include "components/Component.h"
#include "data/Stroke.h"
#include "data/Gesture.h"
#include "components/TextComponent.h"
#include "components/DrawComponent.h"
#include "components/Input.h"
#include "components/Keyboard.h"
#include "components/KeyboardJis.h"
#include "components/KeyboardAscii.h"
#include "components/Button.h"
#include "components/CheckBox.h"
#include "components/List.h"
#include "components/Panel.h"
#include "Tools.h"
#include "scores/ScoreManager.h"
#include "grids/Grid.h"
#include "grids/GridHiragana.h"
#include "grids/GridKatakana.h"
#include "grids/GridKanji.h"
#include "grids/VocabularyList.h"
#include "menus/Menu.h"
#include "menus/MenuStart.h"
#include "menus/MenuProfiles.h"
#include "menus/MenuProfile.h"
#include "menus/MenuMain.h"
#include "menus/MenuLearn.h"
#include "menus/MenuPractice.h"
#include "menus/MenuDifficulty.h"
#include "menus/MenuOptions.h"
#include "games/Game.h"
#include "games/GameIdeogram.h"
#include "games/GameHiragana.h"
#include "games/GameKatakana.h"
#include "games/GameKanji.h"
#include "games/GameDraw.h"
#include "games/GameNumbers.h"
#include "games/GameVocabulary.h"
#include "App.h"

using namespace jlpt;

int main() {

  //Initialization of PA_Lib
  PA_Init();
  PA_InitRand();
  PA_InitSound();
  
  fatInitDefault();

  //Initialization of µlibrary
  ulInit(UL_INIT_ALL);
  ulInitGfx();
  ulInitText();
  ulSetMainLcd(SCREEN_DOWN);
  ulSetKeyAutorepeat(UL_KEY_LEFT | UL_KEY_RIGHT | UL_KEY_UP | UL_KEY_DOWN, 30, 6);
  
  PA_InitVBL();
  PA_Init16cBg(SCREEN_UP, BG_0);

  App* app = new App();

  while (1) {

    PA_CheckLid();

    ulReadKeys(0);
    ulStartDrawing2D();

    app->dealEvent(SCREEN_DOWN);
    app->display(SCREEN_DOWN);

    ulEndDrawing();
    ulSyncFrame();
  }

  return 0;
}

