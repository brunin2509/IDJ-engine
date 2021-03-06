//
// Created by bruno on 28/03/18.
//

#ifndef INC_140017658_IDJ_SOUND_H
#define INC_140017658_IDJ_SOUND_H


#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"

class Sound: public Component {
public:
    explicit Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound() override;

    void Play(int times = 1);
    bool IsPlaying();
    void Stop();
    void Open(std::string file);
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel;
};


#endif //INC_140017658_IDJ_SOUND_H
