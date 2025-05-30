/*
** EPITECH PROJECT, 2024
** sfml-template [WSL: Ubuntu]
** File description:
** create.cpp
*/

#include "../../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createGameScene()
{
    _scene_events[SceneState::GAME] = std::bind(&GraphicalInterface::GraphicalInterface::events_Game, this, std::placeholders::_1);
    _scene_updates[SceneState::GAME] = std::bind(&GraphicalInterface::GraphicalInterface::updates_Game, this);
    _scene_draws[SceneState::GAME] = std::bind(&GraphicalInterface::GraphicalInterface::draws_Game, this);

    // PLAYER
    _playerposition = {740, 273};
    _currentPlayerState = PlayerState::STAND_BY;
    _currentPlayerColor = PlayerColor::PURPLE;

    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::STAND_BY, "assets/game/Player/sleepy_purple.png", 0.2, {32, 30}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::WALKING_FRONT, "assets/game/Player/down_purple.png", 0.2, {32, 32}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::WALKING_BACK, "assets/game/Player/up_purple.png", 0.2, {32, 35}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::WALKING_LEFT, "assets/game/Player/left_purple.png", 0.2, {32, 35}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::WALKING_RIGHT, "assets/game/Player/right_purple.png", 0.2, {32, 35}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::JUMP, "assets/game/Player/jump_purple.png", 0.1, {32.4, 35}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::ASPI, "assets/game/Player/aspi_purple.png", 0.1, {32, 32}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::OVERLOAD, "assets/game/Player/ouch2_purple.png", 0.2, {32, 35}, _playerposition, {1.2, 1.2});
    createPlayerAnimation(PlayerColor::PURPLE, PlayerState::HURT, "assets/game/Player/ouch_purple.png", 0.2, {32, 35}, _playerposition, {1.2, 1.2});

    // PLANTS
    _nbofeach[PlayerColor::PURPLE] = 1;
    _nbofeach[PlayerColor::GREEN] = 0;
    _nbofeach[PlayerColor::YELLOW] = 0;
    _nbofeach[PlayerColor::NONE] = 0;

    createSprite(SceneState::GAME, "green", "assets/game/Points/green_points.png", {48, 48}, {1, 1});
    createSprite(SceneState::GAME, "orange", "assets/game/Points/orange_points.png", {48, 48}, {1, 1});
    createSprite(SceneState::GAME, "pink", "assets/game/Points/pink_points.png", {48, 48}, {1, 1});
    createSprite(SceneState::GAME, "coins", "assets/game/Points/coins.png", {48, 48}, {1, 1});

    createText(SceneState::GAME, "green", "assets/PixelOperator8.ttf", "0", {48, 48}, 15);
    createText(SceneState::GAME, "orange", "assets/PixelOperator8.ttf", "0", {48, 48}, 15);
    createText(SceneState::GAME, "pink", "assets/PixelOperator8.ttf", "0", {48, 48}, 15);
    createText(SceneState::GAME, "coins", "assets/PixelOperator8.ttf", "0", {48, 48}, 15);
}

void GraphicalInterface::GraphicalInterface::events_Game(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        _window.setView(sf::View(sf::FloatRect(0, 0, _resolution.first, _resolution.second)));
        _currentScene = SceneState::LEVELS;
    }
    PlayerAnimationEventHandler(event);
    // std::cout << "player position :" << _playerposition.x << ", " << _playerposition.y << std::endl;
}

void GraphicalInterface::GraphicalInterface::updates_Game()
{
    UpdatePlayerAnimation();
    _player_animations[_currentPlayerColor][_currentPlayerState].sprite.setPosition(_playerposition);

    _texts[SceneState::GAME]["green"].text.setString(std::to_string(_nbofeach[GREEN]));
    _texts[SceneState::GAME]["orange"].text.setString(std::to_string(_nbofeach[YELLOW]));
    _texts[SceneState::GAME]["pink"].text.setString(std::to_string(_nbofeach[PURPLE]));
    _texts[SceneState::GAME]["coins"].text.setString(std::to_string(_nbofeach[NONE]));

    _texts[SceneState::GAME]["green"].text.setPosition({_playerposition.x - 45, _playerposition.y - 80});
    _texts[SceneState::GAME]["orange"].text.setPosition({_playerposition.x - 5, _playerposition.y - 80});
    _texts[SceneState::GAME]["pink"].text.setPosition({_playerposition.x + 35, _playerposition.y - 80});
    _texts[SceneState::GAME]["coins"].text.setPosition({_playerposition.x + 75, _playerposition.y - 80});
    _sprites[SceneState::GAME]["green"].sprite.setPosition({_playerposition.x - 60, _playerposition.y - 80});
    _sprites[SceneState::GAME]["orange"].sprite.setPosition({_playerposition.x - 20, _playerposition.y - 80});
    _sprites[SceneState::GAME]["pink"].sprite.setPosition({_playerposition.x + 20, _playerposition.y - 80});
    _sprites[SceneState::GAME]["coins"].sprite.setPosition({_playerposition.x + 60, _playerposition.y - 80});

    _window.setView(sf::View(sf::FloatRect(_playerposition.x - 170, _playerposition.y - 80, _resolution.first / 4, _resolution.second / 4)));
}

void GraphicalInterface::GraphicalInterface::draws_Game()
{
    _window.clear(sf::Color(175,237,252));
    for (const auto &sprite : _sprites[_currentScene]) {
            _window.draw(sprite.second.sprite);
    }
    DrawPlayerAnimation();
    DrawText();
}