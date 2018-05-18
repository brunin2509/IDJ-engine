//
// Created by bruno on 17/05/18.
//

#ifndef INC_140017658_IDJ_TEXT_H
#define INC_140017658_IDJ_TEXT_H

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Component.h"

class Text : public Component {
public:
    enum TextStyle {SOLID, SHADED, BLENDED};

    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float intermittenceSeconds = 0);
    ~Text() override;

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);

    static SDL_Color GetSDLColor(Uint8 a, Uint8 r, Uint8 g, Uint8 b);

private:
    void RemakeTexture();

    std::shared_ptr<TTF_Font> font;
    SDL_Texture* texture;

    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;

    Timer intermittenceCount;
    float intermittenceSeconds;

};


#endif //INC_140017658_IDJ_TEXT_H
