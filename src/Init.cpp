/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** GraphicalObjects.cpp
*/

#include "../include/GraphicalInterface.hpp"

GraphicalInterface::GraphicalInterface::GraphicalInterface()
{
    _resolution = {1500, 800};
    _window.create(sf::VideoMode(_resolution.first, _resolution.second), "The Colored Slime Adventure");
    _window.setFramerateLimit(60);
    _currentScene = SceneState::BASIC;
}

GraphicalInterface::GraphicalInterface::~GraphicalInterface()
{
}

void GraphicalInterface::GraphicalInterface::createScenes()
{
    _currentScene = SceneState::BASIC;
    createBasicScene();
    createGameScene();
}

void GraphicalInterface::GraphicalInterface::EventHandler()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        
        _scene_events[_currentScene](event);

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _currentScene = SceneState::BASIC;
    }
}

void GraphicalInterface::GraphicalInterface::gameLoop()
{
    createScenes();
    while (_window.isOpen()) {
        EventHandler();
        _scene_updates[_currentScene]();
        _window.clear(sf::Color::Black);
        _scene_draws[_currentScene]();
        _window.display();
    }
}