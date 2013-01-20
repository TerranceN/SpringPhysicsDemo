#include "Window.h"
#include <iostream>

Window::Window() : sf::Window() { maxDeltaTime = 0; }

Window::Window(sf::VideoMode Mode, const std::string &Title, unsigned long WindowStyle, const sf::WindowSettings &Params)
    : sf::Window(Mode, Title, WindowStyle, Params) { maxDeltaTime = 0; }

Window::Window(sf::WindowHandle Handle, const sf::WindowSettings &Params)
    : sf::Window(Handle, Params) { maxDeltaTime = 0; }


float Window::GetDeltaTime()
{
    float delta = lastUpdateTime;

    if (maxDeltaTime > 0 && delta > maxDeltaTime)
    {
        delta = maxDeltaTime;
    }


    return delta;
}

void Window::SetFramerateLimit(unsigned int newFramerate)
{
    updateTime = 1000.0 / newFramerate;
}

void Window::SetMaximumTimeInterval(float interval)
{
    maxDeltaTime = interval;
}

void Window::Update()
{
    lastUpdateTime = timer.GetElapsedTime();
    timer.Reset();
}

