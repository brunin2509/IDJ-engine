//
// Created by bruno on 30/03/18.
//

#include "TileSet.h"

using std::cerr;

TileSet::TileSet(int tileWidth, int tileHeight, std::string file): tileSet(*new GameObject(), file) {
    if(tileSet.IsOpen()){
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
        rows = tileSet.GetHeight() / tileHeight;
        columns = tileSet.GetWidth() / tileWidth;
    }
    else{
        cerr << "TileSet COULD NOT OPEN SPRITE: " << SDL_GetError();
        exit(1);
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if((int) index == -1){ //in case its an empty tile //todo: THIS IS SOOOO SPECIFIC!!
        tileSet.SetClip((columns-1)*tileWidth, (rows-1)*tileHeight, tileHeight, tileHeight);
    }
    else if(index >= (unsigned) rows*columns){ //its not necessary to check whether index < 0, because its unsigned
        cerr << "THE INDEX FOR THE TILE IS NOT VALID. \n";
        exit(1);
    }
    else{
        tileSet.SetClip((index%columns)*tileWidth, (index/columns)*tileHeight, tileHeight, tileHeight);
    }

    tileSet.Render((int) x, (int) y);
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}

