//
// Created by keeper on 09.07.19.
//

#pragma once
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <list>
#include "Controls/Controls.h"
#include "DrawFrame/DrawFrame.h"
#include "Map/MapLoader/FileMapLoader.h"
#include "Player/PlayerController/PlayerController.h"
#include "Settings/Language.h"

class Game {
 private:
  static void renderLegend();
  static void renderPlayerInfo(const Player& player, uint64_t fps);
  static void gameOver(const Player& player);
  static void win(const Player& player);
  static void prevLevel();
  static void nextLevel();
  static void quit();

 public:
  static void run();
  static void load();
  static void highscores();
};
