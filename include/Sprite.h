//
// Created by bruno on 18/03/18.
//

#ifndef INC_140017658_T1_SPRITE_H
#define INC_140017658_T1_SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <iostream>

class Sprite {
public:
    Sprite();
    explicit Sprite(std::string file);
    ~Sprite();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
};


#endif //INC_140017658_T1_SPRITE_H
