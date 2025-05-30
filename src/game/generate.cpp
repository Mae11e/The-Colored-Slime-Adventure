/*
** EPITECH PROJECT, 2024
** owerload [WSL: Ubuntu]
** File description:
** generate.cpp
*/

#include "../../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::generateFire(int yellow, int green, int purple)
{
    for (int i = 0; yellow > i; i++) {
        createAnimation(SceneState::GAME, ("fire" + std::to_string(i)), "assets/game/fire.png", 0.2, {20, 24}, {rand() % 1000, rand() % 1000}, {6, 6});
    };
    for (int i = 0; purple > i; i++) {
        createAnimation(SceneState::GAME, ("purple_fire" + std::to_string(i)), "assets/game/purple_fire.png", 0.2, {rand() % 1000, rand() % 1000}, {630 ,500}, {6, 6});
    };
    for (int i = 0; green > i; i++) {
        createAnimation(SceneState::GAME, ("green_fire" + std::to_string(i)), "assets/game/green_fire.png", 0.2, {rand() % 1000, rand() % 1000}, {630 ,500}, {6, 6});
    };
}

void GraphicalInterface::GraphicalInterface::generateEnemy(int yellow, int green, int purple)
{
    for (int i = 0; yellow > i; i++) {
        createAnimation(SceneState::GAME, ("orange_enemy" + std::to_string(i)), "assets/game/orange_enemy.png", 0.2, {20, 24}, {rand() % 1000, rand() % 1000}, {6, 6});
    };
    for (int i = 0; purple > i; i++) {
        createAnimation(SceneState::GAME, ("purple_enemy" + std::to_string(i)), "assets/game/purple_enemy.png", 0.2, {rand() % 1000, rand() % 1000}, {630 ,500}, {6, 6});
    };
    for (int i = 0; green > i; i++) {
        createAnimation(SceneState::GAME, ("green_enemy" + std::to_string(i)), "assets/game/green_enemy.png", 0.2, {rand() % 1000, rand() % 1000}, {630 ,500}, {6, 6});
    };
}
