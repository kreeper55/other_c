//
// Created by keeper on 25.06.19.
//

#include "Controls/Controls.h"

Controls::Controls(PlayerController* playerController) : _playerController(playerController) {
  _controlConfig[TK_W] = "Up";
  _controlConfig[TK_A] = "Left";
  _controlConfig[TK_S] = "Down";
  _controlConfig[TK_D] = "Right";
}

void Controls::update() {
  while (terminal_has_input()) {
    int event = terminal_read();
    if (event == TK_ESCAPE || event == TK_CLOSE) {
      _isQuit = true;

    } else if (event == TK_W || event == TK_A || event == TK_S || event == TK_D) {
      _playerController->keyPressed(_controlConfig.at(event));
    }
  }
}

bool Controls::isQuit() const {
  return _isQuit;
}
