//
// Created by bruno on 28/03/18.
//

#include <Resources.h>
#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated) {
    chunk = nullptr;
}

Sound::Sound(GameObject &associated, std::string file) : Component(associated) {
    Open(file);
}

Sound::~Sound() {
    Mix_HaltChannel(channel);
};

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times-1);
    if(channel < 0){
        std::cerr << "COULD NOT PLAY SOUND: " << Mix_GetError();
        exit(1);
    }
}

bool Sound::IsPlaying() {
    if(channel < 0){ // no active channel for this component
        return false;
    }
    return Mix_Playing(channel) != 0;
}

void Sound::Stop() {
    if(chunk != nullptr){
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);

    if(!chunk){
        std::cerr << "COULD NOT OPEN SOUND FILE: " << Mix_GetError();
        exit(1);
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {
    //todo?
}

void Sound::Render() {
    //todo?
}

bool Sound::Is(std::string type) {
    return type == "Sound";
}









