/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** Sprites.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createSprite(SceneState scene, std::string name, std::string imagePath, sf::Vector2f position, sf::Vector2f scale)
{
    _sprites[scene][name].texture.loadFromFile(imagePath);
    _sprites[scene][name].sprite.setTexture(_sprites[scene][name].texture);
    _sprites[scene][name].sprite.setPosition(position);
    _sprites[scene][name].sprite.setScale(scale);
}

void GraphicalInterface::GraphicalInterface::DrawSprite()
{
    for (const auto &sprite : _sprites[_currentScene]) {
        _window.draw(sprite.second.sprite);
    }
}
