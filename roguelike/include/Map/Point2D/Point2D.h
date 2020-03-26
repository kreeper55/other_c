//
// Created by keeper on 23.06.19.
//

#pragma once

#include <ostream>

using std::ostream;
class Point2D {
 private:
  int _y, _x;

 public:
  Point2D();
  Point2D(int y, int x);

  int getX() const;

  void setX(int x);

  int getY() const;

  void setY(int y);

  bool operator==(const Point2D &rhs) const;

  bool operator!=(const Point2D &rhs) const;

  friend ostream &operator<<(ostream &os, const Point2D &d);

  ~Point2D() = default;
};
