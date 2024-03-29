#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "Game.h"
//#include "Player.h"
#include "Player2.h"
#include "Rectangle.h"


Game::Game() {
  _running = initGame();
  std::cout << "Created Game\n";
}

Game::~Game()
{
  deleteTextures();
  //Quit SDL_ttf
  TTF_Quit();
  std::cout << "Destroyed Game\n";
}

void Game::deleteTextures() {
  for (auto& i : game_textures)
    SDL_DestroyTexture(i.second);
  
}

void Game::loadLevel(std::string path) {
}

void Game::repositionImage() {
}

void Game::update() {
  repositionImage();
  // for (auto& i : _objects)
  //   i->update();
}

SDL_Rect Game::positionwrtCamera(GameObject* o) {
  SDL_Rect rect = {
      static_cast<int>(o->getX()) - _camera.x,
      static_cast<int>(o->getY()) - _camera.y,
      static_cast<int>(o->getW()),
      static_cast<int>(o->getH())
  };
  return rect;
}

bool Game::isRunning() const {
  return _running;
}

void Game::checkCollision(GameObject* obj1, GameObject* obj2) {
  //more details in copy
  //we can use dynamic programming here n memoiz some stuff or maybe not
  SDL_Rect r1 = positionwrtCamera(obj1);
  SDL_Rect r2 = positionwrtCamera(obj2);//scale = 1 
  SDL_Rect inter = getOverlapRect(r1,r2);
  int area = 0;
  area = getRectArea(inter);
  if (area == 0)
    return; // no collision
  else if (area > 0) { //collision occured
    //notify the pair
    obj1->hasCollided(obj2->getType(), inter);
    obj2->hasCollided(obj1->getType(), inter);
  }
  //we r cool now
}

void Game::updateCollision() {
    //use for loops with iterators to iterate thru pairs
    //player-enemy pairs
    //sweet ;)
}

//i have a 2KRO keyboard :/
void Game::pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    _window->pollEvents(&event);
    //playerobj->getInput(&event);
    if (_window->isClosed())
      _running = false;
  }
  
}

/*
* cannot press more than 2 normal keys simultaneously unless one of them is a modifier key 
* which are wired and programmed to be pressed alongside some other key
* example if i press LEFT RIGHT and hold them then press UP the UP wont be detected until one of RIGHT or LEFT key is released 
* making space for UP to be detected
* this is a hardware limitation
* this is the reason why JUMP should never be DONE using UP key
* this is the reason why I changed it to LCTRL key which is a modifier 
* nowadays n-key rollover keyboards are there which do not have this (key-ghosting issue)
* key-ghosting:condition in which beyond a limit key sequences become ambiguous or not detected 
* broke multiple key presses into sequence of key presses 
* every key press changes the state of game        
*/

void printFPS() {
    static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::steady_clock::now();
    static int fps; fps++;

    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - oldTime) >= std::chrono::seconds{ 1 }) {
        oldTime = std::chrono::steady_clock::now();
        std::cout << "FPS: " << fps <<  std::endl;
        fps = 0;
    }
}
void Game::draw() {
  // for (auto& i : _tiles)
  //   _renderer->renderTile(i, _tilemap);
  // for (auto& i : _objects)
  //  i->draw();
  _renderer->renderFillRect(_camera.x, _camera.y, _camera.w, _camera.h, "green");
  _renderer->clear();
  printFPS();
}

bool Game::initGame()
{
  _window = new Window("Game", SCREEN_W, SCREEN_H);
  if (_window->getWindow() == nullptr) {
    std::cerr << "failed to create window\n";
    return false;
  }
  std::cout << "Created window\n";

  _renderer = new Renderer(_window->getWindow());
  if (_renderer->getRenderer() == nullptr) {
    std::cerr << "failed to create renderer\n";
    return false;
  }
  std::cout << "Created renderer\n";

  _renderer->addColor("red", (SDL_Color){255, 0, 0, 255});
  _renderer->addColor("green", (SDL_Color){0, 255, 0, 255});
  _renderer->addColor("blue", (SDL_Color){0, 0, 255, 255});
  _camera = createRectangle(0, 0, SCREEN_W, SCREEN_H);
  std::cout << "Initialized renderer\n";

  texture_man = new TextureManager();
  std::cout << "Created texture manager\n";
#if 0
  _mountain = new Image(0, 0, _camera.w, _camera.h, texture_man->loadFromFile("assets/mountain.png", _renderer->getRenderer()));
  _cloud = new movingImage(_camera.w/2, 0, 64, 64, -1, 0, texture_man->loadFromFile("assets/cloud.png", _renderer->getRenderer()));
#endif
  return true;
}

bool Game::addTexture(std::string name, std::string path) {
  SDL_Texture* texture = texture_man->loadFromFile(path, _renderer->getRenderer());
  if (!texture)
    return false;
  if (game_textures.find(name) == game_textures.end())
    game_textures.emplace(name, texture);
  std::cout << "Texture added successfully\n";
  std::cout << " name = " << name << " path = " << path << "\n";
  return true;
}

bool Game::loadTextures(std::string configpath) {
  std::ifstream conf_file;
  conf_file.open(configpath);
  while (!conf_file.eof()) {
    std::string path;
    std::string name; 
    // Extracting word by word from stream 
    conf_file >> name;
    conf_file >> path;
    if (conf_file.eof())    
      addTexture(name, path);
    else
      return false;
  }
  conf_file.close();
  return true;
}

bool Game::addTileset(std::string name, int tile_w, int tile_h, int n_rows, int n_cols) {
  Tileset* tileset = new Tileset(tile_w, tile_h, n_rows, n_cols, name, game_textures[name]);
  if (_tilesets.find(name) == _tilesets.end())
    _tilesets.emplace(name, tileset);
  return true;
}

bool Game::loadTilesets(std::string tlstfile) {
  return true;
}

Renderer* Game::getRenderer() {
  return _renderer;
}

// something like load resources might do
