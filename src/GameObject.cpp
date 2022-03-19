#include "GameObject.h"
#include <iostream>
using namespace std;
//having 3 constructors n only 1 of them having renderer init caused undefined behaviour therefore make only 1 base contructor for 
//every entity to avoid further ambuities

GameObject::GameObject(Game& g, ObjectType otype, float x, float y, int w, int h, Tileset* ts) : _game(g)
{
  _otype = otype;
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  _tileset = ts;
  _vx = 0.0;
  _vy = 0.0;
  _ax = 0.0;
  _ay = 0.0;
  _texture = _tileset->getTexture();
  _renderer = _game.getRenderer();
  if(!initSprites())
  {
    _alive = false;
  }
}

GameObject::~GameObject()
{

}

void GameObject::draw() {
  //_renderer->renderRect(_x, _y, _w, _h, "red");
  _renderer->renderSprite(curSprite, _x, _y);
}

void GameObject::updateSprite(bool change)
{
  if(change == true)
  {
      curSprite->stop();
      curSprite = spriteset[current_state];
  }   
  curSprite->update(); 
}

void GameObject::updateSpriteFrame()
{
  curSprite->update();
}

void GameObject::update()
{
  updateSpriteFrame();
  updateState();
}

// void GameObject::updatePosition()
// {
//   updateX();
//   updateY();
//   checkBoundaryCollision();
// }

void GameObject::resolveCollision(ObjectType withtype,SDL_Rect overlap_r)
{

}

void GameObject::checkBoundaryCollision()
{

}

void GameObject::updateState()
{
    // if(curSprite->isOver())
    // {
    //     if(!strcmp(state,"shield"))changeState("idle");
    // }
}

void GameObject::changeState(std::string nextstate)
{
  bool changed = true;
  if( !current_state.compare(nextstate))
  {
      changed = false;
  }   
  current_state = nextstate;
  updateSprite(changed);    
}

void GameObject::addSprite(std::string name, bool isanim, int tid, float scale, int n_frame, int n_loop, float fps)
{
  SDL_Rect base_f = _tileset->getBaseFrameByTileID(tid);
  Sprite* s = new Sprite(n_frame, n_loop, fps, scale, base_f, _texture, isanim);
  // sprites.push_back(s);
  spriteset.emplace(name,s);//made name value pair for the sprite
}

// is overriden
bool GameObject::initSprites() //can be parsed from a file
{
//     SDL_Rect idle = {192,32,32,32};//can store these offsets in a file to parse
// //    SDL_Rect sh = {320,32,32,32};
//     //sdl rect up sdl rect down...
//     state = "idle";
//     addSprite(state,4,-1,10,idle,sheet);
//     curSprite = spriteset[state];
    return true;
}


void GameObject::hasCollided(ObjectType withtype,SDL_Rect overlap_r)
{
    cout<<"Collision occured!"<<endl;
}
