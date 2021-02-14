#include <iostream>
#include <fstream>
#include <sstream>

#include "Game.h"
//#include "Player.h"
#include "Player2.h"
#include "Rectangle.h"


Game::Game() {
  _running = true;
  if(!initGame())
    _running = false;
  std::cout << _running << "\n";
  std::cout << "Created Game\n";
}

Game::~Game()
{
  deleteTextures();
  std::cout<<"Destroying Game\n";
  //Quit SDL_ttf
  TTF_Quit();
}

void Game::deleteTextures() {
  for (auto& i : game_textures)
    SDL_DestroyTexture(i.second);
  
}

void Game::loadLevel(std::string path) {
}

void Game::repositionImage() {
  int ximg = _cloud->getXpos();
  int yimg = _cloud->getYpos();
  int imgw = _cloud->getW();
  int imgh = _cloud->getH();
  if (ximg + imgw <= 0)
    _cloud->changeX(_camera.w);
  if (yimg + imgh <= 0)
    _cloud->changeY(_camera.h);
  if (ximg >= _camera.w)
    _cloud->changeX(0);
  if (yimg >= _camera.h)
    _cloud->changeY(0);
}

void Game::update() {
  _cloud->update();
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

void Game::draw() {
  // for (auto& i : _tiles)
  //   _renderer->renderTile(i, _tilemap);
  // for (auto& i : _objects)
  //  i->draw();
  _renderer->renderImage(_mountain);
  _renderer->renderImage(_cloud);

  _renderer->clear();
}

bool Game::initGame()
{
  _window = new Window("Game", SCREEN_W, SCREEN_H);
  if (_window->getWindow() == nullptr) {
    std::cerr << "failed to create window\n";
    _running = false;
  }
  _renderer = new Renderer(_window->getWindow());
  if (_renderer->getRenderer() == nullptr) {
    std::cerr << "failed to create renderer\n";
    _running = false;
  }
  _renderer->addColor("red", (SDL_Color){255, 0, 0, 255});
  _renderer->addColor("green", (SDL_Color){0, 255, 0, 255});
  _renderer->addColor("blue", (SDL_Color){0, 0, 255, 255});
  _camera = createRectangle(0, 0, SCREEN_W, SCREEN_H);
  texture_man = new TextureManager();
  // loadTextures("texture.conf");
  // addTileset("sokoban", 64, 64, 8, 13);
  // _tilemap = new Tilemap(4, 4, GRID_SIZE, GRID_SIZE);
  // for (int i = 0; i < _tilemap->_grid_size; ++i) {
  //   _tiles.push_back(new Tile(89, _tilesets["sokoban"], i));
  // }
  //playerobj = new Player(*this, ObjectType::PLAYER, 0.0, 0.0, 64, 64, _tilesets["sokoban"]);
  //_objects.push_back(playerobj);
  _mountain = new Image(0, 0, _camera.w, _camera.h, texture_man->loadFromFile("assets/mountain.png", _renderer->getRenderer()));
  _cloud = new movingImage(_camera.w/2, 0, 64, 64, -1, 0, texture_man->loadFromFile("assets/cloud.png", _renderer->getRenderer()));
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