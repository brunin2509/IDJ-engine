//
// Created by bruno on 08/04/18.
//

#include <Sprite.h>
#include <Collider.h>
#include "Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer) :
        Component(associated),
        targetsPlayer(targetsPlayer),
        speed(speed,0),
        distanceLeft(maxDistance),
        damage(damage),
        speedMagnitude(speed){

    auto spriteComponent = new Sprite(associated, sprite, frameCount, frameTime);

    associated.AddComponent(spriteComponent);

    associated.AddComponent(new Collider(associated));

    associated.angleDeg = (180/PI)*angle;

    this->speed = this->speed.Rotate(angle);
}

void Bullet::Update(float dt) {
    distanceLeft -= speedMagnitude*dt;

    if(distanceLeft <= 0){
        associated.RequestDelete();
        return;
    }

    associated.box += speed*dt;
}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::NotifyCollision(GameObject &other) {
    if(other.GetComponent("Alien") && !targetsPlayer || other.GetComponent("PenguinBody") && targetsPlayer ){
        associated.RequestDelete();
    }
}
