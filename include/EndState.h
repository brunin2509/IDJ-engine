//
// Created by bruno on 18/05/18.
//

#ifndef INC_140017658_IDJ_ENDSTATE_H
#define INC_140017658_IDJ_ENDSTATE_H


#include "State.h"
#include "Music.h"

class EndState : public State {
public:
    EndState();
    ~EndState() override;

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music backgroundMusic;
};


#endif //INC_140017658_IDJ_ENDSTATE_H
