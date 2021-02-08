#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>


class Window {
 private:
  std::string _title;
  int _height;
  int _width;
  bool _closed;
  SDL_Window *_window=nullptr;//better than NULL
  //SDL_Rect default_screen; // default screen to everything
  bool initWindow();
  bool init();

 public:
  Window(const std::string &title,int height,int width);
  ~Window();
  bool isClosed() const { 
    return _closed; 
  }
  void pollEvents(SDL_Event *event);
  int getW();
  int getH();
  SDL_Window* getWindow();
};
#endif