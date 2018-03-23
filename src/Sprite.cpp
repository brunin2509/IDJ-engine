//
// Created by bruno on 18/03/18.
//

#include <Game.h>

using std::cerr;

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(std::string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if(texture){
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if(!texture){
        cerr << "IMG_LoadTexture RETURNED ERROR: " << SDL_GetError();
        exit(1);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height); // by default, set the clip to hold the whole texture
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) != 0){
        cerr << "SDL_RenderCopy RETURNED ERROR: " << SDL_GetError();
        exit(1);
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return  height;
}

bool Sprite::IsOpen() {
    return texture!= nullptr;
}


