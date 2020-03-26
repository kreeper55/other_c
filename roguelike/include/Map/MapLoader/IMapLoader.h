//
// Created by keeper on 16.07.19.
//

#pragma once

#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;
using std::invalid_argument;

struct Data {
  size_t column, row;
  vector<vector<char> > vect;

  Data() : column(0), row(0) {}
  ~Data() = default;
};

class IMapLoader {
 public:
  virtual Data* mapLoader(const std::string& filename) = 0;
};
