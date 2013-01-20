#include "GameState_Game.h"

GameState_Game::GameState_Game(Window* newWindow) : GameState(newWindow)
{
    camera.SetTranslationSpeed(6);
    camera.SetScaleSpeed(10);
    camera.ForceScale(0.25);
    camera.SetRotationSpeed(10);

    level = SharedPointer<Level>(new Level());
    player = SharedPointer<Player>(new Player(level));
}

GameState_Game::~GameState_Game()
{
}

void GameState_Game::HandleEvent(const sf::Event& event)
{
    // Handle Events here
}

void GameState_Game::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    {
        camera.Apply();

        level->Draw();

        player->Draw();
    }
    glPopMatrix();
}

void GameState_Game::Update()
{
    if (InputHandler::IsKeyDown(sf::Key::Escape))
    {
        UnLoad();
    }

    if (InputHandler::IsKeyDown(sf::Key::R))
    {
        player.Delete();
        player = SharedPointer<Player>(new Player(level));
    }

    player->Update(mWindow, camera);

    camera.Update(mWindow);
}

