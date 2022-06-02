#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uiboard.h"
#include "uiController.h"
#include "observer.h"

using namespace stratego;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * Apply the visual to the page, and set up some buttons
 */
class MainWindow : public QMainWindow, public stratego::utils::Observer
{
    Q_OBJECT

public:
    explicit MainWindow(uiController controller, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
   * @brief my_on_uiboard_clicked
   * @param value
   * WHen you clicked a button of the board this method will be called, and it will called the method play of the controller by gibing it
   * the position of the button
   */
  void my_on_uiboard_clicked(Position value);

  /**
   * @brief on_startButton_clicked
   * Disable the start button and
   * wHen you clicked on the start button this method will be called, and it will called the method play of the controller
   */
  void on_startButton_clicked();

  /**
   * @brief clearTextError
   * Delete the errors message currently visible
   */

  void clearTextError();

  /**
   * @brief on_debugMode_clicked
   * Called the reversedebugmode method of the uiController
   */
  void on_debugMode_clicked();

  void on_shufflePiece_clicked();

public:
  virtual void update(const stratego::State state, Game &game);
  virtual void update(const std::string &property, const std::string &message, const Game & game);

private:
    Ui::MainWindow *ui;
    UiBoard * _uiBoard;
    uiController _uiController;

};
#endif // MAINWINDOW_H
