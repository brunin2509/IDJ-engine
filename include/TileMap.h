//
// Created by bruno on 30/03/18.
//

#ifndef INC_140017658_IDJ_TILEMAP_H
#define INC_140017658_IDJ_TILEMAP_H


#include <Component.h>
#include <vector>
#include <TileSet.h>

class TileMap: public Component {
public:
    TileMap(GameObject &associated, std::string file, TileSet *tileSet);
    ~TileMap();

    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth();

    void Render() override;
    void Update(float dt) override;
    bool Is(std::string type) override;

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth = -1;
    int mapHeight = -1;
    int mapDepth = -1;
};


#endif //INC_140017658_IDJ_TILEMAP_H
