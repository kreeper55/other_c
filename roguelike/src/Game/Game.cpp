//
// Created by keeper on 09.07.19.
//

#include "Game/Game.h"

uint64_t getTime() {
  timeval t{};
  gettimeofday(&t, nullptr);
  return t.tv_sec * 1000 + t.tv_usec / 1000;
}

void Game::run() {
  terminal_clear();
  FileMapLoader* fileMapLoader = FileMapLoader::getFileMapLoader();
  Map start(fileMapLoader->mapLoader("start.txt"));
  Map map1(fileMapLoader->mapLoader("dungeon.txt"));
  Map map2(fileMapLoader->mapLoader("flower.txt"));
  Map finish(fileMapLoader->mapLoader("pika.txt"));
  std::vector<Map> levels = {start, finish, map2, finish};

  auto* player = new Player();
  auto* playerController = new PlayerController(player);
  Controls controls(playerController);

  uint64_t fps_update_time = getTime();
  int fps_counter = 0;
  int fps_value = 0;

  for (size_t i = 0; i < levels.size();) {
    playerController->setMap(&levels[i]);
    if (playerController->isPrevLevel()) {
      playerController->setIsPrevLevel(false);
      playerController->setLocalQuit();
    } else {
      playerController->setLocalEntrance();
    }

    levels[i].render();
    renderLegend();
    terminal_refresh();

    while ((!controls.isQuit()) && (!playerController->isGameOver()) && (!playerController->isNextLevel()) &&
           (!playerController->isPrevLevel())) {
      controls.update();
      renderPlayerInfo(*player, fps_value);
      terminal_refresh();

      fps_counter += 1;
      uint64_t time = getTime();
      if (time > fps_update_time + 1000) {
        fps_value = fps_counter;
        fps_counter = 0;
        fps_update_time = time;
      }
    }

    if (playerController->isGameOver()) {
      playerController->setIsGameOver(false);
      Game::gameOver(*player);
      break;
    } else if (playerController->isNextLevel()) {
      if (i == levels.size() - 1) {
        Game::win(*player);
        break;
      } else {
        playerController->setIsNextLevel(false);
        Game::nextLevel();
        i++;
      }
    } else if (playerController->isPrevLevel()) {
      if (i != 0) {
        i--;
        Game::prevLevel();
      }
    } else {
      Game::quit();
      break;
    }
  }
}

void Game::load() {
  std::cout << "load //zaglushka//" << std::endl;
}

void Game::highscores() {
  terminal_set("input.filter=(keybord, mouse+)");
  terminal_clear();
  terminal_refresh();

  ifstream fin("../resource/config/records.txt", std::ios_base::in);
  if (!fin.is_open()) throw invalid_argument("Could not open file");

  int count = 0, key = 0, mouse_x = 0, mouse_y = 0, index = 0, index2 = 0, width_left = 1, width_right = 16, height = 2;
  map<int, string> records;
  std::list<int> sequence;
  string str, temp;

  while (!fin.eof()) {
    getline(fin, str);
    if (str.empty()) break;
    index = str.find(" steps");
    index2 = str.rfind(' ', index - 1);
    temp = str.substr(index2 + 1, index - index2 - 1);
    sequence.push_back(std::stoi(temp));
    records.insert(make_pair(std::stoi(temp), str));
    count++;
  }
  fin.close();

  sequence.sort();
  count = count > 25 ? 25 : count;
  for (int i = 1; i < count + 1; i++) {
    switch (i) {
      case 1: {
        terminal_printf(i < 10 ? width_left + 1 : width_left, i + height,
                        "[color=red]%d -> [/color][color=crimson]%s[/color]", i, records[sequence.front()].c_str());
        break;
      }
      case 2: {
        terminal_printf(i < 10 ? width_left + 1 : width_left, i + height,
                        "[color=flame]%d -> [/color][color=magenta]%s[/color]", i, records[sequence.front()].c_str());
        break;
      }
      case 3: {
        terminal_printf(i < 10 ? width_left + 1 : width_left, i + height,
                        "[color=orange]%d -> [/color][color=purple]%s[/color]", i, records[sequence.front()].c_str());
        break;
      }
      default: {
        terminal_printf(i < 10 ? width_left + 1 : width_left, i + height,
                        "[color=amber]%d -> [/color][color=white]%s[/color]", i, records[sequence.front()].c_str());
        break;
      }
    }
    sequence.pop_front();
  }
  records.clear();
  sequence.clear();

  terminal_printf(width_left + 1, height - 1, L"[color=lime]%ls[/color]", language["high_scores_table"].c_str());
  terminal_printf(width_left + 6, height, L"%ls", language["nickname"].c_str());
  terminal_printf(width_left + 30, height, L"%ls", language["steps"].c_str());
  terminal_printf(width_left + 53, height, L"%ls", language["cash"].c_str());
  terminal_printf(width_left + 77, height, L"%ls", language["kills"].c_str());
  terminal_printf(width_left + 0, height + 27, L"[color=orange]0.[/color] %ls", language["exit_to_menu"].c_str());
  terminal_refresh();

  while (true) {
    key = terminal_read();
    mouse_x = terminal_state(TK_MOUSE_X);
    mouse_y = terminal_state(TK_MOUSE_Y);
    if (key == TK_ESCAPE || key == TK_CLOSE || key == TK_0 ||
        (key == TK_MOUSE_LEFT && (mouse_x >= width_left && mouse_x <= width_right) && (mouse_y == height + 27))) {
      Game::quit();
      break;
    }
  }
  terminal_set("input: precise-mouse=false, mouse-cursor=true, filter={keyboard}");
}

void Game::renderLegend() {
  terminal_printf(92, 8, L"[color=orange]%ls[/color]", language["legend"].c_str());
  terminal_printf(92, 10, L"[back[color=white]%c %ls[/color]", _Ground, language["ground"].c_str());
  terminal_printf(92, 12, L"[color=blue]%c %ls[/color]", _Wall, language["wall"].c_str());
  terminal_printf(92, 14, L"[color=green]%c %ls[/color]", _Cash, language["cash"].c_str());
  terminal_printf(92, 16, L"[color=red]%c %ls[/color]", _Enemy, language["enemy"].c_str());
  terminal_printf(92, 18, L"[color=white]%c %ls[/color]", _Entrance, language["entrance_zone"].c_str());
  terminal_printf(92, 19, L"[color=white]%c %ls[/color]", _Quit, language["exit_zone"].c_str());
  terminal_printf(92, 21, L"[color=purple]%c %ls[/color]", _Player, language["player"].c_str());
  terminal_printf(92, 23, L"[color=fuchsia]%c %ls[/color]", _FirstAidKit, language["first_aid_kit"].c_str());
  terminal_printf(92, 25, L"[color=azure]%c %ls[/color]", _Secret, language["secret"].c_str());
  terminal_printf(92, 27, L"[color=amber]%c %ls[/color]", _OpenDoor, language["open_door"].c_str());
  terminal_printf(92, 28, L"[color=amber]%c %ls(doesn't work)[/color]", _ClosedDoor, language["close_door"].c_str());
  terminal_printf(92, 29, L"[color=amber]%c %ls(doesn't work)[/color]", _Key, language["key"].c_str());

  terminal_printf(1, 33, "[color=white]%ls[/color]", language["controls_button"].c_str());
}

void Game::renderPlayerInfo(const Player& player, uint64_t fps_value) {
  terminal_printf(92, 0, L"[color=orange]%ls[/color]", language["player_info"].c_str());
  terminal_printf(92, 1, L"%ls : [color=sky]%d[/color] ", language["cash"].c_str(), player.getCash());
  terminal_printf(92, 2, L"%ls : [color=sky]%d / %d[/color] ", language["health"].c_str(), player.getHealth(),
                  player.getMaxHealth());
  terminal_printf(92, 3, L"%ls : [color=sky]%d[/color] ", language["kills"].c_str(), player.getKills());
  terminal_printf(92, 4, L"%ls : [color=sky]%s[/color] ", language["key"].c_str(), player.isHaveKey() ? "%" : "-");
  terminal_printf(1, 31, L"%ls : [color=sky]%d[/color] ", language["steps"].c_str(), player.getStep());
  terminal_printf(1, 32, "FPS: [color=%s]%d[/color]", fps_value < 50 ? "orange" : "green", fps_value);
}

void Game::gameOver(const Player& player) {
  terminal_clear();
  terminal_set("U+E000: ../Media/pikachulose.png");
  terminal_put(25, 0, 0xE000);
  terminal_printf(5, 2, L"%ls", language["you_died"].c_str());
  terminal_printf(5, 3, L"%ls", language["in_this_game"].c_str());
  terminal_printf(5, 4, L"%ls : %d", language["steps"].c_str(), player.getStep());
  terminal_printf(5, 5, L"%ls : %d", language["cash_collected"].c_str(), player.getCash());
  terminal_printf(5, 6, L"%ls : %d", language["kills"].c_str(), player.getKills());
  terminal_printf(5, 10, L"%ls", language["enter_for_continue"].c_str());
  terminal_refresh();
  for (int key = 0; key != TK_ENTER; key = terminal_read()) continue;
  terminal_set("U+E000: none");
}

void Game::win(const Player& player) {
  const int maxChars = 16;
  int key = 0, temp, j = 0, length = 0;
  char* buffer = new char[maxChars + 1]{0};

  terminal_clear();
  terminal_set("U+E000: ../Media/pikachuwin.png");
  terminal_put(0, 0, 0xE000);
  terminal_printf(5, 2, L"%ls", language["you_win"].c_str());
  terminal_printf(5, 3, L"%ls", language["in_this_game"].c_str());
  terminal_printf(5, 4, L"%ls : %d", language["steps"].c_str(), player.getStep());
  terminal_printf(5, 5, L"%ls : %d", language["cash"].c_str(), player.getCash());
  terminal_printf(5, 6, L"%ls : %d", language["kills"].c_str(), player.getKills());
  terminal_printf(5, 10, L"%ls &", language["enter_name"].c_str());
  terminal_printf(5, 11, L"%ls", language["enter_for_continue"].c_str());

  terminal_color("white");
  DrawFrame::update(5, 12, maxChars + 2, 3);
  terminal_printf(6, 13, "%s", buffer);
  terminal_refresh();

  while (true) {
    key = terminal_read();

    if (key == TK_CLOSE || key == TK_ESCAPE) {
      break;
    }

    if (key == TK_ENTER && (length >= 3)) {
      std::ofstream fout("../resource/config/records.txt", std::ios_base::app);
      fout << buffer;
      for (int i = 0; i < (maxChars - length + 1); i++) {
        fout << ' ';
      }

      fout << "player took : " << player.getStep() << " steps";
      temp = player.getStep();
      for (j = 0; temp != 0; j++) {
        temp /= 10;
      }
      for (int i = 0; i < (5 - j); i++) {
        fout << ' ';
      }

      fout << "cash collected : " << player.getCash();
      temp = player.getCash();
      for (j = 0; temp != 0; j++) {
        temp /= 10;
      }
      for (int i = 0; i < (5 - j); i++) {
        fout << ' ';
      }

      fout << "player killed : " << player.getKills() << " opponents" << std::endl;
      fout.close();
      break;
    } else {
      terminal_color("orange");
      DrawFrame::update(5, 12, maxChars + 2, 3);
      length = terminal_read_str(6, 13, buffer, maxChars);

      terminal_color("white");
      DrawFrame::update(5, 12, maxChars + 2, 3);
      terminal_printf(6, 13, "%s", buffer);
    }
    terminal_refresh();
  }
  terminal_color("white");
  terminal_set("U+E000: none");
}

void Game::prevLevel() {
  terminal_clear();
}

void Game::nextLevel() {
  terminal_clear();
}

void Game::quit() {
  terminal_clear();
  terminal_refresh();
}
