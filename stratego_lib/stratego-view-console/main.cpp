#include "game.h"
#include "view.h"
#include "controller.h"

using namespace stratego;

int main()
{
    Game game{};
    View view{game};
    Controller controller{game, view};
    controller.play();
    return 0;
}
