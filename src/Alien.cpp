//
// Created by bruno on 07/04/18.
//

#include <Sprite.h>
#include <Camera.h>
#include <Game.h>
#include <Minion.h>
#include <Collider.h>
#include <Bullet.h>
#include <Sound.h>
#include <PenguinBody.h>
#include "Alien.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions, float timeOffset):
        Component(associated),
        speed(0,0),
        hp(ALIEN_INITIAL_HP),
        nMinions(nMinions),
        state(RESTING),
        restTimer(timeOffset),
        destination(0,0) {
    associated.AddComponent(new Sprite(associated, "./assets/img/alien.png"));
    associated.AddComponent(new Collider(associated));
    alienCount++;
}

Alien::~Alien(){
    // nao eh boa pratica desalocar a memoria de um shared_ptr por alguem que possui acesso so ao weak_ptr,
    // ja que esse ponteiro eh compartilhado. Deixe para o proprio shared_ptr deletar o objeto automaticamente.
    minionArray.clear();
    alienCount--;
}

void Alien::Start() {
    //auto game = Game::GetInstance();
    GameObject* minionGO = nullptr;
    Minion* minion = nullptr;
    double minionInitialArc = 0;

    for(int i = 0; i < nMinions; i++){
        minionGO = new GameObject();
        minionInitialArc = i*2*PI/nMinions;
        minion = new Minion(*minionGO, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated), (float)minionInitialArc);

        minionGO->AddComponent(minion);

        minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(minionGO));
    }
}

void Alien::Update(float dt) {
    if(hp <= 0){
        associated.RequestDelete();

        auto explosionGO = new GameObject();
        auto explosionSound = new Sound(*explosionGO, "./assets/audio/boom.wav");
        explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/aliendeath.png", 4, 0.1, 0.4));
        explosionGO->AddComponent(explosionSound);
        explosionSound->Play();
        explosionGO->box.PlaceCenterAt(associated.box.Center());
        Game::GetInstance().GetCurrentState().AddObject(explosionGO);

        return;
    }

    associated.angleDeg += ALIEN_ANGULAR_SPEED * dt;

    if(PenguinBody::player){
        if(state == RESTING && restTimer.Get() < ALIEN_RESTING_TIME){
            restTimer.Update(dt);
        }
        else if(state == RESTING){
            destination = PenguinBody::player->GetCenter();

            speed = {1, 0};
            speed = speed.Rotate(destination.InclinationOfDifference(associated.box.Center()));

            state = MOVING;
        }
        else if(state == MOVING && destination.Distance(associated.box.Center()) <= ALIEN_SPEED*dt){
            associated.box.PlaceCenterAt(destination);

            destination = PenguinBody::player->GetCenter();

            if(nMinions > 0){
                auto closestMinionGO = minionArray[0].lock();
                auto minionGO = closestMinionGO;

                for(int i = 1; i < nMinions; i++){
                    minionGO = minionArray[i].lock();
                    if(closestMinionGO.get() && minionGO.get()){ // verifica se os dois shared_ptrs estao preenchidos antes de mais nada
                        closestMinionGO = (destination.Distance({minionGO->box.x,minionGO->box.y}) <
                                           destination.Distance({closestMinionGO->box.x,closestMinionGO->box.y})) ? minionGO : closestMinionGO;
                    }
                }

                auto closestMinion = (Minion*) closestMinionGO->GetComponent("Minion");
                closestMinion->Shoot(destination);
            }

            restTimer.Restart();

            state = RESTING;
        }
        else if(state == MOVING){
            associated.box += speed*ALIEN_SPEED*dt;
        }
    }
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return type == "Alien";
}

void Alien::NotifyCollision(GameObject &other) {
    auto bullet = (Bullet*) other.GetComponent("Bullet");
    if(bullet && !bullet->targetsPlayer){
        hp -= bullet->GetDamage();
    }
}