#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>

#include "Renderer.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Tileset.h"

// NES Screen Resolutions
#define SCREEN_W 256
#define SCREEN_H 256

//forward declaration needed because of circular dependency between the classes Game n GameObject
class GameObject;

class Game {
 public:
  Game();
  ~Game();
  bool isRunning() const;
  void pollEvents();
  void update();
  void draw();
  void loadLevel(std::string path);
  Renderer* getRenderer();
 private:
  TextureManager* texture_man;
  std::unordered_map<std::string, Tileset*> _tilesets;
  SDL_Rect _camera;//just for a simple compile 
  Window* _window;
  Renderer* _renderer; 
  bool _running;
  GameObject* playerobj;
  //std::vector<Tile*> _tiles;
  std::vector<GameObject*> _objects;
  //std::string _level_map; // not being used
  std::unordered_map<std::string, SDL_Texture*> game_textures;
  void updateCamera();  
  bool initGame();
  bool loadTextures(std::string configpath);
  bool loadTilesets(std::string tlstfile);
  bool addTexture(std::string name, std::string path);
  // called after loadTextures has been called
  bool addTileset(std::string name, int tile_w, int tile_h, int n_rows, int n_cols);
  void deleteTextures();
  bool loadObjects();
  void freeObjects();
  SDL_Rect positionwrtCamera(GameObject* o);
  void updateCollision();
  void checkCollision(GameObject* obj1, GameObject* obj2); // in future a collision class as well which can do complex stuff
};
#endif