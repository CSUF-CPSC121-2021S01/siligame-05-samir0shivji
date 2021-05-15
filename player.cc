#include "player.h"

#include <fstream>
#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

void Player::Move(const graphics::Image& image) {}

void PlayerProjectile::Move(const graphics::Image& image) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}
