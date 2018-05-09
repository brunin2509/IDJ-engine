//
// Created by bruno on 08/05/18.
//

#ifndef INC_140017658_IDJ_STATE_H
#define INC_140017658_IDJ_STATE_H


#include <memory>
#include "GameObject.h"

class State {
public:
    State();
    ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
    virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);

    bool PopRequested();
    bool QuitRequested();

protected:
    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();

    bool popRequested;
    bool quitRequested;
    bool started;

    std::vector<std::shared_ptr<GameObject>> objectArray;
};


#endif //INC_140017658_IDJ_STATE_H
