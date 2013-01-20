#include "GameState_Init.h"

GameState_Init::GameState_Init(Window* newWindow) : GameState(newWindow)
{
    // initialize game here, default 2D initialization provided
    sf::VideoMode mode = sf::VideoMode::GetMode(0);
    mode = sf::VideoMode(1280, 720, mode.BitsPerPixel);
    mWindow->Create(sf::VideoMode(mode.Width, mode.Height, mode.BitsPerPixel), "Game Window!", sf::Style::Close, sf::WindowSettings(24, 8, 4));
    mWindow->SetMaximumTimeInterval(0.005);

    glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.9f, 0.f);

    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, mWindow->GetWidth(), mWindow->GetHeight(), 0, 1, -1);

    SetNext(new GameState_Game(mWindow));
}

void GameState_Init::Draw()
{
}

void GameState_Init::Update()
{
    UnLoad();
}

