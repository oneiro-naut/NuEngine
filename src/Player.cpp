#include <iostream>
#include "Player.h"

Player::Player(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ts): Controllable(g, otype, x, y, w, h, ts)
{
  initSprites();
}

Player::~Player()
{}

void Player::updateState() {

}

void Player::update() {
  updateSpriteFrame();
  updateState();
}

// void Player::draw() override {

// }

void Player::hasCollided(ObjectType withtype,SDL_Rect overlap_r) {

}

void Player::resolveCollision(ObjectType withtype,SDL_Rect overlap_r) {

}

void Player::onUserInput(SDL_Event* e) {
  switch (e->type) {
    case SDL_KEYDOWN:
    switch (e->key.keysym.sym)
    {
        case SDLK_LEFT:
        if (!_keystate[KeyCode::left])
          _x -= _w;
        changeState("left");
        _keystate[KeyCode::left] = true;
        break;
        case SDLK_RIGHT:
        if (!_keystate[KeyCode::right]) 
          _x += _w;
        changeState("right");
        _keystate[KeyCode::right] = true; 
        break;
        case SDLK_UP:    
        if (!_keystate[KeyCode::up])
          _y -= _h; 
        changeState("up");
        _keystate[KeyCode::up] = true;
        break;
        case SDLK_DOWN:  
        if (!_keystate[KeyCode::down])
          _y += _h;
        changeState("down");
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
  current_state = "down";
  curSprite = spriteset[current_state];
  return true;
}

void Player::checkBoundaryCollision() {

}