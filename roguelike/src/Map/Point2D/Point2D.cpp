//
// Created by keeper on 23.06.19.
//

#include "Map/Point2D/Point2D.h"

Point2D::Point2D(int y, int x) : _y(y), _x(x) {}

int Point2D::getX() const {
  return _x;
}

void Point2D::setX(int x) {
  Point2D::_x = x;
}

int Point2D::getY() const {
  return _y;
}

void Point2D::setY(int y) {
  Point2D::_y = y;
}

bool Point2D::operator==(const Point2D &rhs) const {
  return _x == rhs._x && _y == rhs._y;
}

bool Point2D::operator!=(const Point2D &rhs) const {
  return !(rhs == *this);
}

ostream &operator<<(ostream &os, const Point2D &d) {
  os << "y: " << d._y << " x: " << d._x;
  return os;
}

Point2D::Point2D() {
  _y = 0;
  _x = 0;
}
