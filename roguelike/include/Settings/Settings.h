//
// Created by keeper on 14.08.19.
//

#pragma once

#include <codecvt>
#include <fstream>
#include <locale>
#include "DrawFrame/DrawFrame.h"
#include "Language.h"

using std::codecvt_utf8_utf16;
using std::ifstream;
using std::wstring_convert;

class Settings {
 public:
  static void update();
  static void setLanguage(bool isEnglish);
};
