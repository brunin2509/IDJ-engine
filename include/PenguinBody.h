//
// Created by bruno on 21/04/18.
//

#ifndef INC_140017658_IDJ_PEGUINBODY_H
#define INC_140017658_IDJ_PEGUINBODY_H


#include <memory>
#include "Component.h"
#include "Vec2.h"

#define PENGUIN_ACCELERATION 100 // em pixels/s^2
#define PENGUIN_ATRICT 20 // em pixels/s^2
#define PENGUIN_ANGULAR_SPEED PI // em rads/s

class PenguinBody : public Component {
public:
    explicit PenguinBody(GameObject& associated);
    ~PenguinBody() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    static PenguinBody* player;

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

};


#endif //INC_140017658_IDJ_PEGUINBODY_H
