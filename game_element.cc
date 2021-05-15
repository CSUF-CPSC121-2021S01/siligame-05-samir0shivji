#include "game_element.h"

#include "cpputils/graphics/image.h"

void GameElement::Draw(graphics::Image& image) {
  image.DrawRectangle(x_, y_, 5, 5, 0, 0, 0);
}

bool GameElement::IntersectsWith(const GameElement* elem) {
  return !(GetX() > elem->GetX() + elem->GetWidth() ||
           elem->GetX() > GetX() + GetWidth() ||
           GetY() > elem->GetY() + elem->GetHeight() ||
           elem->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image& image) {
  if (GetX() + GetWidth() > image.GetWidth() || GetX() < 0 ||
      GetY() + GetHeight() > image.GetHeight() || GetY() < 0) {
    return true;
  } else {
    return false;
  }
}
