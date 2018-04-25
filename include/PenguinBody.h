//
// Created by bruno on 21/04/18.
//

#ifndef INC_140017658_IDJ_PEGUINBODY_H
#define INC_140017658_IDJ_PEGUINBODY_H


#include <memory>
#include "Component.h"
#include "Vec2.h"

#define PENGUIN_MAX_LINEAR_SPEED 500 // em pixels/s
#define PENGUIN_ACCELERATION 1000 // em pixels/s^2
#define PENGUIN_ATRICT 150 // em pixels/s^2
#define PENGUIN_ANGULAR_SPEED PI // em rads/s
#define PENGUIN_INITIAL_HP 30

class PenguinBody : public Component {
public:
    explicit PenguinBody(GameObject& associated);
    ~PenguinBody() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject& other) override;

    static PenguinBody* player;

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

};


#endif //INC_140017658_IDJ_PEGUINBODY_H
