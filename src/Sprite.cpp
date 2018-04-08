//
// Created by bruno on 18/03/18.
//

#include <Game.h>
#include <Camera.h>
#include "Resources.h"

using std::cerr;

Sprite::Sprite(GameObject &associated) : Component(associated), texture(nullptr), width(0), height(0), scale(1,1) {
}

Sprite::Sprite(GameObject &associated, std::string file) : Component(associated), texture(nullptr), width(0), height(0), scale(1,1) {
    Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {

    texture = Resources::GetImage(file);

    if(!texture){
        cerr << "TEXTURE COULD NOT BE OPENED\n";
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
    dstRect.w = (int) (clipRect.w*scale.x);
    dstRect.h = (int) (clipRect.h*scale.y);

    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0){
        cerr << "SDL_RenderCopy RETURNED ERROR: " << SDL_GetError();
        exit(1);
    }
}

void Sprite::Render() {
    Render((int) (this->associated.box.x - Camera::pos.x), (int) (this->associated.box.y - Camera::pos.y));
}

int Sprite::GetWidth() {
    return (int) (width*scale.x);
}

int Sprite::GetHeight() {
    return  (int) (height*scale.y);
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

void Sprite::SetScale(float scaleX, float scaleY) {
    scale.x = (scaleX) ? scaleX : scale.x;
    scale.y = (scaleY) ? scaleY : scale.y;
    auto oldCenter = associated.box.Center();
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
    associated.box += (oldCenter - associated.box.Center());
}

Vec2 Sprite::GetScale() {
    return scale;
}
