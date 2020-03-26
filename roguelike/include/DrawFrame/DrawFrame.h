//
// Created by keeper on 14.08.19.
//

#pragma once
#include <BearLibTerminal.h>

class DrawFrame {
 public:
  static void update(int x, int y, int w, int h) {
    terminal_clear_area(x, y, w, h);

    for (int i = x; i < x + w; i++) {
      terminal_put(i, y, L'─');
      terminal_put(i, y + h - 1, L'─');
    }

    for (int j = y; j < y + h; j++) {
      terminal_put(x, j, L'│');
      terminal_put(x + w - 1, j, L'│');
    }

    terminal_put(x, y, L'┌');
    terminal_put(x + w - 1, y, L'┐');
    terminal_put(x, y + h - 1, L'└');
    terminal_put(x + w - 1, y + h - 1, L'┘');
  }
};
