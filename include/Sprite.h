//
// Created by bruno on 18/03/18.
//

#ifndef INC_140017658_T1_SPRITE_H
#define INC_140017658_T1_SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Timer.h"
#include <iostream>

class Sprite: public Component {
public:
    explicit Sprite(GameObject& associated);
    Sprite(GameObject& associated, std::string file, float secondsToSelfDestruct = 0);
    Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct = 0);
    ~Sprite() override;

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Update(float dt) override;
    void Render() override;
    void Render(int x, int y);
    bool Is(std::string type) override;
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);


private:
    std::shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    Timer selfDestructCount;
    float secondsToSelfDestruct;

    void SetClipToNewFrame();
};


#endif //INC_140017658_T1_SPRITE_H
