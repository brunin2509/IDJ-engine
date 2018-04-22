//
// Created by bruno on 21/04/18.
//

#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody):
        Component(associated),
        pbody(penguinBody),
        angle(0){

    auto sprite = new Sprite(associated, "./assets/img/cubngun.png");
    associated.AddComponent(sprite);
    associated.angleDeg = angle*180/PI;
}

void PenguinCannon::Update(float dt) {
    if(pbody.expired()){
        associated.RequestDelete();
        return;
    }

    auto inputManager = InputManager::GetInstance();
    auto penguinBody = pbody.lock();

    associated.box.PlaceCenterAt(penguinBody->box.Center());

    angle = Vec2(inputManager.GetMouseX()+Camera::pos.x, inputManager.GetMouseY()+Camera::pos.y).InclinationOfDifference(associated.box.Center());
    associated.angleDeg = angle*180/PI;

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
        Shoot();
    }
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot() {

    auto bulletGO = new GameObject();

    auto bullet = new Bullet(
            *bulletGO,
            angle,
            PENGUIN_BULLET_SPEED,
            std::rand() % 11 + PENGUIN_BULLET_MAX_DAMAGE - 10,
            PENGUIN_BULLET_MAX_DISTANCE,
            "./assets/img/penguinbullet.png",
            4,
            0.1);

    bulletGO->AddComponent(bullet);

    bulletGO->box.PlaceCenterAt(associated.box.Center());

    auto bulletPos = Vec2(associated.box.w/2,0);
    bulletPos = bulletPos.Rotate(angle);

    bulletGO->box += bulletPos;

    Game::GetInstance().GetState().AddObject(bulletGO);
}
