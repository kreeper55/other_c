//
// Created by keeper on 23.06.19.
//

// #include "../../../include/Map/Tile/Tile.h"
#include "Map/Tile/Tile.h"

char Tile::getView() const {
  return _view;
}

void Tile::setView(char view) {
  _view = view;
}

char Tile::getBaseView() const {
  return _baseView;
}

void Tile::setBaseView(char baseView) {
  _baseView = baseView;
}

Tile::Tile(char view, char baseView) : _view(view), _baseView(baseView) {}
