//
// Created by bruno on 21/04/18.
//

#ifndef INC_140017658_IDJ_PENGUINCANNON_H
#define INC_140017658_IDJ_PENGUINCANNON_H


#include <Component.h>
#include <memory>

#define PENGUIN_BULLET_SPEED 600
#define PENGUIN_BULLET_MAX_DAMAGE 20
#define PENGUIN_BULLET_MAX_DISTANCE 1000

class PenguinCannon : public Component {
public:
    PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject& other) override;

    void Shoot();

private:
    std::weak_ptr<GameObject> pbody;
    float angle;
};


#endif //INC_140017658_IDJ_PENGUINCANNON_H
