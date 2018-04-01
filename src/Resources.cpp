//
// Created by bruno on 01/04/18.
//

#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

using std::cerr;

SDL_Texture *Resources::GetImage(std::string file) {
    auto search = imageTable.find(file);

    if(search != imageTable.end()){ // if the image is found...
        return search->second;
    }
    else{ // if the image is NOT found...
        auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

        if(!texture){
            cerr << "IMG_LoadTexture RETURNED ERROR: " << SDL_GetError();
            exit(1);
        }

        imageTable[file] = texture;

        return texture;
    }
}

void Resources::ClearImages() {
    for(auto it : imageTable){
        SDL_DestroyTexture(it.second);
    }

    imageTable.clear();
}

Mix_Music *Resources::GetMusic(std::string file) {
    auto search = musicTable.find(file);

    if(search != musicTable.end()){ // if the music is found...
        return search->second;
    }
    else{ // if the music is NOT found...
        auto music = Mix_LoadMUS(file.c_str());

        if(!music){
            std::cerr << "Mix_LoadMUS RETURNED ERROR: " << Mix_GetError();
            exit(1);
        }

        musicTable[file] = music;

        return music;
    }
}

void Resources::ClearMusics() {
    for(auto it : musicTable){
        Mix_FreeMusic(it.second);
    }

    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file) {
    auto search = soundTable.find(file);

    if(search != soundTable.end()){ // if the sound is found...
        return search->second;
    }
    else{ // if the sound is NOT found...
        auto sound = Mix_LoadWAV(file.c_str());

        if(!sound){
            cerr << "IMG_LoadTexture RETURNED ERROR: " << Mix_GetError();
            exit(1);
        }

        soundTable[file] = sound;

        return sound;
    }
}

void Resources::ClearSounds() {
    for(auto it : soundTable){
        Mix_FreeChunk(it.second);
    }

    soundTable.clear();
}
