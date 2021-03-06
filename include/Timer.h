//
// Created by bruno on 23/04/18.
//

#ifndef INC_140017658_IDJ_TIMER_H
#define INC_140017658_IDJ_TIMER_H


class Timer {
public:
    Timer();
    Timer(float time);

    void Update(float dt);
    void Restart();
    float Get();
    void Set(float time);

private:
    float time;
};


#endif //INC_140017658_IDJ_TIMER_H
