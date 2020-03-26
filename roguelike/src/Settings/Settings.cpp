//
// Created by keeper on 14.08.19.
//

#include "Settings/Settings.h"

void Settings::update() {
  terminal_set("input.filter=(keybord, mouse+)");
  ifstream fin("../resource/config/config.txt", std::ios_base::in);
  string temp;
  bool vsync, volume, fullsc, save = false, isEnglish = true;
  fin >> temp;
  vsync = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);
  terminal_setf("output.vsync=%s", vsync ? "true" : "false");

  fin >> temp;
  fullsc = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);
  terminal_setf("window: fullscreen=%s", fullsc ? "true" : "false");

  fin >> temp;
  volume = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);

  fin >> temp;
  isEnglish = (temp.substr(temp.find('=') + 1, temp.length()) == "true" ? 1 : 0);
  fin.close();

  int mouse_x = 0, mouse_y = 0, height = 5, width_left = 10, width_right = 34;
  while (true) {
    terminal_clear();
    terminal_printf(width_left, height, L"%ls", language["settings"].c_str());
    terminal_printf(width_left, height + 2, L"[color=orange]1.[/color] %ls : [color=%s]#[/color]",
                    language["vsync"].c_str(), vsync ? "green" : "red");
    terminal_printf(width_left, height + 3, L"[color=orange]2.[/color] %ls : [color=%s]#[/color]",
                    language["volume"].c_str(), volume ? "green" : "red");
    terminal_printf(width_left + 15, height + 3, L"(%ls)", language["doesnt_work"].c_str());
    terminal_printf(width_left, height + 4, L"[color=orange]3.[/color] %ls : [color=%s]#[/color]",
                    language["fullscreen"].c_str(), fullsc ? "green" : "red");
    terminal_printf(width_left, height + 5, L"[color=orange]4.[/color] %s",
                    isEnglish ? "English language" : "Русский язык    ");
    terminal_printf(width_left, height + 15, L"[color=orange]0.[/color] %ls", language["exit_to_menu"].c_str());

    DrawFrame::update(width_left, height + 11, static_cast<int>(language["save_changes"].length()) + 4, 3);
    terminal_printf(width_left + 2, height + 12, L"[color=%s]%ls[/color]", save ? "green" : "orange",
                    language["save_changes"].c_str());
    terminal_refresh();

    int key = terminal_read();

    switch (key) {
      case TK_1: {
        vsync = !vsync;
        save = false;
        break;
      }
      case TK_2: {
        volume = !volume;
        save = false;
        break;
      }
      case TK_3: {
        fullsc = !fullsc;
        save = false;
        break;
      }
      case TK_4: {
        isEnglish = !isEnglish;
        save = false;
        break;
      }
      case TK_ENTER: {
        save = true;
        terminal_refresh();
        std::ofstream fout("../resource/config/config.txt", std::ios_base::out | std::ios_base::trunc);
        fout << "vsync=" << (vsync ? "true" : "false") << "\n";
        fout << "fullscreen=" << (fullsc ? "true" : "false") << "\n";
        fout << "volume=" << (volume ? "true" : "false") << "\n";
        fout << "isEnglish=" << (isEnglish ? "true" : "false") << "\n";
        fout.close();
        terminal_setf("output.vsync=%s", vsync ? "true" : "false");
        terminal_setf("window: fullscreen=%s", fullsc ? "true" : "false");
        setLanguage(isEnglish);
        break;
      }
      case TK_MOUSE_LEFT: {
        mouse_x = terminal_state(TK_MOUSE_X);
        mouse_y = terminal_state(TK_MOUSE_Y);

        if ((mouse_x >= width_left && mouse_x <= width_right) && (mouse_y >= height + 2 && mouse_y <= height + 5)) {
          switch (mouse_y) {
            case 7: {
              vsync = !vsync;
              save = false;
              break;
            }
            case 8: {
              volume = !volume;
              save = false;
              break;
            }
            case 9: {
              fullsc = !fullsc;
              save = false;
              break;
            }
            case 10: {
              isEnglish = !isEnglish;
              save = false;
              break;
            }
            default: {
              break;
            }
          }
        }

        if ((mouse_x >= width_left && mouse_x <= width_right) && (mouse_y >= height + 11 && mouse_y <= height + 13)) {
          save = true;
          terminal_refresh();
          std::ofstream fout("../resource/config/config.txt", std::ios_base::out | std::ios_base::trunc);
          fout << "vsync=" << (vsync ? "true" : "false") << "\n";
          fout << "fullscreen=" << (fullsc ? "true" : "false") << "\n";
          fout << "volume=" << (volume ? "true" : "false") << "\n";
          fout << "isEnglish=" << (isEnglish ? "true" : "false") << "\n";
          fout.close();
          terminal_setf("output.vsync=%s", vsync ? "true" : "false");
          terminal_setf("window: fullscreen=%s", fullsc ? "true" : "false");
          setLanguage(isEnglish);
        }
        break;
      }
      default: {
        break;
      }
    }

    if (key == TK_ESCAPE || key == TK_CLOSE || key == TK_0 ||
        (key == TK_MOUSE_LEFT && (mouse_x >= width_left && mouse_x <= width_right) && (mouse_y == height + 15))) {
      terminal_clear();
      break;
    }
  }
  terminal_set("input: precise-mouse=false, mouse-cursor=true, filter={keyboard}");
}

map<string, wstring> language;

void Settings::setLanguage(bool isEnglish) {
  string lang = isEnglish ? "en" : "ru";
  ifstream fin("../resource/language/" + lang + ".txt", std::ios_base::in);

  string temp = "", key = "";
  wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
  wstring value;

  while (getline(fin, temp)) {
    key = temp.substr(0, temp.find('='));
    value = converter.from_bytes(temp.substr(temp.find('=') + 1, temp.length() - 1));
    language[key] = value;
  }

  fin.close();
}
