//
// Created by bruno on 17/05/18.
//

#include <Camera.h>
#include <Game.h>
#include <Resources.h>
#include "Text.h"

using std::cerr;

Text::Text(GameObject &associated, std::string fontFile, int fontSize, Text::TextStyle style, std::string text, SDL_Color color, float intermittenceSeconds):
        Component(associated),
        texture(nullptr),
        text(text),
        style(style),
        fontFile(fontFile),
        fontSize(fontSize),
        color(color),
        intermittenceCount(0),
        intermittenceSeconds(intermittenceSeconds){
    RemakeTexture();
}

Text::~Text() {
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {
    if(intermittenceSeconds > 0){
        intermittenceCount.Update(dt);
        float currentTime = intermittenceCount.Get();
        float twiceIntermittenceSeconds = 2 * intermittenceSeconds;
        if(currentTime > twiceIntermittenceSeconds){
            intermittenceCount.Set(currentTime - twiceIntermittenceSeconds);
        }
    }
}

void Text::Render() {
    // only render if the timer is between 0 and intermittenceSeconds
    if(intermittenceCount.Get() < intermittenceSeconds){
        SDL_Rect dstRect{};
        dstRect.x = (int) (associated.box.x - Camera::pos.x);
        dstRect.y = (int) (associated.box.y - Camera::pos.y);
        dstRect.w = (int) (associated.box.w);
        dstRect.h = (int) (associated.box.h);

        SDL_Rect clipRect{};
        clipRect.x = 0;
        clipRect.y = 0;
        clipRect.w = (int) (associated.box.w);
        clipRect.h = (int) (associated.box.h);

        if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0){
            cerr << "SDL_RenderCopy RETURNED ERROR: " << SDL_GetError();
            exit(1);
        }
    }
}

bool Text::Is(std::string type) {
    return type == "Text";
}

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(Text::TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if(texture){
        SDL_DestroyTexture(texture);
    }

    font = Resources::GetFont(fontFile, fontSize);

    if(!font){
        cerr << "This font could not be opened. Aborting...\n";
        exit(1);
    }

    SDL_Surface* surface = nullptr;

    switch(style){
        case SOLID:
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
        case BLENDED:
            surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
        default:
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, GetSDLColor(255, 0, 0, 0));
    }

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

    if(!font){
        cerr << "This texture could not be loaded from the surface. Aborting...\n";
        exit(1);
    }

    associated.box.w = surface->w;
    associated.box.h = surface->h;

    SDL_FreeSurface(surface);
}

SDL_Color Text::GetSDLColor(Uint8 a, Uint8 r, Uint8 g, Uint8 b) {
    return {r, g, b, a};
}


