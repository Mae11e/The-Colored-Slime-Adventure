/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** Player.cpp
*/

#include "../../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::PlayerAnimationEventHandler(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::S) {
            _playerposition.y += 1;
            _currentPlayerState = PlayerState::WALKING_FRONT;
        } else if (event.key.code == sf::Keyboard::Z) {
             _playerposition.y -= 1;
            _currentPlayerState = PlayerState::WALKING_BACK;
        } else if (event.key.code == sf::Keyboard::Q) {
            _playerposition.x -= 1;
            _currentPlayerState = PlayerState::WALKING_LEFT;
        } else if (event.key.code == sf::Keyboard::D) {
            _playerposition.x += 1;
            _currentPlayerState = PlayerState::WALKING_RIGHT;
        } else if (event.key.code == sf::Keyboard::E)
            _currentPlayerState = PlayerState::ASPI;
        else if (event.key.code == sf::Keyboard::Space)
            _currentPlayerState = PlayerState::JUMP;
    }

    if (event.type == sf::Event::KeyReleased)
        _currentPlayerState = PlayerState::STAND_BY;
}