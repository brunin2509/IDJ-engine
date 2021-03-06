//
// Created by bruno on 08/04/18.
//

#ifndef INC_140017658_IDJ_MINION_H
#define INC_140017658_IDJ_MINION_H


#include <memory>
#include "Component.h"
#include "Vec2.h"

#define MINION_ANGULAR_SPEED (PI/2) // em rad/s
#define MINION_RADIUS 150 // em pixels
#define MINION_BULLET_SPEED 500
#define MINION_BULLET_MAX_DAMAGE 20
#define MINION_BULLET_MAX_DISTANCE 1000

class Minion : public Component {
public:
    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject& other) override;

    void Shoot(Vec2 target);

private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};


#endif //INC_140017658_IDJ_MINION_H
