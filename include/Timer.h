//
// Created by bruno on 23/04/18.
//

#ifndef INC_140017658_IDJ_TIMER_H
#define INC_140017658_IDJ_TIMER_H


class Timer {
public:
    Timer();

    void Update(float dt);
    void Restart();
    float Get();

private:
    float time;
};


#endif //INC_140017658_IDJ_TIMER_H
