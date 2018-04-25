//
// Created by bruno on 28/03/18.
//

#ifndef INC_140017658_T1_COMPONENT_H
#define INC_140017658_T1_COMPONENT_H

#include <iostream>

class GameObject;

class Component {
public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;
    virtual void Start();
    virtual void NotifyCollision(GameObject& other);

protected:
    GameObject& associated;
};


#endif //INC_140017658_T1_COMPONENT_H
