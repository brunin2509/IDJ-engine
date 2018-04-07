//
// Created by bruno on 28/03/18.
//

#include <typeinfo>
#include "GameObject.h"

GameObject::GameObject(): isDead(false), started(false) {
}

GameObject::~GameObject() {
    for (auto it = this->components.rbegin(); it != this->components.rend(); it++) {
        it->reset();
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

void GameObject::AddComponent(Component* cpt) {
    this->components.emplace_back(cpt);

    if(started){
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    std::unique_ptr<Component>& component = *(new std::unique_ptr<Component>(cpt));

    for (int i = 0; i < this->components.size(); i++) {
        if(this->components[i] == component){
            this->components.erase(this->components.begin() + i);
        }
    }
}

Component* GameObject::GetComponent(std::string type) {

    for (auto it = this->components.begin(); it != this->components.end(); it++) {
        if((*it)->Is(type)){
            return (*it).get();
        };
    }

    return nullptr;
}

void GameObject::Start() {
    for (auto &component : components) {
        component->Start();
    }

    started = true;
}




