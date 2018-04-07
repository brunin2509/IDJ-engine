//
// Created by bruno on 18/03/18.
//



#ifndef INC_140017658_T1_STATE_H
#define INC_140017658_T1_STATE_H

#define INCLUDE_SDL
#include <memory>
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"

class State {
public:
    State();
    ~State();

    bool QuitRequested();
    void LoadAssets();
    void Update (float dt);
    void Render();

    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

private:
    void AddObject(int mouseX, int mouseY);

    Music music;
    bool quitRequested;
    std::vector<std::shared_ptr<GameObject>> objectArray;

    bool started;
};


#endif //INC_140017658_T1_STATE_H
