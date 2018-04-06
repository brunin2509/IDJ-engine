//
// Created by bruno on 30/03/18.
//

#include "TileMap.h"
#include <fstream>
#include <Camera.h>

using std::cerr;

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component(associated) {
    Load(file);
    SetTileSet(tileSet);
}

TileMap::~TileMap() {
    delete tileSet;
    tileMatrix.clear();
}

void TileMap::Load(std::string file) {
    std::ifstream tileMapFile;
    std::string line;

    tileMapFile.open("./assets/map/tileMap.txt");

    if(!tileMapFile.is_open()){
        cerr << "tileMap.txt COULD NOT BE OPENED. \n";
        exit(1);
    }

    tileMapFile >> line;
    sscanf(line.c_str(), "%d,%d,%d,", &mapHeight, &mapWidth, &mapDepth);

    if(mapWidth == -1 || mapHeight == -1 || mapDepth == -1){ // if one of these values are STILL -1...
        cerr << "mapHeight, mapWidth OR mapDepth COULD NOT BE READ. \n";
        tileMapFile.close();
        exit(1);
    }

    int tileIndex;
    char comma;

    for(int i = 0; i < mapWidth*mapHeight*mapDepth; i++){
        tileMapFile >> tileIndex;
        tileMapFile >> comma;
        tileMatrix.push_back(tileIndex-1);
    }

    tileMapFile.close();
}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
    if(x >= mapWidth || y >= mapHeight || z >= mapDepth){
        cerr << "ONE ORE MORE POSITIONS FOR THE TILE MAP ARE NOT VALID. \n";
        exit(1);
    }

    return tileMatrix[z*mapWidth*mapHeight + y*mapWidth + x];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for(int y = 0; y < mapHeight; y++){
        for(int x = 0; x < mapWidth; x++){
            tileSet->RenderTile((unsigned) At(x, y, layer), x*tileSet->GetTileWidth() - cameraX, y*tileSet->GetTileHeight() - cameraY);
        }
    }
}

void TileMap::Render() {
    for(int i = 0; i < mapDepth; i++){
        RenderLayer(i, (int) Camera::pos.x, (int) Camera::pos.y);
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


