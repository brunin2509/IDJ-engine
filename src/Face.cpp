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


