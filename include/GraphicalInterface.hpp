/*
** EPITECH PROJECT, 2024
** Raytracer [WSL: Ubuntu]
** File description:
** UI.hpp
*/

#ifndef UI_HPP
    #define UI_HPP

    #include <string>
    #include <iostream>
    #include <map>
    #include <list>
    #include <memory>
    #include <SFML/Graphics.hpp>
    #include <functional>
    #include <fstream>

namespace GraphicalInterface {

    enum ButtonState {
        NORMAL,
        HOVER,
        CLICKED
    };

    enum SceneState {
        BASIC,
        GAME,
        GAMEOVER,
        LEVELS,
        END
    };

    enum PlayerState {
        STAND_BY,
        WALKING_FRONT,
        WALKING_BACK,
        WALKING_LEFT,
        WALKING_RIGHT,
        ASPI,
        OVERLOAD,
        JUMP,
        HURT
    };

    enum PlayerColor {
        PURPLE,
        GREEN,
        YELLOW,
        NONE
    };

    struct SpriteObject {
        sf::Texture texture;
        sf::Sprite sprite;
    };

    struct TextObject {
        sf::Font font;
        sf::Text text;
    };

    struct InputObject {
        sf::Font font;
        sf::Text text;
        std::string input;
        bool hasFocus;
        sf::Clock cursorClock;
        bool showCursor;
    };

    struct ButtonObject {
        sf::Texture texture[3];
        sf::Sprite sprite[3];

        ButtonState state;

        std::pair<double, double> hitbox_up;
        std::pair<double, double> hitbox_down;
    };

    struct AnimationObject {
        double speed;
        sf::Vector2f box_size;
        sf::Clock clock;

        sf::Texture texture;
        sf::Sprite sprite;

        std::list<std::string> frames;
        std::list<std::string>::iterator currentFrame;
    };

    class GraphicalInterface {
        private:
            int _menu;
            std::pair<int, int> _resolution;
            sf::RenderWindow _window;
            SceneState _currentScene;
            std::string _actualMap;

            std::map<SceneState, std::map<std::string, ButtonObject>> _buttons;
            std::map<SceneState, std::map<std::string, SpriteObject>> _sprites;
            std::map<SceneState, std::map<std::string, TextObject>> _texts;
            std::map<SceneState, std::map<std::string, InputObject>> _inputs;
            std::map<SceneState, std::map<std::string, AnimationObject>> _animations;

            std::map<SceneState, std::map<std::string, std::string>> _inputdata;

            std::map<SceneState, std::function<void(sf::Event)>> _scene_events;
            std::map<SceneState, std::function<void()>> _scene_updates;
            std::map<SceneState, std::function<void()>> _scene_draws;

            // PLAYER
            sf::Vector2f _playerposition;
            PlayerState _currentPlayerState;
            PlayerColor _currentPlayerColor;
            std::map <PlayerColor, std::map<PlayerState, AnimationObject>> _player_animations;
            std::map <PlayerColor, int> _nbofeach;

        public:
            GraphicalInterface();
            ~GraphicalInterface();

            // MAIN FUNCTIONS
            void createScenes();
            void gameLoop();
            void EventHandler();

            // TEXTS
            void createText(SceneState scene, std::string name, std::string fontPath, std::string text, sf::Vector2f position, unsigned int size);
            void DrawText();

            // SPRITES
            void createSprite(SceneState scene, std::string name, std::string imagePath, sf::Vector2f position, sf::Vector2f scale);
            void DrawSprite();

            // PLAYER ANIMATION SPRITES
            void createPlayerSprite(PlayerState state, std::string imagePath, sf::Vector2f position, sf::Vector2f scale);
            void DrawPlayerSprite();
            void createPlayerAnimation(PlayerColor color, PlayerState state, std::string imagePath, double speed, sf::Vector2f box_size, sf::Vector2f position, sf::Vector2f scale);
            void DrawPlayerAnimation();
            void UpdatePlayerAnimation();
            void PlayerAnimationEventHandler(sf::Event event);

            // ANIMATIONS
            void createAnimation(SceneState scene, std::string name, std::string imagePath, double speed, sf::Vector2f box_size, sf::Vector2f position, sf::Vector2f scale);
            void DrawAnimation();
            void AnimationEventHandler(sf::Event event);
            void UpdateAnimation();

            // BUTTONS
            void createButton(SceneState scene, std::string name, std::list<std::string> imagePath, sf::Vector2f position, sf::Vector2f scale, std::pair<double, double> hitbox_up, std::pair<double, double> hitbox_down);
            void DrawButton();
            void ButtonEventHandler(sf::Event event);

            // INPUTS
            void createUserInput(SceneState scene, std::string name, std::string fontPath, sf::Vector2f position, unsigned int size);
            void DrawInputs();
            void InputEventHandler(sf::Event event);
            void UpdateInputs();
            std::map <std::string, std::string> getInputData(SceneState scene) {return _inputdata[scene];}

            // BASIC SCENE
            void createBasicScene();
            void events_Basic(sf::Event event);
            void updates_Basic();
            void draws_Basic();

            // GAME SCENE
            void createGameScene();
            void events_Game(sf::Event event);
            void updates_Game();
            void draws_Game();

            // LEVELS SCENE
            void createLevelsScene();
            void events_Levels(sf::Event event);
            void updates_Levels();
            void draws_Levels();
            void createLevelsText();
            void createLevelsBox();

            //OTHERS
            void generateMap(int number, int zone);
            void generateFire(int yellow, int green, int purple, int zone);
            void generateEnemy(int yellow, int green, int purple, int zone);
            void check_fire();
            void check_enemies();
    };
};

#endif