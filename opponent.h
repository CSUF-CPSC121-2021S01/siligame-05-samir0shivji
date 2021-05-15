#ifndef OPPONENT_H
#define OPPONENT_H
#include <fstream>
#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#include "game_element.h"

// Opponent Projectile
class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  OpponentProjectile() : GameElement(0, 0, 5, 5) {}
  void Move(const graphics::Image& image) override;
  void Draw(graphics::Image& Can) override {
    Can.DrawCircle(2 + x_, 2 + y_, 1, 150, 200, 255);
  }
};

class Opponent : public GameElement {
 public:
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  Opponent() : GameElement(0, 0, 50, 50) {}
  void Move(const graphics::Image& Image) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();
  void Draw(graphics::Image& Can) override {
    Can.DrawLine(11 + x_, 20 + y_, 31 + x_, 12 + y_, 0, 0, 0, 1);
    Can.DrawLine(31 + x_, 12 + y_, 36 + x_, 21 + y_, 0, 0, 0, 1);
    Can.DrawLine(36 + x_, 21 + y_, 40 + x_, 24 + y_, 0, 0, 0, 1);
    Can.DrawLine(40 + x_, 24 + y_, 37 + x_, 33 + y_, 0, 0, 0, 1);
    Can.DrawLine(37 + x_, 33 + y_, 39 + x_, 37 + y_, 0, 0, 0, 1);
    Can.DrawLine(39 + x_, 37 + y_, 27 + x_, 34 + y_, 0, 0, 0, 1);
    Can.DrawLine(27 + x_, 34 + y_, 21 + x_, 38 + y_, 0, 0, 0, 1);
    Can.DrawLine(21 + x_, 38 + y_, 15 + x_, 29 + y_, 0, 0, 0, 1);
    Can.DrawLine(15 + x_, 29 + y_, 16 + x_, 26 + y_, 0, 0, 0, 1);
    Can.DrawLine(16 + x_, 26 + y_, 11 + x_, 20 + y_, 0, 0, 0, 1);
    Can.DrawLine(21 + x_, 21 + y_, 26 + x_, 26 + y_, 0, 0, 0, 1);
    Can.DrawLine(26 + x_, 21 + y_, 21 + x_, 26 + y_, 0, 0, 0, 1);
    Can.DrawLine(30 + x_, 21 + y_, 34 + x_, 26 + y_, 0, 0, 0, 1);
    Can.DrawLine(29 + x_, 26 + y_, 35 + x_, 21 + y_, 0, 0, 0, 1);
    Can.DrawLine(25 + x_, 31 + y_, 27 + x_, 29 + y_, 0, 0, 0, 1);
    Can.DrawLine(27 + x_, 29 + y_, 31 + x_, 29 + y_, 0, 0, 0, 1);
    Can.DrawLine(31 + x_, 29 + y_, 33 + x_, 31 + y_, 0, 0, 0, 1);
  }

 private:
  int counter = 0;
};

#endif
