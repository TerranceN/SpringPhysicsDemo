#ifndef GAMESTATE_INIT_H
#define GAMESTATE_INIT_H

#include "GameState.h"
#include "GameState_Game.h"
#include "Window.h"

class GameState_Init : public GameState
{
    public:
        GameState_Init(Window* newWindow);
        virtual void Update();
        virtual void Draw();
};

#endif
