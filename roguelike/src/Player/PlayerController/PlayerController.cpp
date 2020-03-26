//
// Created by keeper on 25.06.19.
//

#include "Player/PlayerController/PlayerController.h"

void PlayerController::keyPressed(const std::string& route) {
  if (route == "Up") {
    Point2D p_prev(_y, _x);
    Point2D p_next(_y - 1, _x);
    _move[_map->getTile(p_next).getView()](p_prev, p_next);
  } else if (route == "Left") {
    Point2D p_prev(_y, _x);
    Point2D p_next(_y, _x - 1);
    _move[_map->getTile(p_next).getView()](p_prev, p_next);
  } else if (route == "Down") {
    Point2D p_prev(_y, _x);
    Point2D p_next(_y + 1, _x);
    _move[_map->getTile(p_next).getView()](p_prev, p_next);
  } else {
    Point2D p_prev(_y, _x);
    Point2D p_next(_y, _x + 1);
    _move[_map->getTile(p_next).getView()](p_prev, p_next);
  }

  if (_player->getHealth() <= 0) _isGameOver = true;
}

PlayerController::PlayerController(Player* player) : _player(player) {
  _move.insert(make_pair(ObjectType ::_Ground, bind(&PlayerController::_Ground, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Wall, bind(&PlayerController::_Wall, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Cash, bind(&PlayerController::_Cash, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Key, bind(&PlayerController::_Key, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_OpenDoor, bind(&PlayerController::_OpenDoor, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_ClosedDoor, bind(&PlayerController::_ClosedDoor, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Secret, bind(&PlayerController::_Secret, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_FirstAidKit, bind(&PlayerController::_FirstAidKit, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Enemy, bind(&PlayerController::_Enemy, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Player, bind(&PlayerController::_Player, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Quit, bind(&PlayerController::_Quit, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_Entrance, bind(&PlayerController::_Entrance, this, _1, _2)));
  _move.insert(make_pair(ObjectType ::_ClosedEntrance, bind(&PlayerController::_ClosedEntrance, this, _1, _2)));

  _isGameOver = false;
  _isNextLevel = false;
  _isPrevLevel = false;

  _map = new Map(1, 1);
  _y = 0;
  _x = 0;
}

bool PlayerController::isNextLevel() const {
  return _isNextLevel;
}

bool PlayerController::isPrevLevel() const {
  return _isPrevLevel;
}

bool PlayerController::isGameOver() const {
  return _isGameOver;
}

void PlayerController::setIsPrevLevel(bool isPrevLevel) {
  _isPrevLevel = isPrevLevel;
}

void PlayerController::setIsGameOver(bool isGameOver) {
  _isGameOver = isGameOver;
}

void PlayerController::setIsNextLevel(bool isNextLevel) {
  _isNextLevel = isNextLevel;
}

void PlayerController::setMap(Map* map) {
  _map = map;
}

void PlayerController::setLocalQuit() {
  if (_map->getTile(Point2D(_map->getExit().getY(), _map->getExit().getX() + 1)).getView() == ObjectType::_Ground) {
    _x = _map->getExit().getX() + 1;
    _y = _map->getExit().getY();
  } else if (_map->getTile(Point2D(_map->getExit().getY(), _map->getExit().getX() - 1)).getView() ==
             ObjectType::_Ground) {
    _x = _map->getExit().getX() - 1;
    _y = _map->getExit().getY();
  } else if (_map->getTile(Point2D(_map->getExit().getY() + 1, _map->getExit().getX())).getView() ==
             ObjectType::_Ground) {
    _x = _map->getExit().getX();
    _y = _map->getExit().getY() + 1;
  } else {
    _x = _map->getExit().getX();
    _y = _map->getExit().getY() - 1;
  }
  _map->setTile(Point2D(_y, _x), Tile(ObjectType::_Player, ObjectType::_Ground));
  terminal_printf(_x, _y, "[color=purple]@[/color]");
}

void PlayerController::setLocalEntrance() {
  if (_map->getTile(Point2D(_map->getEntrance().getY(), _map->getEntrance().getX() + 1)).getView() ==
      ObjectType::_Ground) {
    _x = _map->getEntrance().getX() + 1;
    _y = _map->getEntrance().getY();
  } else if (_map->getTile(Point2D(_map->getEntrance().getY(), _map->getEntrance().getX() - 1)).getView() ==
             ObjectType::_Ground) {
    _x = _map->getEntrance().getX() - 1;
    _y = _map->getEntrance().getY();
  } else if (_map->getTile(Point2D(_map->getEntrance().getY() + 1, _map->getEntrance().getX())).getView() ==
             ObjectType::_Ground) {
    _x = _map->getEntrance().getX();
    _y = _map->getEntrance().getY() + 1;
  } else {
    _x = _map->getEntrance().getX();
    _y = _map->getEntrance().getY() - 1;
  }
  _map->setTile(Point2D(_y, _x), Tile(ObjectType::_Player, ObjectType::_Ground));
  terminal_printf(_x, _y, "[color=purple]@[/color]");
}

void PlayerController::_Ground(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  _y = p_next.getY();
  _x = p_next.getX();
  _map->render(p_prev, p_next);
}

void PlayerController::_Wall(const Point2D& p_prev, const Point2D& p_next) {}

void PlayerController::_Cash(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  _y = p_next.getY();
  _x = p_next.getX();
  _player->incCash();
  _map->setTile(p_next, Tile(ObjectType::_Ground, ObjectType::_Ground));
  _map->render(p_prev, p_next);
}

void PlayerController::_Key(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  _player->setHaveKey(true);
  _y = p_next.getY();
  _x = p_next.getX();
  _map->setTile(p_next, Tile(ObjectType::_Ground, ObjectType::_Ground));
  _map->render(p_prev, p_next);
}

void PlayerController::_OpenDoor(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  switch (p_prev.getX() - p_next.getX()) {
    case 1: {  // move Left
      _move[_map->getTile(Point2D(p_next.getY(), p_next.getX() - 1)).getView()](
          p_prev, Point2D(p_next.getY(), p_next.getX() - 1));
      break;
    }
    case -1: {  // Right
      _move[_map->getTile(Point2D(p_next.getY(), p_next.getX() + 1)).getView()](
          p_prev, Point2D(p_next.getY(), p_next.getX() + 1));
      break;
    }
    default: {
      break;
    }
  }

  switch (p_prev.getY() - p_next.getY()) {
    case 1: {  // Up
      _move[_map->getTile(Point2D(p_next.getY() - 1, p_next.getX())).getView()](
          p_prev, Point2D(p_next.getY() - 1, p_next.getX()));
      break;
    }
    case -1: {  // Down
      _move[_map->getTile(Point2D(p_next.getY() + 1, p_next.getX())).getView()](
          p_prev, Point2D(p_next.getY() + 1, p_next.getX()));
      break;
    }
    default: {
      break;
    }
  }
}

void PlayerController::_ClosedDoor(const Point2D& p_prev, const Point2D& p_next) {
  if (_player->isHaveKey()) {
    _player->incStep();
    _player->setHaveKey(false);
    _map->setTile(p_next, Tile(ObjectType::_OpenDoor, ObjectType::_Ground));
    terminal_printf(p_next.getX(), p_next.getY(), "[color=orange]%c[/color]", ObjectType::_OpenDoor);
  }
}

void PlayerController::_Secret(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  _map->setTile(p_next, Tile(ObjectType::_Enemy, ObjectType::_Ground));
  terminal_printf(p_next.getX(), p_next.getY(), "[color=red]%c[/color]", ObjectType::_Enemy);
}

void PlayerController::_FirstAidKit(const Point2D& p_prev, const Point2D& p_next) {
  if (_player->getHealth() != _player->getMaxHealth()) {
    _player->incStep();
    _player->setHealth(9);
    _y = p_next.getY();
    _x = p_next.getX();
    _map->setTile(p_next, Tile(ObjectType::_Ground, ObjectType::_Ground));
    _map->render(p_prev, p_next);
  }
}

void PlayerController::_Enemy(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  _player->decHealth();
  _player->incKills();
  if (_player->getHealth() <= 0) _isGameOver = true;
  _map->setTile(p_next, Tile(ObjectType::_Cash, ObjectType::_Ground));
  terminal_printf(p_next.getX(), p_next.getY(), "[color=green]%c[/color]", ObjectType::_Cash);
}

void PlayerController::_Player(const Point2D& p_prev, const Point2D& p_next) {}

void PlayerController::_Quit(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  _isNextLevel = true;
  _map->setTile(p_prev, Tile(ObjectType::_Ground, ObjectType::_Ground));
}

void PlayerController::_Entrance(const Point2D& p_prev, const Point2D& p_next) {
  _player->incStep();
  _isPrevLevel = true;
  _map->setTile(p_prev, Tile(ObjectType::_Ground, ObjectType::_Ground));
}

void PlayerController::_ClosedEntrance(const Point2D& p1, const Point2D& p2) {}

PlayerController::~PlayerController() {
  _move.clear();
  delete _player;
  delete _map;
}
