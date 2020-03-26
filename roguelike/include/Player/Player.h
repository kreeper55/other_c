//
// Created by keeper on 25.06.19.
//

#pragma once

class Player {
 private:
  int _cash, _step, _health, _max_health, _kills, _protection, _max_protection, _damage;
  bool _have_key;

 public:
  Player()
      : _cash(0),
        _step(0),
        _health(80),
        _max_health(150),
        _kills(0),
        _protection(5),
        _max_protection(75),
        _damage(10),
        _have_key(false) {}

  int getCash() const;
  int getStep() const;
  int getHealth() const;
  int getKills() const;
  int getMaxHealth() const;
  bool isHaveKey() const;

  void incCash();
  void incHealth();
  void incStep();
  void incKills();
  void decHealth();

  void setHaveKey(bool haveKey);
  void setHealth(int health);

  ~Player() = default;
};
