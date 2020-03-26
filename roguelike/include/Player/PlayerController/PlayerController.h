//
// Created by keeper on 25.06.19.
//

#pragma once

#include <functional>
#include <map>
#include <string>
#include "Map/Map.h"
#include "Player/Player.h"

using std::bind;
using std::function;
using std::make_pair;
using std::map;
using std::string;
using std::placeholders::_1;
using std::placeholders::_2;

class PlayerController {
 private:
  int _y, _x;
  bool _isGameOver, _isNextLevel, _isPrevLevel;
  Player* _player;
  Map* _map;
  map<char, function<void(Point2D, Point2D)> > _move;

  void _Ground(const Point2D& p1, const Point2D& p2);
  void _Wall(const Point2D& p1, const Point2D& p2);
  void _Cash(const Point2D& p1, const Point2D& p2);
  void _Key(const Point2D& p1, const Point2D& p2);
  void _OpenDoor(const Point2D& p1, const Point2D& p2);
  void _ClosedDoor(const Point2D& p1, const Point2D& p2);
  void _Secret(const Point2D& p1, const Point2D& p2);
  void _FirstAidKit(const Point2D& p1, const Point2D& p2);
  void _Enemy(const Point2D& p1, const Point2D& p2);
  void _Player(const Point2D& p1, const Point2D& p2);
  void _Quit(const Point2D& p1, const Point2D& p2);
  void _Entrance(const Point2D& p1, const Point2D& p2);
  void _ClosedEntrance(const Point2D& p1, const Point2D& p2);

 public:
  explicit PlayerController(Player* player);

  void keyPressed(const std::string& key);

  bool isGameOver() const;
  bool isNextLevel() const;
  bool isPrevLevel() const;

  void setMap(Map* map);
  void setLocalQuit();
  void setLocalEntrance();

  void setIsPrevLevel(bool isPrevLevel);
  void setIsGameOver(bool isGameOver);
  void setIsNextLevel(bool isNextLevel);

  virtual ~PlayerController();
};
