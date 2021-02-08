#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <unordered_map>
#include <vector>
#include <string>
#include <array>

#include "Game.h"

 //**not an abstract base class anymore


#define MAXSTATES 20

//forward declaration needed because of circular dependency
class Game;
class Tileset;

enum class ObjectType {
  PLAYER,
  ENEMY,
  OTHER
};


class GameObject {
 protected:
  Game& _game;
  Renderer* _renderer;
  SDL_Texture* _texture;
  Tileset* _tileset;
  bool _alive;
  float _x, _y;// these will be static_cast<int>()-ed
  float _vx,_vy;// 
  float _ax,_ay;// velocity n acceleration arent that universal ig
  std::array<std::string, MAXSTATES> states{ "default" };
  std::string current_state;
  Sprite* curSprite; // ptr to current 
  ObjectType _otype;
  //CollisionBox* curBox;
  int _w,_h; //collision shape parameters...for now no hit boxes data inside Sprite class
  void changeState(std::string nextstate);
  virtual void updateState();
  //array of sprites
  std::vector<Sprite*> sprites; // sprites obj ptr s
  //vector<SDL_Rect> collisionBoxes;
  std::unordered_map<std::string, Sprite*> spriteset; // associated array for the above
  //std::unordered_map<std::string, CollisionBox*> collisionBoxSet;
  virtual bool initSprites();
  void updateSprite(bool change);
  void updateSpriteFrame();
  // i think there shud be a separate animated_sprite class
  void addSprite(std::string name, bool isanim, int tile_id, float scale, int n_frame, int n_loop, float fps);
  void updateX(){ _x = _x + _vx; }
  void updateY(){ _y = _y + _vy; }
  void updatevX(){ _vx = _vx + _ax; }
  void updatevY(){ _vy = _vy + _ay; }
  void setvX(float vx){ _vx = vx;}
  void setvY(float vy){ _vy = vy;}
  void setaX(float ax){ _ax = ax;}
  void setaY(float ay){ _ay = ay;}
  void setY(float y){ _y = y;}
  void setX(float x){ _x = x;}
  //virtual SDL_Rect getNextFrame();
  virtual void checkBoundaryCollision(); //umm this is redundant
  virtual void resolveCollision(ObjectType withtype,SDL_Rect overlap_r);

 public:
  GameObject(Game &g, ObjectType otype, float x, float y, int w, int h, Tileset* ts);
  ~GameObject();
  float getX(){ return _x;};
  float getY(){ return _y;};
  int getW(){ return _w;}
  int getH(){ return _h;}
  float getvX(){ return _vx;};
  float getvY(){ return _vy;};
  float getaX(){ return _ax;};
  float getaY(){ return _ay;};
  ObjectType getType() { return _otype;}
  virtual void update();
  virtual void draw();
  virtual void getInput(SDL_Event* e) = 0;
  virtual void hasCollided(ObjectType withtype,SDL_Rect overlap_r);
  //could have passed a special collision struct containing details about collision but its fine for now
};
#endif