#ifndef GAME_STATE_MAIN_H
#define GAME_STATE_MAIN_H

#include "GameState.h"
#include "InputHandler.h"
#include "Vector2.h"
#include "Matrix4.h"
#include "Camera.h"
#include "LinkedList.h"
#include "SharedPointer.h"
#include "PhysicsPoint.h"
#include "Spring.h"
#include "Player.h"
#include "Level.h"

#include "Window.h"

class GameState_Game : public GameState
{
    public:
        GameState_Game(Window* newWindow);
        virtual ~GameState_Game();

        virtual void HandleEvent(const sf::Event& event);

        virtual void Update();
        virtual void Draw();
    private:
        Camera camera;

        SharedPointer<Level> level;
        SharedPointer<Player> player;
};

#endif
