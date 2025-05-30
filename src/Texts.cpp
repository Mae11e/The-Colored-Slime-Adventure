/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** Texts.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createText(SceneState scene, std::string name, std::string fontPath, std::string text, sf::Vector2f position, unsigned int size)
{
    _texts[scene][name].font.loadFromFile(fontPath);
    _texts[scene][name].text.setFont(_texts[scene][name].font);
    _texts[scene][name].text.setString(text);
    _texts[scene][name].text.setCharacterSize(size);
    _texts[scene][name].text.setPosition(position);
}

void GraphicalInterface::GraphicalInterface::DrawText()
{
    for (const auto &text : _texts[_currentScene]) {
        _window.draw(text.second.text);
    }
}