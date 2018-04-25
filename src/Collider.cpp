//
// Created by bruno on 23/04/18.
//

#include <GameObject.h>
#include "Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset):
        Component(associated),
        scale(scale),
        offset(offset){
}

void Collider::Update(float dt) {
    box = associated.box;

    box.w *= scale.x;
    box.h *= scale.y;

    box.PlaceCenterAt(associated.box.Center());
    box += offset.Rotate(associated.angleDeg*PI/180);
}

void Collider::Render() {

}

bool Collider::Is(std::string type) {
    return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}


