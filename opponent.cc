#include "opponent.h"

void Opponent::Move(const graphics::Image& image) {
  SetY(GetY() + 3);
  SetX(GetX() + 5);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}

void OpponentProjectile::Move(const graphics::Image& image) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (counter == 5) {
    std::unique_ptr<OpponentProjectile> projectile =
        std::make_unique<OpponentProjectile>(Opponent::GetX(),
                                             Opponent::GetY());
    counter = 0;
    return projectile;
  } else {
    counter++;
    return nullptr;
  }
}
