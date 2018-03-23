//
// Created by bruno on 18/03/18.
//

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
    if(music){
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if(music){
        Mix_PlayMusic(music, times);
    } else{
        cerr << "MUSIC COULD NOT BE PLAYED BECAUSE IT IS NULL";
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Mix_LoadMUS(file.c_str());

    if(!music){
        cerr << "THE MUSIC COULD NOT BE LOADED CORRECTLY";
    }
}

bool Music::IsOpen() {
    return music!= nullptr;
}


