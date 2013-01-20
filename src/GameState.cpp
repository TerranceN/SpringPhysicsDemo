#include "GameState.h"
#include <iostream>

GameState::GameState(Window* newWindow)
{
    mWindow = newWindow;
    mIsAlive = true;
    mHasNextState = false;
}

GameState* GameState::PeekNext()
{
    return mNextState;
}

GameState* GameState::TakeNext()
{
    GameState* returnVal = mNextState;
    mNextState = NULL;
    mHasNextState = false;
    return returnVal;
}

bool GameState::HasNext()
{
    return mHasNextState;
}

void GameState::SetNext(GameState* newState)
{
    mHasNextState = true;
    mNextState = newState;
}

bool GameState::IsAlive()
{
    return mIsAlive;
}

void GameState::HandleEvent(const sf::Event& event)
{
}

void GameState::Draw()
{
}

void GameState::UnLoad()
{
    mIsAlive = false;
}

void GameState::Update()
{
}

