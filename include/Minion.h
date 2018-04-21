//
// Created by bruno on 08/04/18.
//

#ifndef INC_140017658_IDJ_MINION_H
#define INC_140017658_IDJ_MINION_H


#include <memory>
#include "Component.h"
#include "Vec2.h"

#define ANGULAR_SPEED (PI/2) // em rad/s
#define RADIUS 150 // em pixels
#define BULLET_SPEED 100
#define BULLET_MAX_DAMAGE 20
#define BULLET_MAX_DISTANCE 1000

class Minion : public Component {
public:
    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void Shoot(Vec2 target);

private:
    GameObject& alienCenter;
    float arc;
};


#endif //INC_140017658_IDJ_MINION_H
