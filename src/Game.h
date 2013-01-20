#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "GameState.h"
#include "GameState_Init.h"

#include "InputHandler.h"
#include "Stack.h"

#include <SFML/System.hpp>

class Game
{
    private:
        Window* mWindow;

        Stack<GameState> mGameStates;

        // Purpose: Updates the game
        void Update();

        // Purpose: Draws the game
        void Draw();

    public:
        Game();
        ~Game();

        // Purpose: Runs the game
        void Run();
};

#endif
