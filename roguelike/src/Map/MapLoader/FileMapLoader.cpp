//
// Created by keeper on 23.06.19.
//

#include "Map/MapLoader/FileMapLoader.h"

FileMapLoader* FileMapLoader::_p_instance = nullptr;

Data* FileMapLoader::mapLoader(const string& filename) {
  ifstream fin("../resource/maps/" + filename);
  if (!fin.is_open()) throw invalid_argument("Could not open file");

  Data* data = new Data;

  fin >> data->column;
  fin >> data->row;

  char buff = ' ';
  data->vect.resize(data->row);

  for (size_t i = 0; i < data->row; i++) {
    data->vect[i].resize(data->column);
    if (fin.eof()) break;
    for (size_t j = 0; j < data->column; j++) {
      fin >> buff;
      data->vect[i][j] = buff;
    }
  }

  fin.close();
  return data;
}

FileMapLoader::~FileMapLoader() {
  delete _p_instance;
}
