//
// Created by bruno on 07/04/18.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Game.h>
#include "Alien.h"

Alien::Alien(GameObject &associated, int nMinions): Component(associated), speed(0,0), hp(30), nMinions(nMinions) {
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
    auto boxCenter = associated.box.Center();
    Vec2 minionPositioner(MINION_DISTANCE, 0);
    Vec2 minionPosition(0, 0);
    GameObject* minionGO = nullptr;

    for(int i = 0; i < nMinions; i++){
        minionGO = new GameObject();
        minionGO->AddComponent(new Sprite(*minionGO, "./assets/img/minion.png"));

        minionPosition = boxCenter + minionPositioner.Rotate(i*2*PI/nMinions);
        minionGO->box.x = minionPosition.x;
        minionGO->box.y = minionPosition.y;
        minionGO->box.Centralize();

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

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
        taskQueue.push(Action(Action::SHOOT, mouseX + Camera::pos.x, mouseY + Camera::pos.y));
    }
    else if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)){
        taskQueue.push(Action(Action::MOVE, mouseX + Camera::pos.x, mouseY + Camera::pos.y));
    }

    if(!taskQueue.empty()){
        auto task = taskQueue.front();
        if(task.type == Action::MOVE && task.pos.Distance(associated.box.Center()) <= ALIEN_SPEED*dt) {
            associated.box.x = task.pos.x;
            associated.box.y = task.pos.y;
            associated.box.Centralize();

            speed = {0,0};
            taskQueue.pop();
        }
        else if(task.type == Action::MOVE){
            if(speed.x == 0 && speed.y == 0){
                speed = {ALIEN_SPEED*dt, 0};
                speed = speed.Rotate(task.pos.InclinationOfDifference(associated.box.Center()));
            }

            associated.box.x += speed.x;
            associated.box.y += speed.y;
        }
        else if(task.type == Action::SHOOT){
            //todo
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
