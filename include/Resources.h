//
// Created by bruno on 30/03/18.
//

#ifndef INC_140017658_IDJ_RESOURCES_H
#define INC_140017658_IDJ_RESOURCES_H


#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>

class Resources {
public:
    SDL_Texture* GetImage(std::string file);
    void ClearImages();
    Mix_Music* GetMusic(std::string file);
    void ClearMusics();
    Mix_Chunk* GetSound(std::string file);
    void ClearSounds();

private:
    std::unordered_map<std::string, SDL_Texture*> imageTable;
    std::unordered_map<std::string, Mix_Music*> musicTable;
    std::unordered_map<std::string, Mix_Chunk*> soundTable;
};


#endif //INC_140017658_IDJ_RESOURCES_H
