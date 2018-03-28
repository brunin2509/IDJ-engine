//
// Created by bruno on 28/03/18.
//

#ifndef INC_140017658_IDJ_SOUND_H
#define INC_140017658_IDJ_SOUND_H


#include <SDL_mixer.h>
#include "GameObject.h"

class Sound: public Component {
public:
    explicit Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound() override;

    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
    Mix_Chunk* chunk;
    int channel;
};


#endif //INC_140017658_IDJ_SOUND_H
