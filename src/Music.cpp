//
// Created by bruno on 18/03/18.
//

#include <Resources.h>
#include "Music.h"

using std::cerr;

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
    Open(file);
}

Music::~Music(){
}

void Music::Play(int times) {
    if(music){
        Mix_PlayMusic(music, times);
    } else{
        cerr << "MUSIC COULD NOT BE PLAYED BECAUSE IT IS NULL";
        exit(1);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);

    if(!music){
        cerr << "COULD NOT OPEN SOUND FILE: " << Mix_GetError();
        exit(1);
    }
}

bool Music::IsOpen() {
    return music!= nullptr;
}


