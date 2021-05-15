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

std::unique_ptr<OpponentProjectile> OpponentProjectile::LaunchProjectile(GameElement* object){
  std::unique_ptr<OpponentProjectile> projectile;
  int counter = 0;
  if(counter < 5){
    counter ++;
    projectile = nullptr;
    return projectile;
  }else{
    projectile = std::make_unique<OpponentProjectile>(object->GetX(), object->GetY());
    counter = 0;
    return std::move(projectile);
  }
}
