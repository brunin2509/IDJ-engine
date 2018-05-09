//
// Created by bruno on 08/05/18.
//

#include "State.h"

State::State():
        popRequested(false),
        quitRequested(false),
        started(false) {

}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *object) {
    std::shared_ptr<GameObject> sharedGO(object);

    objectArray.push_back(sharedGO);

    if(started){
        object->Start();
    }
    return std::weak_ptr<GameObject>(sharedGO);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object) {
    for(auto& it : objectArray){
        if(it.get() == object){
            return std::weak_ptr<GameObject>(it);
        }
    }

    return std::weak_ptr<GameObject>();
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    LoadAssets();

    for (unsigned i = 0; i < objectArray.size(); i++) {
        if(objectArray[i].get()){
            objectArray[i]->Start();
        }
        else{ // if null...
            std::cout << "shared_ptr contains a null reference to a GameObject inside objectArray\n";
        }
    }

    started = true;
}

void State::UpdateArray(float dt) {
    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (auto &gameObjects : objectArray) {
        gameObjects->Render();
    }
}


