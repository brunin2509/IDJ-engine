//
// Created by bruno on 05/04/18.
//

#ifndef INC_140017658_IDJ_CAMERAFOLLOWER_H
#define INC_140017658_IDJ_CAMERAFOLLOWER_H


#include <string>
#include "GameObject.h"

class CameraFollower : public Component{
public:
    explicit CameraFollower(GameObject& go);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
};


#endif //INC_140017658_IDJ_CAMERAFOLLOWER_H
