//
// Created by keeper on 23.06.19.
//

#include "Map/Map.h"
#include <iostream>

Map::Map(size_t column, size_t row) : _column(column), _row(row) {
  _arr.resize(_row);
  for (size_t i = 0; i < _row; i++) {
    _arr[i].resize(_column);
  }
}

Map::Map(const Map& map) : _column(map._column), _row(map._row) {
  _arr.resize(_row);
  for (size_t i = 0; i < _row; i++) {
    _arr[i].resize(_column);
    for (size_t j = 0; j < _column; j++) {
      switch (map._arr[i][j].getView()) {
        case _Wall: {
          _arr[i][j] = map._arr[i][j];
          break;
        }
        case _Entrance: {
          _entrance = Point2D(i, j);
          _arr[i][j] = map._arr[i][j];
          break;
        }
        case _ClosedEntrance: {
          _entrance = Point2D(i, j);
          _arr[i][j] = map._arr[i][j];
          break;
        }
        case _Quit: {
          _exit = Point2D(i, j);
          _arr[i][j] = map._arr[i][j];
          break;
        }
        default: {
          _arr[i][j] = map._arr[i][j];
          break;
        }
      }
    }
  }
}

Map& Map::operator=(const Map& map) {
  if (this == &map) return *this;
  _column = map._column;
  _row = map._row;
  _arr.resize(_row);
  for (size_t i = 0; i < _row; i++) {
    _arr[i].resize(_column);
    for (size_t j = 0; j < _column; j++) {
      switch (map._arr[i][j].getView()) {
        case _Wall: {
          _arr[i][j] = map._arr[i][j];
          break;
        }
        case _Entrance: {
          _entrance = Point2D(i, j);
          _arr[i][j] = map._arr[i][j];
          break;
        }
        case _ClosedEntrance: {
          _entrance = Point2D(i, j);
          _arr[i][j] = map._arr[i][j];
          break;
        }
        case _Quit: {
          _exit = Point2D(i, j);
          _arr[i][j] = map._arr[i][j];
          break;
        }
        default: {
          _arr[i][j] = map._arr[i][j];
          break;
        }
      }
    }
  }
  return *this;
}

Map::Map(Data* data) : _column(data->column), _row(data->row) {
  _arr.resize(data->row);
  for (size_t i = 0; i < data->row; i++) {
    _arr[i].resize(data->column);
    for (size_t j = 0; j < data->column; j++) {
      switch (data->vect[i][j]) {
        case _Wall: {
          _arr[i][j] = Tile(data->vect[i][j], _Ground);
          break;
        }
        case _Entrance: {
          _entrance = Point2D(i, j);
          _arr[i][j] = Tile(data->vect[i][j], _Entrance);
          break;
        }
        case _ClosedEntrance: {
          _entrance = Point2D(i, j);
          _arr[i][j] = Tile(data->vect[i][j], _ClosedEntrance);
          break;
        }
        case _Quit: {
          _exit = Point2D(i, j);
          _arr[i][j] = Tile(data->vect[i][j], _Quit);
          break;
        }
        default: {
          _arr[i][j] = Tile(data->vect[i][j], _Ground);
          break;
        }
      }
    }
  }
  delete data;
}

size_t Map::getColumn() const {
  return _column;
}

void Map::setColumn(size_t column) {
  Map::_column = column;
}

size_t Map::getRow() const {
  return _row;
}

void Map::setRow(size_t row) {
  Map::_row = row;
}

Tile Map::getTile(const Point2D point) const {
  if (point.getY() >= static_cast<int>(_row) || point.getY() < 0 || point.getX() >= static_cast<int>(_column) ||
      point.getX() < 0) {
    throw std::invalid_argument("index out of range - getChar");  // throw except
  }
  return _arr[point.getY()][point.getX()];
}

void Map::setTile(const Point2D point, const Tile& tile) {
  if (point.getY() >= static_cast<int>(_row) || point.getY() < 0 || point.getX() >= static_cast<int>(_column) ||
      point.getX() < 0) {
    throw std::invalid_argument("index out of range - setChar");  // throw except
  }
  _arr[point.getY()][point.getX()] = tile;
}

//  By name: grey (or gray), red, flame, orange, amber, yellow, lime, chartreuse, green, sea, turquoise, cyan, sky,
//  azure, blue, han, violet, purple, fuchsia, magenta, pink, crimson, transparent.
void Map::render() {
  for (size_t i = 0; i < _row; i++) {
    for (size_t j = 0; j < _column; j++) {
      switch (_arr[i][j].getView()) {
        case _Ground: {
          terminal_printf(j, i, "[color=transparent]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _Wall: {
          terminal_printf(j, i, "[color=blue]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _Cash: {
          terminal_printf(j, i, "[color=green]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _Enemy: {
          terminal_printf(j, i, "[color=red]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _Quit: {
          terminal_printf(j, i, "[color=white]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _Entrance: {
          terminal_printf(j, i, "[color=white]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _ClosedEntrance: {
          terminal_printf(j, i, "[color=white]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _Player: {
          terminal_printf(j, i, "[color=purple]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _FirstAidKit: {
          terminal_printf(j, i, "[color=fuchsia]%c[/color]", _arr[i][j].getView());
          break;
        }
        case _Secret: {
          terminal_printf(j, i, "[color=azure]%c[/color]", _arr[i][j].getView());
          break;
        }
        default: {
          terminal_printf(j, i, "[color=amber]%c[/color]", _arr[i][j].getView());
          break;
        }
      }
    }
  }
}

void Map::render(const Point2D p1, const Point2D p2) {
  char tile = _arr[p1.getY()][p1.getX()].getView();
  _arr[p1.getY()][p1.getX()].setView(_arr[p2.getY()][p2.getX()].getView());
  _arr[p2.getY()][p2.getX()].setView(tile);
  terminal_printf(p1.getX(), p1.getY(), "[color=transparent]%c[/color]", _arr[p1.getY()][p1.getX()].getView());
  terminal_printf(p2.getX(), p2.getY(), "[color=purple]%c[/color]", _arr[p2.getY()][p2.getX()].getView());
}

const Point2D& Map::getEntrance() const {
  return _entrance;
}

void Map::setEntrance(const Point2D& entrance) {
  _entrance = entrance;
}

const Point2D& Map::getExit() const {
  return _exit;
}

void Map::setExit(const Point2D& exit) {
  _exit = exit;
}
