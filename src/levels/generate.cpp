/*
** EPITECH PROJECT, 2024
** owerload [WSL: Ubuntu]
** File description:
** generate.cpp
*/

#include "../../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::generateFire(int yellow, int green, int purple, int zone)
{
    for (int i = 0; yellow > i; i++) {
        createAnimation(SceneState::GAME, ("fire_" + std::to_string(i)), "assets/game/fire.png", 0.2, {20, 24}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.5, 1.5});
    };
    for (int i = 0; purple > i; i++) {
        createAnimation(SceneState::GAME, ("purple_fire_" + std::to_string(i)), "assets/game/purple_fire.png", 0.2, {20, 24}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.5, 1.5});
    };
    for (int i = 0; green > i; i++) {
        createAnimation(SceneState::GAME, ("green_fire_" + std::to_string(i)), "assets/game/green_fire.png", 0.2, {20, 24}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.5, 1.5});
    };
}

void GraphicalInterface::GraphicalInterface::check_fire()
{
    if (_animations.find(_currentScene) == _animations.end())
        return;

    sf::FloatRect playerBounds(_playerposition.x, _playerposition.y, 32, 32);
    std::vector<std::string> animationsToRemove;

    for (const auto &animPair : _animations[_currentScene]) {
        const std::string &animName = animPair.first;
        const AnimationObject &anim = animPair.second;
        if (animName.find("fire") != std::string::npos) {
            sf::FloatRect fireBounds = anim.sprite.getGlobalBounds();
            if (playerBounds.intersects(fireBounds)) {
                animationsToRemove.push_back(animName);
                if (animName.find("purple_fire") != std::string::npos)
                    _nbofeach[PlayerColor::PURPLE]++;
                else if (animName.find("green_fire") != std::string::npos)
                    _nbofeach[PlayerColor::GREEN]++;
                else if (animName.find("fire") != std::string::npos && 
                          animName.find("purple_fire") == std::string::npos && 
                          animName.find("green_fire") == std::string::npos) {
                    _nbofeach[PlayerColor::YELLOW]++;
                }
            }
        }
    }
    for (const std::string &animName : animationsToRemove) _animations[_currentScene].erase(animName);
}

void GraphicalInterface::GraphicalInterface::check_enemies()
{
    if (_animations.find(_currentScene) == _animations.end())
        return;
    
    sf::FloatRect playerBounds(_playerposition.x, _playerposition.y, 32, 32);
    std::vector<std::string> toRemove;
    
    for (const auto &[name, anim] : _animations[_currentScene]) {
        if (name.find("enemy") != std::string::npos && playerBounds.intersects(anim.sprite.getGlobalBounds())) {
            if (name.find("purple_enemy") != std::string::npos && _nbofeach[PlayerColor::PURPLE] > 0 && _currentPlayerColor == PlayerColor::PURPLE) {
                _nbofeach[PlayerColor::PURPLE]--;
                toRemove.push_back(name);
            } else if (name.find("orange_enemy") != std::string::npos && _nbofeach[PlayerColor::YELLOW] > 0 && _currentPlayerColor == PlayerColor::YELLOW) {
                _nbofeach[PlayerColor::YELLOW]--;
                toRemove.push_back(name);
            } else if (name.find("green_enemy") != std::string::npos && _nbofeach[PlayerColor::GREEN] > 0 && _currentPlayerColor == PlayerColor::GREEN) {
                _nbofeach[PlayerColor::GREEN]--;
                toRemove.push_back(name);
            } else
                _currentPlayerState = PlayerState::HURT;
        }
    }
    for (const std::string &name : toRemove) _animations[_currentScene].erase(name);
}

void GraphicalInterface::GraphicalInterface::generateEnemy(int yellow, int green, int purple, int zone)
{
    for (int i = 0; yellow > i; i++) {
        createAnimation(SceneState::GAME, ("orange_enemy" + std::to_string(i)), "assets/game/Ennemies/carrot_down.png", 0.2, {32, 30}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
        auto& enemy = _animations[SceneState::GAME]["orange_enemy" + std::to_string(i)];
        enemy.velocity = {0, 0};
        enemy.isFollowingPlayer = false;
        enemy.detectionRange = 100.0f;
        enemy.moveSpeed = 0.5f;
        enemy.lastRandomDirection = getRandomDirection();
    }
    
    for (int i = 0; purple > i; i++) {
        createAnimation(SceneState::GAME, ("purple_enemy" + std::to_string(i)), "assets/game/Ennemies/hop_down.png", 0.2, {32, 25}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
        auto& enemy = _animations[SceneState::GAME]["purple_enemy" + std::to_string(i)];
        enemy.velocity = {0, 0};
        enemy.isFollowingPlayer = false;
        enemy.detectionRange = 120.0f;
        enemy.moveSpeed = 0.7f;
        enemy.lastRandomDirection = getRandomDirection();
    }
    
    for (int i = 0; green > i; i++) {
        createAnimation(SceneState::GAME, ("green_enemy" + std::to_string(i)), "assets/game/Ennemies/navet_down.png", 0.2, {32, 30}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
        auto& enemy = _animations[SceneState::GAME]["green_enemy" + std::to_string(i)];
        enemy.velocity = {0, 0};
        enemy.isFollowingPlayer = false;
        enemy.detectionRange = 80.0f;
        enemy.moveSpeed = 0.3f;
        enemy.lastRandomDirection = getRandomDirection();
    }
}

void  GraphicalInterface::GraphicalInterface::generateMap(int number, int zone)
{
    int i = rand() % number;
    for (; i > 0; i--) {
        createSprite(SceneState::GAME, ("little_tree_" + std::to_string(i)), "assets/game/map/tiny_tree.png", {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.2, 1.2});
    };
    i = rand() % number;
    for (; i > 0; i--) {
        createSprite(SceneState::GAME, ("big_tree_" + std::to_string(i)), "assets/game/map/big_tree.png", {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.2, 1.2});
    };
    i = rand() % number;
    for (; i > 0; i--) {
        createSprite(SceneState::GAME, ("bush_" + std::to_string(i)), "assets/game/map/bush.png", {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1, 1});
    };
    i = rand() % number;
    for (; i > 0; i--) {
        createSprite(SceneState::GAME, ("blue_flower_" + std::to_string(i)), "assets/game/map/blue_flower.png", {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
    };
    i = rand() % number;
    for (; i > 0; i--) {
        createSprite(SceneState::GAME, ("mush_red_" + std::to_string(i)), "assets/game/map/mush_red.png", {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
    };
    i = rand() % number;
    for (; i > 0; i--) {
        createSprite(SceneState::GAME, ("mush_" + std::to_string(i)), "assets/game/map/mush.png", {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
    };
    i = rand() % number;
    for (; i > 0; i--) {
        createSprite(SceneState::GAME, ("yellow_flower_" + std::to_string(i)), "assets/game/map/yellow_flower.png", {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
    };
}

void GraphicalInterface::GraphicalInterface::UpdateEnemyAI()
{
    if (_animations.find(_currentScene) == _animations.end())
        return;

    for (auto& [name, enemy] : _animations[_currentScene]) {
        if (name.find("enemy") != std::string::npos) {
            if (isPlayerInRange(enemy)) {
                enemy.isFollowingPlayer = true;
                moveEnemyTowardsPlayer(enemy);
            } else {
                enemy.isFollowingPlayer = false;
                moveEnemyRandomly(enemy);
            }
            sf::Vector2f currentPos = enemy.sprite.getPosition();
            enemy.sprite.setPosition(currentPos + enemy.velocity);
        }
    }
}

bool GraphicalInterface::GraphicalInterface::isPlayerInRange(const AnimationObject& enemy)
{
    sf::Vector2f enemyPos = enemy.sprite.getPosition();
    sf::Vector2f playerPos = _playerposition;
    float distance = sqrt(pow(playerPos.x - enemyPos.x, 2) + pow(playerPos.y - enemyPos.y, 2));
    return distance <= enemy.detectionRange;
}

void GraphicalInterface::GraphicalInterface::moveEnemyTowardsPlayer(AnimationObject& enemy)
{
    sf::Vector2f enemyPos = enemy.sprite.getPosition();
    sf::Vector2f playerPos = _playerposition;
    sf::Vector2f direction = playerPos - enemyPos;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }
    enemy.velocity = direction * enemy.moveSpeed;
}

void GraphicalInterface::GraphicalInterface::moveEnemyRandomly(AnimationObject& enemy)
{
    if (enemy.movementClock.getElapsedTime().asSeconds() >= 2.0f) {
        enemy.movementClock.restart();
        enemy.lastRandomDirection = getRandomDirection();
    }
    enemy.velocity = enemy.lastRandomDirection * enemy.moveSpeed * 0.3f;
}

sf::Vector2f GraphicalInterface::GraphicalInterface::getRandomDirection()
{
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
    return sf::Vector2f(cos(angle), sin(angle));
}
