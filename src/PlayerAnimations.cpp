/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** Animations.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createPlayerAnimation(PlayerColor color, PlayerState state, std::string imagePath, double speed, sf::Vector2f box_size, sf::Vector2f position, sf::Vector2f scale)
{
    _player_animations[color][state].texture.loadFromFile(imagePath);
    _player_animations[color][state].sprite.setTexture(_player_animations[color][state].texture);
    _player_animations[color][state].sprite.setPosition(position);
    _player_animations[color][state].sprite.setScale(scale);
    _player_animations[color][state].box_size = box_size;
    _player_animations[color][state].speed = speed;

    for (int i = 0; i < _player_animations[color][state].texture.getSize().x / box_size.x; ++i) {
        _player_animations[color][state].frames.push_back(std::to_string(i));
    }
    _player_animations[color][state].currentFrame = _player_animations[_currentPlayerColor][state].frames.begin();
}

void GraphicalInterface::GraphicalInterface::DrawPlayerAnimation()
{
    if (_player_animations[_currentPlayerColor].find(_currentPlayerState) != _player_animations[_currentPlayerColor].end()) {
        _window.draw(_player_animations[_currentPlayerColor][_currentPlayerState].sprite);
    }
}

void GraphicalInterface::GraphicalInterface::UpdatePlayerAnimation()
{
    if (_player_animations[_currentPlayerColor].find(_currentPlayerState) != _player_animations[_currentPlayerColor].end()) {
        if (_player_animations[_currentPlayerColor][_currentPlayerState].clock.getElapsedTime().asSeconds() >= _player_animations[_currentPlayerColor][_currentPlayerState].speed) {
            _player_animations[_currentPlayerColor][_currentPlayerState].clock.restart();
            _player_animations[_currentPlayerColor][_currentPlayerState].sprite.setTextureRect(sf::IntRect(std::stoi(*_player_animations[_currentPlayerColor][_currentPlayerState].currentFrame) * _player_animations[_currentPlayerColor][_currentPlayerState].box_size.x, 0, _player_animations[_currentPlayerColor][_currentPlayerState].box_size.x, _player_animations[_currentPlayerColor][_currentPlayerState].box_size.y));
            ++_player_animations[_currentPlayerColor][_currentPlayerState].currentFrame;
            if (_player_animations[_currentPlayerColor][_currentPlayerState].currentFrame == _player_animations[_currentPlayerColor][_currentPlayerState].frames.end()) {
                _player_animations[_currentPlayerColor][_currentPlayerState].currentFrame = _player_animations[_currentPlayerColor][_currentPlayerState].frames.begin();
            }
        }
    }
}
