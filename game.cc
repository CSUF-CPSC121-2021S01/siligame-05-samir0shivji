#include "game.h"

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opp(100, 100);
  GetOpponents().push_back(opp);
}
void Game::CreateOpponentProjectiles() {
  std::unique_ptr<OpponentProjectile> oProj(100, 160);
  GetOpponentProjectiles().push_back(oProj);
}
void Game::CreatePlayerProjectiles() {
  std::unique_ptr<PlayerProjectile> pProj(300, 700);
  GetPlayerProjectiles().push_back(pProj);
}
void Game::OnAnimationStep() {
  if(opponents.size() == 0){
    CreateOpponents();
  }
  MoveGameElements();
  for(int i = 0; i < oppoents.size(); i++){
    opponents[i]->LaunchProjectiles();
  }
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
  gameScreen.DrawText(10, 10, "Score: ", 5, graphics::Color(0, 0, 0));
  gameScreen.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  if(playerStatus == false){
    gameScreen.DrawText(gameScreen.GetWidth()/2, gameScreen.GetHeight()/2, "GAME OVER", 20, graphics::Color(0, 0, 0));
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
    if (player.IntersectsWith(opponents[x]->Get()) == true) {
      player.SetIsActive(false);
      opponents[x]->SetIsActive(false);
      playerStatus = false;
    }
  }
  for (int i = 0; i < oProjectiles.size(); i++) {
    if (player.IntersectsWith(oProjectiles[i]->Get()) == true) {
      player.SetIsActive(false);
      oProjectiles[i]->SetIsActive(false);
      playerStatus = false;
    }
  }
  for (int y = 0; y < opponents.size(); y++) {
    for (int a = 0; a < pProjectiles.size(); a++) {
      if (opponents[y]->IntersectsWith(pProjectiles[a]->Get()) == true) {
        opponents[y]->SetIsActive(false);
        pProjectiles[a]->SetIsActive(false);
        score_++;
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
  if(mouseEvent.GetMouseAction() == graphics::MouseAction::kPressed){
    std::make_unique<PlayerProjectile> pProj;
    pProjectiles.push_back(std::move(pProj));
  }
}

std::unique_ptr<OpponentProjectile> Game::LaunchProjectiles(){
  for(int i = 0; i < oppoents.size(); i++){
    if(opponents[i]->LaunchProjectile() != nullptr){
      opponents[i] = std::move(push_back(opponents[i]->LaunchProjectile()));
    }
  }
}

void RemoveIncative(){
  for(int i = opponents.size()-1; i >= 0; i--){
    if(opponents[i]->GetIsActive() == false){
      opponents.erase(opponents.begin() + i);
    }else{
      continue;
    }
  }
  for(int i = oProjectile.size()-1; i >= 0; i--){
    if(oProjectiles[i]->GetIsActive() == false){
      oProjectiles.erase(oProjectiles.begin() + i);
    }else{
      continue;
    }
  }
  for(int i = pProjectiles.size()-1; i >=0; i--){
    if(pProjectiles[i]->GetIsActive() == false){
      pProjectiles.erase(pProjectiles.begin() + i);
    }else{
      continue;
    }
  }
}
