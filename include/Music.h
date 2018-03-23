//
// Created by bruno on 18/03/18.
//

#ifndef INC_140017658_T1_MUSIC_H
#define INC_140017658_T1_MUSIC_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>

class Music {
public:
    Music();
    explicit Music(std::string file);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen();

private:
    Mix_Music* music;
};


#endif //INC_140017658_T1_MUSIC_H
