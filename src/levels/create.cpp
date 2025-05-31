/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** create.cpp
*/

#include "../../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createLevelsScene()
{
    _scene_events[SceneState::LEVELS] = std::bind(&GraphicalInterface::GraphicalInterface::events_Levels, this, std::placeholders::_1);
    _scene_updates[SceneState::LEVELS] = std::bind(&GraphicalInterface::GraphicalInterface::updates_Levels, this);
    _scene_draws[SceneState::LEVELS] = std::bind(&GraphicalInterface::GraphicalInterface::draws_Levels, this);

    createText(SceneState::LEVELS, "Select One Level Please :)", "assets/PixelOperator8-Bold.ttf", "Select One Level Please :)", {290, 100}, 40);

    createLevelsBox();
    createLevelsText();
}

void GraphicalInterface::GraphicalInterface::createLevelsBox()
{
    float y_max = 600;
    float x_max = 1450;
    float x = 19;
    float y = 200;
    int i = 0;

    while (y < y_max) {
        createButton(SceneState::LEVELS, "box_" + std::to_string(i), {"assets/level_button.png", "assets/level_hover.png", "assets/level_button.png"}, {x, y}, {1, 1}, {x, y}, {x + 99, y + 99});
        x += 122.5;
        if (x >= x_max) {
            y += 122.5;
            x = 19;
        }
        i += 1;
    }
}

void GraphicalInterface::GraphicalInterface::createLevelsText()
{
    float y_max = 700;
    float x_max = 1450;
    float x = 46;
    float y = 250;
    int i = 0;

    while (y_max > y) {
        createText(SceneState::LEVELS, "lv_" + std::to_string(i), "assets/PixelOperator8.ttf", std::to_string(i), {x, y}, 35);
        x += 122.5;
        if (x >= x_max) {
            y+= 122.5;
            x = 46;
        }
        i++;
    }
}

void GraphicalInterface::GraphicalInterface::events_Levels(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        _window.setView(sf::View(sf::FloatRect(0, 0, _resolution.first, _resolution.second)));
        _currentScene = SceneState::BASIC;
    }
    ButtonEventHandler(event);
    if (_buttons[SceneState::LEVELS]["box_0"].state == CLICKED) {
        _menu = 0;
        generateFire(2, 1, 3, 1000);
        generateEnemy(2, 2, 4, 1000);
        generateMap(30, 1000);
        _currentPlayerState = PlayerState::STAND_BY;
        _currentScene = SceneState::GAME;
    }
}

void GraphicalInterface::GraphicalInterface::updates_Levels()
{
    _window.setView(sf::View(sf::FloatRect(0, 0, _resolution.first, _resolution.second)));
}

void GraphicalInterface::GraphicalInterface::draws_Levels()
{
    DrawButton();
    DrawText();
}