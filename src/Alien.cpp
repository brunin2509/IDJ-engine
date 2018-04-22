//
// Created by bruno on 07/04/18.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Game.h>
#include <Minion.h>
#include "Alien.h"

Alien::Alien(GameObject &associated, int nMinions): Component(associated), speed(0,0), hp(ALIEN_INITIAL_HP), nMinions(nMinions) {
    associated.AddComponent(new Sprite(associated, "./assets/img/alien.png"));
}

Alien::~Alien(){
    // nao eh boa pratica desalocar a memoria de um shared_ptr por alguem que possui acesso soh ao weak_ptr,
    // ja que esse ponteiro eh compartilhado. Deixe para o proprio shared_ptr deletar o objeto automaticamente.
    minionArray.clear();
}

void Alien::Start() {
    // WTFFFFFFFFFFF
    //auto game = Game::GetInstance();
    GameObject* minionGO = nullptr;
    Minion* minion = nullptr;
    double minionInitialArc = 0;

    for(int i = 0; i < nMinions; i++){
        minionGO = new GameObject();
        minionInitialArc = i*2*PI/nMinions;
        minion = new Minion(*minionGO, Game::GetInstance().GetState().GetObjectPtr(&associated), (float)minionInitialArc);

        minionGO->AddComponent(minion);

        minionArray.push_back(Game::GetInstance().GetState().AddObject(minionGO));
    }
}

void Alien::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    auto mouseX = inputManager.GetMouseX();
    auto mouseY = inputManager.GetMouseY();

    if(hp <= 0){
        associated.RequestDelete();
        return;
    }

    associated.angleDeg += ALIEN_ANGULAR_SPEED * dt;

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
        taskQueue.push(Action(Action::SHOOT, mouseX + Camera::pos.x, mouseY + Camera::pos.y));
    }
    else if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)){
        taskQueue.push(Action(Action::MOVE, mouseX + Camera::pos.x, mouseY + Camera::pos.y));
    }

    if(!taskQueue.empty()){
        auto task = taskQueue.front();
        if(task.type == Action::MOVE && task.pos.Distance(associated.box.Center()) <= ALIEN_SPEED*dt) {
            associated.box = task.pos;
            associated.box.Centralize();

            speed = {0,0};
            taskQueue.pop();
        }
        else if(task.type == Action::MOVE){
            if(speed.x == 0 && speed.y == 0){
                speed = {ALIEN_SPEED*dt, 0};
                speed = speed.Rotate(task.pos.InclinationOfDifference(associated.box.Center()));
            }

            associated.box += speed;;
        }
        else if(task.type == Action::SHOOT){
            if(nMinions > 0){
                auto closestMinionGO = minionArray[0].lock();
                auto minionGO = closestMinionGO;

                for(int i = 1; i < nMinions; i++){
                    minionGO = minionArray[i].lock();
                    if(closestMinionGO.get() && minionGO.get()){ // verifica se os dois shared_ptrs estao preenchidos antes de mais nada
                        closestMinionGO = (task.pos.Distance({minionGO->box.x,minionGO->box.y}) <
                                           task.pos.Distance({closestMinionGO->box.x,closestMinionGO->box.y})) ? minionGO : closestMinionGO;
                    }
                }

                auto closestMinion = (Minion*) closestMinionGO->GetComponent("Minion");
                closestMinion->Shoot(task.pos);
            }


            taskQueue.pop();
        }

    }
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return type == "Alien";
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) {
    this->type = type;
    pos = {x,y};
}
