//
// Created by bruno on 05/04/18.
//

#ifndef INC_140017658_IDJ_CAMERA_H
#define INC_140017658_IDJ_CAMERA_H


#include <GameObject.h>

#define CAMERA_SPEED 300 // em pixels/s

class Camera {
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;

private:
    static GameObject* focus;
};


#endif //INC_140017658_IDJ_CAMERA_H
