//
// Created by keeper on 23.06.19.
//

#pragma once

enum ObjectType {
  _Ground = '.',
  _Wall = '#',
  _Cash = '$',
  _Key = '%',
  _OpenDoor = '/',
  _ClosedDoor = '|',
  _Secret = '?',
  _FirstAidKit = '+',
  _Enemy = 'E',
  _Player = '@',
  _Quit = '>',
  _Entrance = '<' ,
  _ClosedEntrance = 'X'
};

class Tile {
 private:
  char _view;
  char _baseView;

 public:
  Tile() = default;
  Tile(char view, char baseView);

  char getView() const;

  void setView(char view);

  char getBaseView() const;

  void setBaseView(char baseView);
  //  void render();
  ~Tile() = default;
};

// class TilePlayer : public Tile {};
