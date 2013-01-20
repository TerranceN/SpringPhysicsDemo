#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Window : public sf::Window
{
    public:
        Window();
        Window(sf::VideoMode Mode, const std::string &Title, unsigned long WindowStyle=sf::Style::Resize|sf::Style::Close, const sf::WindowSettings &Params=sf::WindowSettings());
        Window(sf::WindowHandle Handle, const sf::WindowSettings &Params=sf::WindowSettings());

        void SetFramerateLimit(unsigned int newFramerate);
        float GetDeltaTime();
        void SetMaximumTimeInterval(float interval);
        void Update();

    private:
        float maxDeltaTime;
        float updateTime;
        float lastUpdateTime;
        sf::Clock timer;
};

#endif
