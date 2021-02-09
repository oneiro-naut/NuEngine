#include "Player2.h"

Player2::Player2(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ts): Player(g, otype, x, y, w, h, ts)
{}

Player2::~Player2()
{}

void Player2::onUserInput(SDL_Event* e) {
  switch (e->type) {
    case SDL_KEYDOWN:
    switch (e->key.keysym.sym)
    {
        case SDLK_LEFT:
        changeState("left");
        _x -= 8;
        _keystate[KeyCode::left] = true;
        break;
        case SDLK_RIGHT:
        changeState("right");
        _x += 8;
        _keystate[KeyCode::right] = true; 
        break;
        case SDLK_UP:    
        changeState("up");
        _y -= 8;
        _keystate[KeyCode::up] = true;
        break;
        case SDLK_DOWN:  
        changeState("down");
        _y += 8;
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