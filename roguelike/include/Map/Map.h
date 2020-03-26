//
// Created by keeper on 23.06.19.
//

#pragma once

#include <vector>
#include "BearLibTerminal.h"
#include "Map/MapLoader/IMapLoader.h"
#include "Point2D/Point2D.h"
#include "Tile/Tile.h"

using std::vector;

class Map {
 private:
  size_t _column, _row;
  Point2D _entrance, _exit;
  vector<vector<Tile>> _arr;

 public:
  Map(size_t column, size_t row);
  Map(const Map& map);
  explicit Map(Data* data);

  Map& operator=(const Map& map);

  Tile getTile(Point2D point) const;
  void setTile(Point2D point, const Tile& tile);

  void render();
  void render(Point2D p1, Point2D p2);

  size_t getColumn() const;
  void setColumn(size_t column);

  size_t getRow() const;
  void setRow(size_t row);

  const Point2D& getEntrance() const;
  void setEntrance(const Point2D& entrance);
  const Point2D& getExit() const;
  void setExit(const Point2D& exit);

  virtual ~Map() = default;
};
