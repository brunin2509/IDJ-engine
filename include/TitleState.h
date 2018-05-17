//
// Created by bruno on 11/05/18.
//

#ifndef INC_140017658_IDJ_TITLESTATE_H
#define INC_140017658_IDJ_TITLESTATE_H


#include "State.h"

class TitleState : public State {
public:
    TitleState();
    ~TitleState() override;

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;
};


#endif //INC_140017658_IDJ_TITLESTATE_H
