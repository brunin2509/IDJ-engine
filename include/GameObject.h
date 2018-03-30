//
// Created by bruno on 28/03/18.
//

#ifndef INC_140017658_IDJ_GAMEOBJECT_H
#define INC_140017658_IDJ_GAMEOBJECT_H

#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"

class GameObject {
public:
    GameObject();
    ~GameObject();

    Rect box{0,0,0,0};

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);

private:
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;
};


#endif //INC_140017658_IDJ_GAMEOBJECT_H
