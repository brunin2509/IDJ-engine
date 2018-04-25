//
// Created by bruno on 08/04/18.
//

#include <Sprite.h>
#include <Bullet.h>
#include <Game.h>
#include <Collider.h>
#include "Minion.h"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg):
        Component(associated),
        alienCenter(alienCenter),
        arc(arcOffsetDeg) {

    auto sprite = new Sprite(associated, "./assets/img/minion.png");
    auto randScale = (std::rand() % 51 + 100)/100.0;
    sprite->SetScale(randScale, randScale);
    associated.AddComponent(sprite);

    associated.AddComponent(new Collider(associated));

    Vec2 initialPos(MINION_RADIUS, 0);
    initialPos = initialPos.Rotate(arcOffsetDeg);

    auto alienGO = alienCenter.lock();

    if(!alienGO){
        std::cout << "O ponteiro para o GameObject do Alien eh nullptr.\n";
        associated.RequestDelete();
        return;
    }

    associated.box.PlaceCenterAt(alienGO->box.Center() + initialPos);
}

void Minion::Update(float dt) {
    auto alienGO = alienCenter.lock();

    if(!alienGO){
        associated.RequestDelete();
        return;
    }

    Vec2 pos(MINION_RADIUS, 0);

    arc += MINION_ANGULAR_SPEED*dt;

    associated.angleDeg = (180/PI)*arc;

    pos = pos.Rotate(arc);
    associated.box.PlaceCenterAt(alienGO->box.Center() + pos);
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
    auto bulletGO = new GameObject();

    auto bullet = new Bullet(
            *bulletGO,
            target.InclinationOfDifference(associated.box.Center()),
            MINION_BULLET_SPEED,
            std::rand() % 11 + MINION_BULLET_MAX_DAMAGE - 10,
            MINION_BULLET_MAX_DISTANCE,
            "./assets/img/minionbullet2.png",
            3,
            0.1);

    bulletGO->AddComponent(bullet);

    bulletGO->box.PlaceCenterAt(associated.box.Center());

    Game::GetInstance().GetState().AddObject(bulletGO);
}

void Minion::NotifyCollision(GameObject &other) {
    // todo?
}
