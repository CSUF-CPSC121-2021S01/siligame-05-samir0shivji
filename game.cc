#include "game.h"

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opp = std::make_unique<Opponent>(100, 100);
  GetOpponents().push_back(std::move(opp));
}

void Game::OnAnimationStep() {
  if (opponents.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  gameScreen.Flush();
}
void Game::Init() {
  player.GameElement::SetX(player.GameElement::GetX() + 1);
  player.GameElement::SetY(player.GameElement::GetY() + 1);
  gameScreen.AddMouseEventListener(*this);
  gameScreen.AddAnimationEventListener(*this);
}
void Game::UpdateScreen() {
  std::string score = "Score: " + std::to_string(score_);
  gameScreen.DrawText(10, 10, score, 5, graphics::Color(0, 0, 0));
  gameScreen.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  if (playerStatus == true) {
    gameScreen.DrawText(gameScreen.GetWidth() / 2, gameScreen.GetHeight() / 2,
                        "GAME OVER", 20, graphics::Color(0, 0, 0));
  }
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->GetIsActive() == true) {
      opponents[i]->Draw(gameScreen);
    } else {
      continue;
    }
  }
  for (int x = 0; x < oProjectiles.size(); x++) {
    if (oProjectiles[x]->GetIsActive() == true) {
      oProjectiles[x]->Draw(gameScreen);
    } else {
      continue;
    }
  }
  for (int y = 0; y < pProjectiles.size(); y++) {
    if (pProjectiles[y]->GetIsActive() == true) {
      pProjectiles[y]->Draw(gameScreen);
    } else {
      continue;
    }
  }
  if (player.GetIsActive() == true) {
    player.Draw(gameScreen);
  }
}
void Game::Start() { gameScreen.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->GetIsActive()) {
      opponents[i]->Move(gameScreen);
    }
  }
  for (int x = 0; x < oProjectiles.size(); x++) {
    if (oProjectiles[x]->GetIsActive()) {
      oProjectiles[x]->Move(gameScreen);
    }
  }
  for (int y = 0; y < pProjectiles.size(); y++) {
    if (pProjectiles[y]->GetIsActive()) {
      pProjectiles[y]->Move(gameScreen);
    }
  }
}

void Game::FilterIntersections() {
  for (int x = 0; x < opponents.size(); x++) {
    if (player.IntersectsWith(opponents[x].get()) == true) {
      player.SetIsActive(false);
      opponents[x]->SetIsActive(false);
      playerStatus = true;
    }
  }
  for (int i = 0; i < oProjectiles.size(); i++) {
    if (player.IntersectsWith(oProjectiles[i].get()) == true) {
      player.SetIsActive(false);
      oProjectiles[i]->SetIsActive(false);
      playerStatus = true;
    }
  }
  for (int y = 0; y < opponents.size(); y++) {
    for (int a = 0; a < pProjectiles.size(); a++) {
      if (opponents[y]->IntersectsWith(pProjectiles[a].get()) == true) {
        opponents[y]->SetIsActive(false);
        pProjectiles[a]->SetIsActive(false);
        if (player.GetIsActive() == true) {
          score_++;
        }
      }
    }
  }
}

void Game::OnMouseEvent(const graphics::MouseEvent &mouseEvent) {
  if (mouseEvent.GetMouseAction() == graphics::MouseAction::kMoved ||
      mouseEvent.GetMouseAction() == graphics::MouseAction::kDragged) {
    int temp_x = player.GetX();
    int temp_y = player.GetY();
    player.SetX(mouseEvent.GetX() - player.GetWidth() / 2);
    player.SetY(mouseEvent.GetY() - player.GetHeight() / 2);
    if (player.GetX() > 800 || player.GetX() < 0) {
      player.SetX(temp_x);
    }
    if (player.GetY() > 600 || player.GetY() < 0) {
      player.SetY(temp_y);
    }
  }
  if (mouseEvent.GetMouseAction() == graphics::MouseAction::kPressed ||
      mouseEvent.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> pProj =
        std::make_unique<PlayerProjectile>(player.GetX(), player.GetY());
    pProjectiles.push_back(std::move(pProj));
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents.size(); i++) {
    std::unique_ptr<OpponentProjectile> oProj =
        std::make_unique<OpponentProjectile>();
    if (oProj != nullptr) {
      GetOpponentProjectiles().push_back(std::move(oProj));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = opponents.size() - 1; i >= 0; i--) {
    if (opponents[i]->GetIsActive() == false) {
      opponents.erase(opponents.begin() + i);
    } else {
      continue;
    }
  }
  for (int i = oProjectiles.size() - 1; i >= 0; i--) {
    if (oProjectiles[i]->GetIsActive() == false) {
      oProjectiles.erase(oProjectiles.begin() + i);
    } else {
      continue;
    }
  }
  for (int i = pProjectiles.size() - 1; i >= 0; i--) {
    if (pProjectiles[i]->GetIsActive() == false) {
      pProjectiles.erase(pProjectiles.begin() + i);
    } else {
      continue;
    }
  }
}
