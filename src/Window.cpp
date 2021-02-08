#include "Window.h"
#include <iostream>

//I HATE Static variables (lol)

Window::Window(const std::string &title,int width,int height): _title(title), _height(height), _width(width) {
  _closed = false;

  //default_screen = { 0, 0, _width, _height}; // will be passed to renderer then Game obj will change it

  if(!initWindow())
  {
      _closed = true;
  }
}

bool Window::initWindow() {
  if (SDL_Init(SDL_INIT_VIDEO)!=0) {
    std::cerr << "Failed to initialize SDL.\n";
    return false; 
  }
  
  if (IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG) {
    std::cerr << "Failed to initilize SDL_image.\n";
    return false;
  }

  //Initialize SDL_ttf

  if ( TTF_Init() == -1 ) 
    return false;    
  
  //Create window

  _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0); 
  
  //c_str converts cpp string to c string
  
  std::cout << "Created window\n";  
  if (_window == nullptr) {
    std::cerr << "Failed to create window.\n";
    return false;
  }  
  return true;
}

// destructor
Window::~Window() {
  std::cout << "detroying window\n";
  SDL_DestroyWindow(_window);
  IMG_Quit();
  SDL_Quit();
}

void Window::pollEvents(SDL_Event *event) {
  switch(event->type) {
    case SDL_QUIT:
      _closed = true;
      std::cout << "Closing window!\n";
      break;
    case SDL_MOUSEMOTION:
      //cout<<event.motion.x<<","<<event.motion.y<<endl;
      break;
    case SDL_MOUSEBUTTONDOWN:
      //cout<<"Mouse clicked!"<<endl;    
      break;
    case SDL_MOUSEBUTTONUP:
      //cout<<"Mouse botton released!"<<endl;
      break;
    default:
      break;
  }  
}

int Window::getW() {
  return _width;
}

int Window::getH() {
  return _height;
}

SDL_Window* Window::getWindow() {
  return _window;
}