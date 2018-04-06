//
// Created by bruno on 18/03/18.
//

#include <Sound.h>
#include <Face.h>
#include "State.h"
#define PI 3.14159265358979323846

State::State(): music("./assets/audio/stageState.ogg") {
    auto gameObject = new GameObject();

    gameObject->AddComponent(new Sprite(*gameObject, "./assets/img/ocean.jpg"));
    objectArray.emplace_back(gameObject);

    quitRequested = false;
    music.Play();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    Input();

    for (auto &gameObjects : objectArray) {
        gameObjects->Update(dt);
    }

    for (unsigned i = 0; i < objectArray.size(); i++) {
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render() {
    for (auto &gameObjects : objectArray) {
        gameObjects->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}


void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {

        // Se o evento for quit, setar a flag para terminação
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }

        // Se o evento for clique...
        if(event.type == SDL_MOUSEBUTTONDOWN) {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for(long i = objectArray.size() - 1; i >= 0; --i) {
                // Obtem o ponteiro e casta pra Face.
                auto go = (GameObject*) objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
                    Face* face = (Face*)go->GetComponent( "Face" );
                    if ( nullptr != face && !face->Died() ) {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if( event.type == SDL_KEYDOWN ) {
            // Se a tecla for ESC, setar a flag de quit
            if( event.key.keysym.sym == SDLK_ESCAPE ) {
                quitRequested = true;
            }
                // Se não, crie um objeto
            else {
                Vec2 objPos = Vec2( 200, 0 ).Rotate((float)(-PI + PI * (std::rand() % 1001) / 500.0)) + Vec2(mouseX, mouseY );
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY) {
    auto gameObject = new GameObject();

    auto sprite = new Sprite(*gameObject, "./assets/img/penguinface.png");

    gameObject->box.x = mouseX - gameObject->box.w/2;
    gameObject->box.y = mouseY - gameObject->box.h/2;

    auto sound = new Sound(*gameObject, "./assets/audio/boom.wav");

    auto face = new Face(*gameObject);

    gameObject->AddComponent(sprite);
    gameObject->AddComponent(sound);
    gameObject->AddComponent(face);

    objectArray.emplace_back(gameObject);
}



