//
// Created by keeper on 25.06.19.
//

#pragma once

#include <BearLibTerminal.h>
#include <map>
#include <string>
#include "Player/PlayerController/PlayerController.h"

class Controls {
 private:
  bool _isQuit = false;
  PlayerController* _playerController;
  std::map<int, std::string> _controlConfig;

 public:
  explicit Controls(PlayerController* playerController);

  void update();

  bool isQuit() const;
  ~Controls() = default;
};
