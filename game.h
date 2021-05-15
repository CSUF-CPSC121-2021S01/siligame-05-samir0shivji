#ifndef GAME_H
#define GAME_H
#include <fstream>
#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game() : gameScreen(800, 600) {}
  Game(int width, int height) : gameScreen(width, height) {}
  graphics::Image& GetGameScreen() { return gameScreen; }
  std::vector<std::unique_ptr<Opponent>>& GetOpponents() { return &opponents; }
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return &oProjectiles;
  }
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() { return &pProjectiles; }
  Player& GetPlayer() { return player; }
  int GetScore(){return score_;}
  bool HasLost(){return playerStatus;}
  std::unique_ptr<OpponentProjectile> LaunchProjectiles();
  void RemoveIncative();
  void MoveGameElements();
  void FilterIntersections();
  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent& mouseEvent);

 protected:
  graphics::Image gameScreen;
  std::vector<std::unique_ptr<Opponent>> opponents;
  std::vector<std::unique_ptr<OpponentProjectile>> oProjectiles;
  std::vector<std::unique_ptr<PlayerProjectile>> pProjectiles;
  Player player;
  int score_ = 0;
  bool playerStatus = true;
};
#endif
