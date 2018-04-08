//
// Created by bruno on 23/03/18.
//

#include "Rect.h"

Rect::Rect() {
    x = 0.0;
    y = 0.0;
    w = 0.0;
    h = 0.0;
}

Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect::operator+(Vec2 vec) {
    return {vec.x+this->x, vec.y+this->y, this->w, this->h};
}

Vec2 Rect::Center() {
    return {this->x+this->w/2, this->y+this->h/2};
}

Vec2 Rect::DifferenceBetweenCenters(Rect r2) {
    return this->Center()-r2.Center();
}

bool Rect::Contains(Vec2 vec) {
    return vec.x >= x && vec.x <= x+w && vec.y >= y && vec.y <= y+h;
}

void Rect::Centralize() {
    x = x - w/2;
    y = y - h/2;
}

