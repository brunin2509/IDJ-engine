//
// Created by bruno on 30/03/18.
//

#ifndef INC_140017658_IDJ_TILESET_H
#define INC_140017658_IDJ_TILESET_H

#include <iostream>
#include "Sprite.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, std::string file);

    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();

private:
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
};


#endif //INC_140017658_IDJ_TILESET_H
