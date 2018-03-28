//
// Created by bruno on 28/03/18.
//

#include <typeinfo>
#include "GameObject.h"

GameObject::GameObject() {
    this->isDead = false;
}

GameObject::~GameObject() {
    for (auto &component : this->components) {
        delete component;
    }
    this->components.clear();
}

void GameObject::Update(float dt) {
    for (auto &component : this->components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto &component : this->components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    this->components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt) {
    for (int i = 0; i < this->components.size(); i++) {
        if(this->components[i] == cpt){
            this->components.erase(this->components.begin() + i);
        }
    }
}

Component *GameObject::GetComponent(std::string type) {
    for (auto &component : this->components) {
        if(component->Is(type)){
            return component;
        };
    }

    return nullptr;
}




