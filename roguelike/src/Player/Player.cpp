//
// Created by keeper on 25.06.19.
//

#include "Player/Player.h"

int Player::getCash() const {
  return _cash;
}

void Player::incCash() {
  _cash++;
}

int Player::getStep() const {
  return _step;
}

void Player::incStep() {
  _step++;
}

int Player::getHealth() const {
  return _health;
}

void Player::decHealth() {
  _health -= 10;
}

void Player::incHealth() {
  _health += 8;
}

void Player::incKills() {
  _kills++;
}

int Player::getKills() const {
  return _kills;
}

bool Player::isHaveKey() const {
  return _have_key;
}

void Player::setHaveKey(bool haveKey) {
  _have_key = haveKey;
}

int Player::getMaxHealth() const {
  return _max_health;
}

void Player::setHealth(int health) {
  if ((_health + health) <= _max_health)
    _health += health;
  else
    _health = _max_health;
}
