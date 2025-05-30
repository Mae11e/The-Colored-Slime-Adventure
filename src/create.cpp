/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** create.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createBasicScene()
{
    // createSprite(SceneState::BASIC, "fond", "assets/basic/fond.png", {0,0}, {1.5,1.5});

    createButton(SceneState::BASIC, "start_button", {"assets/basic/play_normal.png", "assets/basic/play_hover.png", "assets/basic/play_normal.png"}, {620, 250}, {1.5, 1.5}, {620, 250}, {895, 308});
    createButton(SceneState::BASIC, "exit_button", {"assets/basic/quit_normal.png", "assets/basic/quit_hover.png", "assets/basic/quit_normal.png"}, {620, 350}, {1.5, 1.5}, {620, 350}, {895, 408});
    
    createAnimation(SceneState::BASIC, "aspi", "assets/game/Player/aspi_purple.png", 0.4, {32, 32}, {730, 450}, {6, 6});
    createAnimation(SceneState::BASIC, "fire", "assets/game/fire.png", 0.2, {20, 24}, {630 ,500}, {6, 6});

    // SCENE ACTIONS
    _scene_events[SceneState::BASIC] = std::bind(&GraphicalInterface::GraphicalInterface::events_Basic, this, std::placeholders::_1);
    _scene_updates[SceneState::BASIC] = std::bind(&GraphicalInterface::GraphicalInterface::updates_Basic, this);
    _scene_draws[SceneState::BASIC] = std::bind(&GraphicalInterface::GraphicalInterface::draws_Basic, this);

    createText(SceneState::BASIC, "The Colored Slime Adventure", "assets/PixelOperator8-Bold.ttf", "The Colored Slime Adventure", {250, 100}, 40);
}

void GraphicalInterface::GraphicalInterface::events_Basic(sf::Event event)
{
    ButtonEventHandler(event);

    if (_buttons[SceneState::BASIC]["start_button"].state == ButtonState::CLICKED) {
        _currentScene = SceneState::GAME;
    } else if (_buttons[SceneState::BASIC]["exit_button"].state == ButtonState::CLICKED) {
        _window.close();
    }   
}

void GraphicalInterface::GraphicalInterface::updates_Basic()
{
    UpdateAnimation();
}

void GraphicalInterface::GraphicalInterface::draws_Basic()
{
    DrawSprite();
    DrawButton();
    DrawAnimation();
    DrawText();
}