//
// Created by bruno on 28/03/18.
//

#include <Sound.h>
#include "Face.h"

Face::Face(GameObject &associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints -= damage;

    if(hitpoints <= 0){

        auto soundComponent = (Sound*) associated.GetComponent("Sound");

        if(soundComponent){
            soundComponent->Play();
        }

        associated.RequestDelete(); //todo: isso aqui ta bizarro
    }
}

void Face::Update(float dt) {

}

void Face::Render() {

}

bool Face::Is(std::string type) {
    return type == "Face";
}


