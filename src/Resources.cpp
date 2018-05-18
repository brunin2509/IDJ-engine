//
// Created by bruno on 01/04/18.
//

#include "Resources.h"
#include "Game.h"
#include <memory>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;

using std::cerr;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
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

        std::shared_ptr<SDL_Texture> sharedTexture(texture, [] (SDL_Texture *p) -> void {
            SDL_DestroyTexture(p);
        });

        imageTable[file] = sharedTexture;

        return sharedTexture;
    }
}

void Resources::ClearImages() {
    for(auto it = imageTable.begin(); it != imageTable.end();){
        if((it->second).unique()){
            it = imageTable.erase(it);
        }
        else{
            it++;
        }
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
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

        std::shared_ptr<Mix_Music> sharedMusic(music, [] (Mix_Music *p) -> void {
            Mix_FreeMusic(p);
        });

        musicTable[file] = sharedMusic;

        return sharedMusic;
    }
}

void Resources::ClearMusics() {
    for(auto it = musicTable.begin(); it != musicTable.end();){
        if((it->second).unique()){
            it = musicTable.erase(it);
        }
        else{
            it++;
        }
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
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

        std::shared_ptr<Mix_Chunk> sharedSound(sound, [] (Mix_Chunk *p) -> void {
            Mix_FreeChunk(p);
        });

        soundTable[file] = sharedSound;

        return sharedSound;
    }
}

void Resources::ClearSounds() {
    for(auto it = soundTable.begin(); it != soundTable.end();){
        if((it->second).unique()){
            it = soundTable.erase(it);
        }
        else{
            it++;
        }
    }
}
