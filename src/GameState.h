#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Window.h"

class GameState
{
    protected:
        Window* mWindow;
        bool mIsAlive;

    private:
        bool mHasNextState;
        GameState* mNextState;

    public:
        GameState(Window* newWindow);
        virtual ~GameState() {}

        bool IsAlive();

        bool HasNext();
        void SetNext(GameState* newState);
        GameState* PeekNext();
        GameState* TakeNext();

        virtual void HandleEvent(const sf::Event& event);

        virtual void UnLoad();
        virtual void Update();
        virtual void Draw();
};

#endif
