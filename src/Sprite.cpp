//
// Created by bruno on 18/03/18.
//

#include <Game.h>

using std::cerr;

Sprite::Sprite(GameObject &associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file) : Component(associated) {
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

    SetClip(0, 0, width, height);
    this->associated.box.w = width;
    this->associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstRect{};
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) != 0){
        cerr << "SDL_RenderCopy RETURNED ERROR: " << SDL_GetError();
        exit(1);
    }
}

void Sprite::Render() {
    Render((int) this->associated.box.x, (int) this->associated.box.y);
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

void Sprite::Update(float dt) {
    //todo?
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}


