/*
** EPITECH PROJECT, 2024
** owerload [WSL: Ubuntu]
** File description:
** Animations.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createAnimation(SceneState scene, std::string name, std::string imagePath, double speed, sf::Vector2f box_size, sf::Vector2f position, sf::Vector2f scale)
{
    _animations[scene][name].texture.loadFromFile(imagePath);
    _animations[scene][name].sprite.setTexture(_animations[scene][name].texture);
    _animations[scene][name].sprite.setPosition(position);
    _animations[scene][name].sprite.setScale(scale);
    _animations[scene][name].box_size = box_size;
    _animations[scene][name].speed = speed;

    for (int i = 0; i < _animations[scene][name].texture.getSize().x / box_size.x; ++i) {
        _animations[scene][name].frames.push_back(std::to_string(i));
    }
    _animations[scene][name].currentFrame = _animations[_currentScene][name].frames.begin();
}

void GraphicalInterface::GraphicalInterface::DrawAnimation()
{
    for (const auto &anim : _animations[_currentScene]) {
        _window.draw(anim.second.sprite);
    }
}

void GraphicalInterface::GraphicalInterface::UpdateAnimation()
{
    for (const auto &anim : _animations[_currentScene])
        if (_animations[_currentScene][anim.first].clock.getElapsedTime().asSeconds() >= _animations[_currentScene][anim.first].speed) {
            _animations[_currentScene][anim.first].clock.restart();
            _animations[_currentScene][anim.first].sprite.setTextureRect(sf::IntRect(std::stoi(*_animations[_currentScene][anim.first].currentFrame) * _animations[_currentScene][anim.first].box_size.x, 0, _animations[_currentScene][anim.first].box_size.x, _animations[_currentScene][anim.first].box_size.y));
            ++_animations[_currentScene][anim.first].currentFrame;
            if (_animations[_currentScene][anim.first].currentFrame == _animations[_currentScene][anim.first].frames.end()) {
                _animations[_currentScene][anim.first].currentFrame = _animations[_currentScene][anim.first].frames.begin();
            }
        }
}
