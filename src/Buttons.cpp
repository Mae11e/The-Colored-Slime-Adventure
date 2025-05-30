/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** Buttons.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createButton(SceneState scene, std::string name, std::list<std::string> imagePath, sf::Vector2f position, sf::Vector2f scale, std::pair<double, double> position_up, std::pair<double, double> position_down)
{
    auto it = imagePath.begin();
    for (int i = 0; i < 3; ++i) {
        _buttons[scene][name].texture[i].loadFromFile(*it);
        _buttons[scene][name].sprite[i].setTexture(_buttons[scene][name].texture[i]);
        _buttons[scene][name].sprite[i].setPosition(position);
        _buttons[scene][name].sprite[i].setScale(scale);
        ++it;
    }
    _buttons[scene][name].hitbox_up = position_up;
    _buttons[scene][name].hitbox_down = position_down;
    _buttons[scene][name].state = ButtonState::NORMAL;
}

void GraphicalInterface::GraphicalInterface::DrawButton()
{
    for (const auto &button : _buttons[_currentScene]) {
        _window.draw(button.second.sprite[button.second.state]);
    }
}

void GraphicalInterface::GraphicalInterface::ButtonEventHandler(sf::Event event)
{
    for (auto &button : _buttons[_currentScene]) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        
        if (button.second.hitbox_up.first <= mousePos.x && mousePos.x <= button.second.hitbox_down.first &&
            button.second.hitbox_up.second <= mousePos.y && mousePos.y <= button.second.hitbox_down.second) {
            if (event.type == sf::Event::MouseButtonPressed) {
                button.second.state = ButtonState::CLICKED;
            } else if (event.type == sf::Event::MouseMoved) {
                button.second.state = ButtonState::HOVER;
            }
        } else {
            button.second.state = ButtonState::NORMAL;
        }
    }
}