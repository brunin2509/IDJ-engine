//
// Created by bruno on 08/04/18.
//

#include <Sprite.h>
#include <Bullet.h>
#include <Game.h>
#include "Minion.h"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg):
        Component(associated),
        alienCenter(*(alienCenter.lock())),
        arc(arcOffsetDeg) {

    auto sprite = new Sprite(associated, "./assets/img/minion.png");
    auto randScale = (std::rand() % 51 + 100)/100.0;
    sprite->SetScale(randScale, randScale);
    associated.AddComponent(sprite);

    Vec2 initialPos(RADIUS, 0);
    initialPos = initialPos.Rotate(arcOffsetDeg);
    associated.box = this->alienCenter.box.Center() + initialPos;
    associated.box.Centralize();
}

void Minion::Update(float dt) {
    Vec2 pos(RADIUS, 0);

    arc += ANGULAR_SPEED*dt;

    associated.angleDeg = (180/PI)*arc;

    pos = pos.Rotate(arc);
    associated.box = this->alienCenter.box.Center() + pos;
    associated.box.Centralize();
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
    auto bulletGO = new GameObject();
    bulletGO->box = associated.box.Center();

    auto bullet = new Bullet(
            *bulletGO,
            target.InclinationOfDifference(associated.box.Center()),
            BULLET_SPEED,
            std::rand() % 11 + BULLET_MAX_DAMAGE - 10,
            BULLET_MAX_DISTANCE,
            "./assets/img/minionbullet1.png");

    bulletGO->AddComponent(bullet);

    Game::GetInstance().GetState().AddObject(bulletGO);
}
