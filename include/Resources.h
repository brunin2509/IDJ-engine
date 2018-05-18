//
// Created by bruno on 01/04/18.
//

#ifndef INC_140017658_IDJ_RESOURCES_H
#define INC_140017658_IDJ_RESOURCES_H

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <iostream>
#include <unordered_map>
#include <memory>

class Resources {
public:
    static std::shared_ptr<SDL_Texture> GetImage(std::string file);
    static void ClearImages();
    static std::shared_ptr<Mix_Music> GetMusic(std::string file);
    static void ClearMusics();
    static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
    static void ClearSounds();
    static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
    static void ClearFonts();

private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
    static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
};


#endif //INC_140017658_IDJ_RESOURCES_H
