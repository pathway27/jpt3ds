/*
*  This file is part of jpt3ds,
*  based on jtp by denis.george.
*  Copyright (C) 2016 pathway27
* 
*/

#include <stdio.h>
#include <string.h>

#include <3ds.h>
#include "App.h"

using namespace jlpt;

int main()
{
  gfxInitDefault();
  //gfxSet3D(true); // uncomment if using stereoscopic 3D

  // TODO: init fat filesystem

  //In this example we need one PrintConsole for each screen
  PrintConsole topScreen, bottomScreen;

  //Initialize console for both screen using the two different PrintConsole we have defined
  consoleInit(GFX_TOP, &topScreen);
  consoleInit(GFX_BOTTOM, &bottomScreen);

  // Before doing any text printing we should select the PrintConsole in which we are willing to write,
  // otherwise the library will print on the last selected/initialized one
  //Let's start by printing something on the top screen
  consoleSelect(&topScreen);
  printf("This is the top screen. We have lot of space here!\n");
  printf("\x1b[29;15HTop Screen, bottom centered.");

  // SET MAIN LCD
  consoleSelect(&bottomScreen);
  printf("This is the bottom screen. We don't have much space...\nStill better than DS screens :D\n");

  App* app = new App();

  // Main loop
  while (aptMainLoop())
  {
    gspWaitForVBlank();
    hidScanInput();

    // Your code goes here
    // TODO: Check Lid

    // TODO: READ Keys
    // TODO: Start 2D, replace ulib with lib2d or citro3d?

    // TODO: deal events to down
    // TODO: display to down

    u32 kDown = hidKeysDown();

    // TODO: if app.close, end app
    if (kDown & KEY_START)
      break; // break in order to return to hbmenu

    // Example rendering code that displays a white pixel
    // Please note that the 3DS screens are sideways (thus 240x400 and 240x320)
    // u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    // memset(fb, 0, 240*400*3);
    // fb[3*(10+10*240)] = 0xFF;
    // fb[3*(10+10*240)+1] = 0xFF;
    // fb[3*(10+10*240)+2] = 0xFF;

    // Flush and swap framebuffers
    gfxFlushBuffers();
    gfxSwapBuffers();
  }

  gfxExit();
  return 0;
}
