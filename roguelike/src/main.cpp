#include <Game/Game.h>
#include <Settings/Settings.h>
#include <locale>
#include <vector>

using std::string;
using std::vector;
using std::wstring;

struct Function {
  wstring name;
  void (*func)();
};

vector<Function> entries;

auto reset = []() {
  ifstream fin("../resource/config/config.txt", std::ios_base::in);
  string temp;
  bool vsync, fullsc, volume, isEnglish;
  fin >> temp;
  vsync = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);

  fin >> temp;
  fullsc = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);

  fin >> temp;
  volume = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);
  volume = !volume;

  fin >> temp;
  isEnglish = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);
  fin.close();

  Settings::setLanguage(isEnglish);
  entries[0].name = language["new_game"];
  entries[1].name = language["load_game"];
  entries[2].name = language["high_scores"];
  entries[3].name = language["settings"];
  entries[4].name = language["quit"];

  terminal_color("white");
  terminal_setf("window: title=keeper's game, minimum-size=100x30, size=120x35, cellsize=auto, fullscreen=%s;",
                fullsc ? "true" : "false");
  terminal_setf("output.vsync=%s", vsync ? "true" : "false");
  terminal_set("font: ../Media/UbuntuMono-R.ttf, size=10x20;");
  terminal_set("input.filter={keyboard, mouse+}");
};

static void quit() {
  terminal_clear();
  terminal_printf(10, 2, L"%ls", language["quit"].c_str());
  terminal_refresh();
  terminal_delay(500);
  terminal_close();
}

int main() {
  setlocale(LC_ALL, "rus");
  terminal_open();
  terminal_refresh();

  entries = {{}, {}, {}, {}, {}};
  entries[0].func = Game::run;
  entries[1].func = Game::load;
  entries[2].func = Game::highscores;
  entries[3].func = Settings::update;
  entries[4].func = quit;
  reset();

  int key = 0;
  int mouse_x = 0, mouse_y = 0, height = 5, width_left = 3, width_right = 20;
  size_t i = 0;
  while (true) {
    terminal_clear();
    for (i = 0; i < entries.size(); i++) {
      terminal_printf(width_left, i + height, L"[color=red]%d[/color]. %ls", i + 1, entries[i].name.c_str());
    }
    terminal_refresh();

    key = terminal_read();

    if (key >= TK_1 && key <= TK_5) {
      terminal_set("input: precise-mouse=false, mouse-cursor=true, filter={keyboard}");
      entries[key - TK_1].func();
      reset();
    } else if (key == TK_MOUSE_LEFT) {
      mouse_x = terminal_state(TK_MOUSE_X);
      mouse_y = terminal_state(TK_MOUSE_Y);
      if ((mouse_x >= width_left && mouse_x <= width_right) &&
          (mouse_y >= height && mouse_y <= static_cast<int>(height + entries.size()))) {
        terminal_set("input: precise-mouse=false, mouse-cursor=true, filter={keyboard}");
        entries[mouse_y - height].func();
        reset();
      }
    }

    if (key == TK_ESCAPE || key == TK_CLOSE) {
      quit();
      break;
    }
  }
  return 0;
}
