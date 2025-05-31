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
        createAnimation(SceneState::GAME, ("fire" + std::to_string(i)), "assets/game/fire.png", 0.2, {20, 24}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.5, 1.5});
    };
    for (int i = 0; purple > i; i++) {
        createAnimation(SceneState::GAME, ("purple_fire" + std::to_string(i)), "assets/game/purple_fire.png", 0.2, {20, 24}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.5, 1.5});
    };
    for (int i = 0; green > i; i++) {
        createAnimation(SceneState::GAME, ("green_fire" + std::to_string(i)), "assets/game/green_fire.png", 0.2, {20, 24}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {1.5, 1.5});
    };
}

void GraphicalInterface::GraphicalInterface::generateEnemy(int yellow, int green, int purple, int zone)
{
    for (int i = 0; yellow > i; i++) {
        createAnimation(SceneState::GAME, ("orange_enemy" + std::to_string(i)), "assets/game/Ennemies/carrot_down.png", 0.2, {32, 30}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
    };
    for (int i = 0; purple > i; i++) {
        createAnimation(SceneState::GAME, ("purple_enemy" + std::to_string(i)), "assets/game/Ennemies/hop_down.png", 0.2, {32, 25}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
    };
    for (int i = 0; green > i; i++) {
        createAnimation(SceneState::GAME, ("green_enemy" + std::to_string(i)), "assets/game/Ennemies/navet_down.png", 0.2, {32, 30}, {static_cast<float>(rand() % zone), static_cast<float>(rand() % zone)}, {0.8, 0.8});
    };
}
