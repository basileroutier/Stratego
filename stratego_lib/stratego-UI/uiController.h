#ifndef UICONTROLLER_H
#define UICONTROLLER_H
#include "game.h"
#include <optional>
#endif // UICONTROLLER_H

using namespace stratego;

/**
 * @brief The uiController class
 * This class is the controller for the UI
 */
class uiController{
    private:
        stratego::Game & _game;

    public:
        explicit uiController(stratego::Game & game);



        /**
         * play the game, it will called model.play()e
         * @brief play
         */
        void play(std::optional<Position> position, std::optional<int> numberOfMoveDirection);

        /**
         * @brief reverseDebugMode
         * Called the reverseDebugMode method of the game.
         */
        void reverseDebugMode();

        /**
         * Shuffle order of piece in the game
         * @brief shufflePieces
         */
        void shufflePieces();

     private:
        /**
         * This method start the app. It must be called by the main file
         * @brief start
         */
        void start(int nbFile);
};
