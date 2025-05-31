/*
** EPITECH PROJECT, 2024
** owerload [WSL: Ubuntu]
** File description:
** Animations.cpp
*/

#include "../include/GraphicalInterface.hpp"

void GraphicalInterface::GraphicalInterface::createAnimation(SceneState scene, std::string name, std::string imagePath, double speed, sf::Vector2f box_size, sf::Vector2f position, sf::Vector2f scale)
{
    if (!_animations[scene][name].texture.loadFromFile(imagePath)) {
        std::cerr << "Erreur: Impossible de charger la texture " << imagePath << std::endl;
        return;
    }
    _animations[scene][name].sprite.setTexture(_animations[scene][name].texture);
    _animations[scene][name].sprite.setPosition(position);
    _animations[scene][name].sprite.setScale(scale);
    _animations[scene][name].box_size = box_size;
    _animations[scene][name].speed = speed;
    int frameCount = static_cast<int>(_animations[scene][name].texture.getSize().x / box_size.x);
    _animations[scene][name].frames.clear();
    
    for (int i = 0; i < frameCount; ++i) {
        _animations[scene][name].frames.push_back(std::to_string(i));
    }
    if (!_animations[scene][name].frames.empty()) {
        _animations[scene][name].currentFrame = _animations[scene][name].frames.begin();
    }
    if (!_animations[scene][name].frames.empty()) {
        _animations[scene][name].sprite.setTextureRect(sf::IntRect(0, 0, 
            static_cast<int>(box_size.x), static_cast<int>(box_size.y)));
    }
}

void GraphicalInterface::GraphicalInterface::DrawAnimation()
{
    if (_animations.find(_currentScene) == _animations.end()) {
        return;
    }
    for (const auto &anim : _animations[_currentScene]) {
        _window.draw(anim.second.sprite);
    }
}

void GraphicalInterface::GraphicalInterface::UpdateAnimation()
{
    if (_animations.find(_currentScene) == _animations.end()) {
        return;
    }
    for (auto &animPair : _animations[_currentScene]) {
        const std::string &animName = animPair.first;
        AnimationObject &anim = animPair.second;
        
        if (anim.frames.empty()) {
            std::cerr << "Attention: Animation '" << animName << "' n'a pas de frames" << std::endl;
            continue;
        }        
        if (anim.currentFrame == anim.frames.end()) {
            std::cerr << "Attention: currentFrame invalide pour '" << animName << "', réinitialisation" << std::endl;
            anim.currentFrame = anim.frames.begin();
        }
        if (anim.clock.getElapsedTime().asSeconds() >= anim.speed) {
            anim.clock.restart();            
            if (anim.currentFrame != anim.frames.end()) {
                try {
                    int frameIndex = std::stoi(*anim.currentFrame);                    
                    int textureX = frameIndex * static_cast<int>(anim.box_size.x);
                    int textureY = 0;
                    int frameWidth = static_cast<int>(anim.box_size.x);
                    int frameHeight = static_cast<int>(anim.box_size.y);
                    
                    if (textureX + frameWidth <= static_cast<int>(anim.texture.getSize().x) &&
                        textureY + frameHeight <= static_cast<int>(anim.texture.getSize().y)) {
                        
                        anim.sprite.setTextureRect(sf::IntRect(textureX, textureY, frameWidth, frameHeight));
                    } else {
                        std::cerr << "Erreur: Frame " << frameIndex << " dépasse les limites de la texture pour '" << animName << "'" << std::endl;
                    }
                    
                } catch (const std::exception &e) {
                    std::cerr << "Erreur lors de la conversion du frame index pour '" << animName << "': " << e.what() << std::endl;
                    continue;
                }
                ++anim.currentFrame;
                if (anim.currentFrame == anim.frames.end()) {
                    anim.currentFrame = anim.frames.begin();
                }
            }
        }
    }
}