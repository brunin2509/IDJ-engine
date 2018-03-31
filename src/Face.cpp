//
// Created by bruno on 28/03/18.
//

#include <Sound.h>
#include "Face.h"

Face::Face(GameObject &associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    if(hitpoints <= 0) return; // no need to do anything to an HP that is already 0 or less

    hitpoints -= damage;

    if(hitpoints <= 0){

        auto soundComponent = (Sound*) associated.GetComponent("Sound");

        if(soundComponent){
            soundComponent->Play();
        }

        // todo: its still bad, because, even without the sprite, we know the component
        // todo: still exists, and it is still clickable
        // currently, this problem is being treated inside State::Input
        associated.RemoveComponent(associated.GetComponent("Sprite"));
    }
}

void Face::Update(float dt) {
    if(Died()){
        auto soundComponent = (Sound*) associated.GetComponent("Sound");

        if(soundComponent && !soundComponent->IsPlaying()){
            associated.RequestDelete(); // objeto morre somente se o componente ja tocou o som
        }
    }


}

void Face::Render() {

}

bool Face::Is(std::string type) {
    return type == "Face";
}

bool Face::Died() {
    return hitpoints <= 0;
}


