#include <iostream>
#include "Player.h"

Player::Player(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ts): Controllable(g, otype, x, y, w, h, ts)
{
  initSprites();
}

Player::~Player()
{}

// NOTE: diagonal movements look faster...fix them using normalization
// add 2d vector type to GameObject class
void Player::updateCoordinates() {
  // == acts as a xnor while != operator as xor for bool
  if (_keystate[KeyCode::left] == _keystate[KeyCode::right]) {
    _vx = 0;
  }
  else{
    if (_keystate[KeyCode::left]) {
      _vx = -4;
    }
    if (_keystate[KeyCode::right]) {
      _vx = 4;
    }
  }
  if (_keystate[KeyCode::up] == _keystate[KeyCode::down]) {
    _vy = 0;
  }
  else {
    if (_keystate[KeyCode::up]) {
      _vy = -4;
    }
    if (_keystate[KeyCode::down]) {
      _vy = 4;
    }
  }
  _x += _vx;
  _y += _vy;
}

void Player::updateState() {
  if (_vx == 0 && _vy == 0) {
    if (!current_state.compare("left"))
      changeState("left_idle");
    if (!current_state.compare("right"))
      changeState("right_idle");
    if (!current_state.compare("up"))
      changeState("up_idle");
    if (!current_state.compare("down"))
      changeState("down_idle");
    return;  
  }
  if (_vx < 0)
    changeState("left");
  if (_vx > 0)
    changeState("right");
  if (_vy < 0)
    changeState("up");
  if (_vy > 0)
    changeState("down");

}

void Player::update() {
  updateCoordinates();
  updateSpriteFrame();
  updateState();
}

// void Player::draw() override {

// }

void Player::hasCollided(ObjectType withtype, SDL_Rect overlap_r) {

}

void Player::resolveCollision(ObjectType withtype,SDL_Rect overlap_r) {

}

void Player::onUserInput(SDL_Event* e) {
  switch (e->type) {
    case SDL_KEYDOWN:
    switch (e->key.keysym.sym)
    {
      case SDLK_LEFT:
      _keystate[KeyCode::left] = true;
      break;
      case SDLK_RIGHT:
      _keystate[KeyCode::right] = true; 
      break;
      case SDLK_UP:    
      _keystate[KeyCode::up] = true;
      break;
      case SDLK_DOWN:  
      _keystate[KeyCode::down] = true;
      break;
      default:
      break;
    }
    break;
    case SDL_KEYUP:
    switch (e->key.keysym.sym)
    {
        case SDLK_LEFT:
        _keystate[KeyCode::left] = false;
        break;
        case SDLK_RIGHT:
        _keystate[KeyCode::right] = false; 
        break;
        case SDLK_UP:    
        _keystate[KeyCode::up] = false;
        break;
        case SDLK_DOWN:  
        _keystate[KeyCode::down] = false;
        break;
        default:
        break;
    }
    break;  
    default:
    break;
  }
}

bool Player::initSprites() {
  if (_texture)
    std::cout << "player texture loaded\n";
  addSprite("left", true, 81, 1.0, 3, -1, 1000/60);
  addSprite("right", true, 78, 1.0, 3, -1, 1000/60);
  addSprite("up", true, 55, 1.0, 3, -1, 1000/60);
  addSprite("down", true, 52, 1.0, 3, -1, 1000/60);
  addSprite("left_idle", false, 81, 1.0, 1, -1, 1000/60);
  addSprite("right_idle", false, 78, 1.0, 1, -1, 1000/60);
  addSprite("up_idle", false, 55, 1.0, 1, -1, 1000/60);
  addSprite("down_idle", false, 52, 1.0, 1, -1, 1000/60);
  current_state = "down_idle";
  curSprite = spriteset[current_state];
  return true;
}

void Player::checkBoundaryCollision() {

}