//
// Created by bruno on 23/04/18.
//

#include "Timer.h"

Timer::Timer(): time(0){
}

Timer::Timer(float time): time(time) {
}

void Timer::Update(float dt) {
    time += dt;
}

void Timer::Restart() {
    time = 0;
}

float Timer::Get() {
    return time;
}

