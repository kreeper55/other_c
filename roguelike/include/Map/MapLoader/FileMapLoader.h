//
// Created by keeper on 23.06.19.
//

#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "IMapLoader.h"

class FileMapLoader : public IMapLoader {
 private:
  static FileMapLoader* _p_instance;
  FileMapLoader() = default;
  FileMapLoader(const FileMapLoader& fileMapLoader) {}

 public:
  static FileMapLoader* getFileMapLoader() {
    if (!_p_instance) _p_instance = new FileMapLoader();
    return _p_instance;
  }

  Data* mapLoader(const string& filename) override;
  virtual ~FileMapLoader();
};
