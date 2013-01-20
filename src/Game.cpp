#include "Game.h"
#include <iostream>

Game::Game()
{
    mWindow = new Window(sf::VideoMode(800, 600, 32), "TempWindow", sf::Style::Close);

    mGameStates.Push(new GameState_Init(mWindow));
    mWindow->SetFramerateLimit(1000);
}

Game::~Game()
{
    delete(mWindow);
}

void Game::Run()
{
    sf::Clock c;
    while (mWindow->IsOpened())
    {
        sf::Event event;
        while (mWindow->GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                mWindow->Close();
            }

            if (event.Type == sf::Event::KeyPressed || event.Type == sf::Event::KeyReleased)
            {
                InputHandler::HandleEvent(event);
            }
        }

        if (mGameStates.Peek()->HasNext())
        {
            mGameStates.Push(mGameStates.Peek()->TakeNext());
        }

        if (!mGameStates.Peek()->IsAlive())
        {
            mGameStates.Pop();
        }

        if (!mGameStates.HasNext())
        {
            mWindow->Close();
            break;
        }
        
        mWindow->Update();
        Update();

        if (c.GetElapsedTime() > 1.0 / 60)
        {
            Draw();
            c.Reset();
        }
    }
}

void Game::Update()
{
    mGameStates.Peek()->Update();
}

void Game::Draw()
{
    mGameStates.Peek()->Draw();
    mWindow->Display();
}

