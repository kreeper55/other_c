//
// Created by keeper on 24.06.19.
//

#pragma once

#include <vector>

template<typename type>
using event_type = void (*)(type, type);

template<typename type>
class Event {
 private:
  std::vector<event_type<type> > _vector;

 public:
  Event operator+=(event_type<type> func);

  Event operator-=(event_type<type> func);

  void operator()(const type& value);
};

template<typename type>
Event<type> Event<type>::operator+=(event_type<type> func) {
  for (auto a : _vector) {
    if (func == a) return *this;
  }
  _vector.push_back(func);
  return *this;
}

template<typename type>
Event<type> Event<type>::operator-=(event_type<type> func) {
  for (int i = 0; i < _vector.size(); i++)
    if (func == _vector[i]) {
      for (int j = i; j < _vector.size() - 1; j++) _vector[j] = _vector[j + 1];
      _vector.resize(_vector.size() - 1);
      break;
    }
  return *this;
}

template<typename type>
void Event<type>::operator()(const type& value) {
  for (int i = 0; i < _vector.size(); i++) _vector[i](value);
}
