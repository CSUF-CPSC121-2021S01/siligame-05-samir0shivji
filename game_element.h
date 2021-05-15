#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H
#include <fstream>
#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : x_(0), y_(0), width_(50), height_(50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  void SetX(int x) { x_ = x; }
  int GetX() const { return x_; }
  void SetY(int y) { y_ = y; }
  void SetIsActive(bool state) { is_active = state; }
  int GetY() const { return y_; }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  bool GetIsActive() const { return is_active; }
  virtual void Draw(graphics::Image& image) = 0;
  virtual void Move(const graphics::Image& image) = 0;
  bool IntersectsWith(const GameElement& elem);
  bool IsOutOfBounds(const graphics::Image& img);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active = true;
};
#endif
