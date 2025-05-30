/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** Inputs.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createUserInput(SceneState scene, std::string name, std::string fontPath, sf::Vector2f position, unsigned int size)
{
    _inputs[scene][name].font.loadFromFile(fontPath);
    _inputs[scene][name].text.setFont(_inputs[scene][name].font);
    _inputs[scene][name].text.setString("");
    _inputs[scene][name].text.setCharacterSize(size);
    _inputs[scene][name].text.setPosition(position);
    _inputs[scene][name].hasFocus = false;
    _inputs[scene][name].showCursor = false;
    _inputs[scene][name].input = "";
}

void GraphicalInterface::GraphicalInterface::InputEventHandler(sf::Event event)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto &input : _inputs[_currentScene]) {
            auto sprite = _sprites[_currentScene].find(input.first);
            if (sprite != _sprites[_currentScene].end()) {
                sf::FloatRect bounds = sprite->second.sprite.getGlobalBounds();
                if (bounds.contains(mousePos.x, mousePos.y)) {
                    input.second.hasFocus = true;
                } else {
                    input.second.hasFocus = false;
                }
            }
        }
    }
    
    if (event.type == sf::Event::TextEntered) {
        for (auto &input : _inputs[_currentScene]) {
            if (input.second.hasFocus) {
                if (event.text.unicode == 8) {
                    if (!input.second.input.empty()) {
                        input.second.input.pop_back();
                    }
                } else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                    input.second.input += static_cast<char>(event.text.unicode);
                }
                input.second.text.setString(input.second.input);
                _inputdata[_currentScene][input.first] = input.second.input;
            }
        }
    }
}

void GraphicalInterface::GraphicalInterface::UpdateInputs()
{
    for (auto &input : _inputs[_currentScene]) {
        if (input.second.hasFocus) {
            if (input.second.cursorClock.getElapsedTime().asSeconds() > 0.5f) {
                input.second.showCursor = !input.second.showCursor;
                input.second.cursorClock.restart();
            }
        }
    }
}

void GraphicalInterface::GraphicalInterface::DrawInputs()
{
    for (const auto &input : _inputs[_currentScene]) {
        _window.draw(input.second.text);
        
        if (input.second.hasFocus && input.second.showCursor) {
            sf::Text cursor("|", input.second.font, input.second.text.getCharacterSize());
            cursor.setFillColor(sf::Color::Black);
            cursor.setPosition(input.second.text.getPosition().x + input.second.text.getGlobalBounds().width + 2, input.second.text.getPosition().y);
            _window.draw(cursor);
        }
    }
}