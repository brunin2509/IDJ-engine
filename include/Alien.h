//
// Created by bruno on 07/04/18.
//

#ifndef INC_140017658_IDJ_ALIEN_H
#define INC_140017658_IDJ_ALIEN_H


#include <Component.h>
#include <Vec2.h>
#include <vector>
#include <queue>
#include <memory>

#define ALIEN_SPEED 300 // em pixels/s
#define ALIEN_ANGULAR_SPEED -20 // em graus
#define ALIEN_INITIAL_HP 30

class Alien : public Component{
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
    class Action{
    public:
        enum ActionType {MOVE, SHOOT};
        Action(ActionType type, float x, float y);

        ActionType type;
        float x;
        Vec2 pos;
    };

    Vec2 speed;
    int hp;
    int nMinions;

    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
};


#endif //INC_140017658_IDJ_ALIEN_H
