#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "game.h"
#include "view.h"
#include <optional>


namespace stratego {

    /**
     * @brief The Controller of the app
     */
    class Controller{

     /**
      * The controller has the model/the view and the number of file to read to initialize the board.
     * @brief model_
     */
    private :
        Game & model_;
        View & view_;
        int nbFile_;

    public:
        /**
         * Constructor
         * @brief Controller
         * @param model
         * @param view
         */
        Controller(Game & model, View & view);

        /**
         * This method start the app. It must be called by the main file
         * @brief start
         */
        void start();

        /**
         * play the game, it will called model.play()e
         * @brief play
         */
        void play();

    };
}
#endif // CONTROLLER_H
