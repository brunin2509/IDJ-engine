//
// Created by bruno on 05/04/18.
//

#include <InputManager.h>
#include <Game.h>
#include "Camera.h"

Vec2 Camera::pos = {0,0};
Vec2 Camera::speed = {0,0};
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus){
        pos.x = focus->box.Center().x - Game::GetInstance().GetWidth()/2;
        pos.y = focus->box.Center().y - Game::GetInstance().GetHeight()/2;
    }
    else{
        // vetor inicial, inclinacao de 0 rad em relacao a x.
        speed = {CAMERA_SPEED*dt, 0};
        auto inputManager = InputManager::GetInstance();
        bool directionBtnPressed = false;

        if(inputManager.IsKeyDown(UP_ARROW_KEY) && inputManager.IsKeyDown(LEFT_ARROW_KEY)){
            speed = speed.Rotate((float)(1.25*PI));
            directionBtnPressed = true;
        }
        else if(inputManager.IsKeyDown(LEFT_ARROW_KEY) && inputManager.IsKeyDown(DOWN_ARROW_KEY)){
            speed = speed.Rotate((float)(0.75*PI));
            directionBtnPressed = true;
        }
        else if(inputManager.IsKeyDown(DOWN_ARROW_KEY) && inputManager.IsKeyDown(RIGHT_ARROW_KEY)){
            speed = speed.Rotate((float)(0.25*PI));
            directionBtnPressed = true;
        }
        else if(inputManager.IsKeyDown(RIGHT_ARROW_KEY) && inputManager.IsKeyDown(UP_ARROW_KEY)){
            speed = speed.Rotate((float)(1.75*PI));
            directionBtnPressed = true;
        }
        else if(inputManager.IsKeyDown(UP_ARROW_KEY)){
            speed = speed.Rotate((float)(1.5*PI));
            directionBtnPressed = true;
        }
        else if(inputManager.IsKeyDown(LEFT_ARROW_KEY)){
            speed = speed.Rotate((float)(PI));
            directionBtnPressed = true;
        }
        else if(inputManager.IsKeyDown(DOWN_ARROW_KEY)){
            speed = speed.Rotate((float)(0.5*PI));
            directionBtnPressed = true;
        }
        else if(inputManager.IsKeyDown(RIGHT_ARROW_KEY)){
            directionBtnPressed = true;
        }

        if(directionBtnPressed){
            pos = pos + speed;
        }
    }
}
