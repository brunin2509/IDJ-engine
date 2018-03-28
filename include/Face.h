//
// Created by bruno on 28/03/18.
//

#ifndef INC_140017658_IDJ_FACE_H
#define INC_140017658_IDJ_FACE_H


#include "Component.h"

class Face : public Component {
public:
    explicit Face(GameObject& associated);

    void Damage(int damage);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
    int hitpoints;
};


#endif //INC_140017658_IDJ_FACE_H
