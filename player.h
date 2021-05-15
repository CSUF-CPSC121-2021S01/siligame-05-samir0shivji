#ifndef PLAYER_H
#define PLAYER_H
#include <fstream>
#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  Player() : GameElement() {}
  void Move(const graphics::Image& image) override;
  void Draw(graphics::Image& Can) override {
    Can.DrawLine(25 + x_, 11 + y_, 40 + x_, 35 + y_, 0, 0, 0, 1);
    Can.DrawLine(40 + x_, 35 + y_, 25 + x_, 29 + y_, 0, 0, 0, 1);
    Can.DrawLine(25 + x_, 29 + y_, 10 + x_, 35 + y_, 0, 0, 0, 1);
    Can.DrawLine(10 + x_, 35 + y_, 25 + x_, 11 + y_, 0, 0, 0, 1);
    Can.DrawLine(25 + x_, 11 + y_, 25 + x_, 29 + y_, 0, 0, 0, 1);
    Can.DrawLine(30 + x_, 31 + y_, 26 + x_, 37 + y_, 0, 0, 0, 1);
    Can.DrawLine(21 + x_, 31 + y_, 25 + x_, 37 + y_, 0, 0, 0, 1);
  }
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  PlayerProjectile() : GameElement(0, 0, 5, 5) {}
  void Move(const graphics::Image& image) override;
  void Draw(graphics::Image& Can) override {
    Can.DrawCircle(2 + x_, 2 + y_, 1, 255, 200, 150);
  }
};
#endif
