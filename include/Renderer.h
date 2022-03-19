#ifndef RENDERER_H
#define RENDERER_H
#include <unordered_map>
#include <string>

#include "Window.h" // for now i wont make it independent of Window class // i will now ;)
#include "Image.h"
#include "Sprite.h"
#include "Tile.h"
#include "Tilemap.h"

const SDL_Color red = { 255, 0, 0, 255 };

//it can render Sprite objects and maybe text
class Renderer{ 
 private:
  //associated window (not just a reference)
  SDL_Window* _pwin;
  //camera basically
  std::unordered_map<std::string, SDL_Color> color_map;
  //will point to window renderer here
  SDL_Renderer* _renderer;
  void createRenderer();
  void apply_text(SDL_Surface* surface,SDL_Rect position);
  SDL_Rect getDestinationRect(float x,float y,int width,int height,float scale);  

 public:
  Renderer(SDL_Window* win);
  ~Renderer();
  void clear();
  //notifies about renderer init status to Window class
  bool initComplete() const;
  void addColor(std::string colorname, SDL_Color color);
  //reference or ptr idk man
  void renderSprite(Sprite* sprite, float x, float y); 
  void renderSprite(Sprite* sprite, float x, float y, float scale);
  void renderSprite(Sprite* sprite, float x, float y, float scale, SDL_RendererFlip flip);
  void renderSprite(Sprite* sprite, float x, float y, float scale, double angle, SDL_Point* center, SDL_RendererFlip flip);
  // char * rules because i m illiterate when it comes to string...well...not really
  void renderImage(Image* img);
  void renderText(const char* text, int x, int y, TTF_Font* font, SDL_Color color);  
  void renderTexture(SDL_Texture* texture, SDL_Rect srcrect, SDL_Rect drect, double angle, SDL_Point* center, SDL_RendererFlip flip);
  void renderTexture(SDL_Texture* texture, int x, int y);
  void renderTexture(SDL_Texture* texture, SDL_Rect drect);
  void renderTile(Tile* tile, Tilemap* tilemap);
  //idk how to create a formatted std::string so...sprintf anyday ;] //use stringstream dumbhead
  void renderRect(float x, float y, int w, int h, std::string color);
  void renderFillRect(int x, int y, int w, int h, std::string color);
  SDL_Renderer* getRenderer();
};
#endif
