//
// Created by bruno on 28/03/18.
//

#include "Component.h"

Component::Component(GameObject &associated) : associated(associated) {
}

Component::~Component(){

}

void Component::Start() {

}

void Component::NotifyCollision(GameObject &other) {

}
