//
// Created by bruno on 01/04/18.
//

#ifndef INC_140017658_IDJ_RESOURCES_H
#define INC_140017658_IDJ_RESOURCES_H

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <iostream>
#include <unordered_map>

class Resources {
public:
    static SDL_Texture* GetImage(std::string file);
    static void ClearImages();
    static Mix_Music* GetMusic(std::string file);
    static void ClearMusics();
    static Mix_Chunk* GetSound(std::string file);
    static void ClearSounds();

private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};


#endif //INC_140017658_IDJ_RESOURCES_H