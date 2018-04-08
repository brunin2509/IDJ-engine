//
// Created by bruno on 08/04/18.
//

#ifndef INC_140017658_IDJ_BULLET_H
#define INC_140017658_IDJ_BULLET_H


#include <Component.h>
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    int GetDamage();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
    float speedMagnitude;

};


#endif //INC_140017658_IDJ_BULLET_H
