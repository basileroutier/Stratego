#include "mainwindow.h"
#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    stratego::Game game{}; //Model

    uiController controller{game};
    MainWindow w{controller};
    game.addObserver(&w);


    w.show();

    return a.exec();
}
