//
// Created by bruno on 18/03/18.
//

#include <Game.h>
#include <Camera.h>
#include "Resources.h"

using std::cerr;

Sprite::Sprite(GameObject &associated) :
        Component(associated),
        texture(nullptr),
        width(0),
        height(0),
        scale(1,1),
        frameCount(1),
        currentFrame(0),
        timeElapsed(0),
        frameTime(1),
        selfDestructCount(0),
        secondsToSelfDestruct(0) {
}

Sprite::Sprite(GameObject &associated, std::string file, float secondsToSelfDestruct): Sprite(associated) {
    Open(file);
    this->secondsToSelfDestruct = secondsToSelfDestruct;
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct): Sprite(associated, file, secondsToSelfDestruct) {
    SetFrameTime(frameTime);
    SetFrameCount(frameCount);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {

    texture = Resources::GetImage(file);

    if(!texture){
        cerr << "TEXTURE COULD NOT BE OPENED\n";
        exit(1);
    }

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

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

    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0){
        cerr << "SDL_RenderCopy RETURNED ERROR: " << SDL_GetError();
        exit(1);
    }
}

void Sprite::Render() {
    Render((int) (this->associated.box.x - Camera::pos.x), (int) (this->associated.box.y - Camera::pos.y));
}

int Sprite::GetWidth() {
    return (int) (clipRect.w*scale.x);
}

int Sprite::GetHeight() {
    return  (int) (clipRect.h*scale.y);
}

bool Sprite::IsOpen() {
    return texture!= nullptr;
}

void Sprite::Update(float dt) {
    if(secondsToSelfDestruct > 0){
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct){
            associated.RequestDelete();
            return;
        }
    }

    if(frameCount > 1){ // esse processo so faz sentido para sprites com mais de um frame (nao estaticas)
        timeElapsed += dt;

        if(timeElapsed > frameTime){
            timeElapsed -= frameTime;
            currentFrame++;
            SetClipToNewFrame();
        }
    }
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

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    SetClipToNewFrame();
}

void Sprite::SetClipToNewFrame() {
    if(currentFrame < frameCount){
        SetClip(currentFrame*clipRect.w, 0, clipRect.w, clipRect.h);
    }
    else{
        currentFrame = 0;
        SetClip(0, 0, clipRect.w, clipRect.h);
    }
}

void Sprite::SetFrameCount(int frameCount) {
    this->frameCount = frameCount;
    clipRect.w /= frameCount;
    associated.box.w = GetWidth(); // does the center matter?
    SetFrame(0);
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}




