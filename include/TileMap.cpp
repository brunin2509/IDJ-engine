//
// Created by bruno on 30/03/18.
//

#include "../src/TileMap.h"

using std::cerr;

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component(associated) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(std::string file) {
    //todo (chatao)
}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
    if(x >= mapWidth || y >= mapHeight || z >= mapDepth){
        cerr << "ONE ORE MORE INDEXES FOR THE TILE MAP ARE NOT VALID. \n";
        exit(1);
    }

    return tileMatrix[z*mapWidth*mapHeight + y*mapWidth + x];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for(int y = 0; y < mapHeight; y++){
        for(int x = 0; x < mapWidth; x++){
            tileSet->RenderTile((unsigned) At(x, y, layer), x*tileSet->GetTileWidth(), y*tileSet->GetTileHeight());
        }
    }
}

void TileMap::Render() {
    for(int i = 0; i < mapDepth; i++){
        RenderLayer(i, (int) associated.box.x, (int) associated.box.y)
    }
}

void TileMap::Update(float dt) {
    //empty
}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}


