//
// Created by bruno on 04/04/18.
//

#include <cstring>
#include <iostream>
#include "InputManager.h"

InputManager &InputManager::GetInstance() {
    static InputManager singleton;

    return singleton;
}

InputManager::InputManager() : quitRequested(false), updateCounter(0), mouseX(0), mouseY(0) {
    memset(mouseState, false, sizeof(mouseState));
    memset(mouseUpdate, 0, sizeof(mouseUpdate));
}

InputManager::~InputManager() = default;

void InputManager::Update() {
    SDL_Event event;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // Reseta o quitRequested (se ele foi setado antes e o game nao encerrou,
    // eh porque State deve ter feito algum tratamento especial)
    quitRequested = false;

    // Incrementa o frame
    updateCounter++;

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {

        switch(event.type){
            case SDL_QUIT:
                quitRequested = true;
                //std::cout << "EVENT: SDL_QUIT\n";
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.key.repeat == 0){
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                    //std::cout << "EVENT: SDL_MOUSEBUTTONDOWN\n";
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                //std::cout << "EVENT: SDL_MOUSEBUTTONUP\n";
                break;
            case SDL_KEYDOWN:
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                //std::cout << "EVENT: SDL_KEYDOWN\n";
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                //std::cout << "EVENT: SDL_KEYUP\n";
                break;
            default:break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}


