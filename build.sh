#!/bin/bash
g++ -o test_game src/GameObject.cpp src/Window.cpp src/main.cpp src/Renderer.cpp src/Sprite.cpp src/Rectangle.cpp src/TextureManager.cpp src/Player.cpp src/Controllable.cpp src/Game.cpp src/Tileset.cpp -Iinclude/  -lSDL2 -lSDL2_image -lSDL2_ttf && echo "Build successful"
