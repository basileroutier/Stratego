#ifndef UIBOARD_H
#define UIBOARD_H

#include <QWidget>

#include "uicellepiece.h"
#include "game.h"

using namespace stratego;

/**
 * @brief The UiBoard class
 * Manage the board visually
 * This class will update the board, display it and apply signal to buttons
 */
class UiBoard : public QWidget
{
    Q_OBJECT

  private:
    std::vector<UiCellPiece *> _cells;

    /**
     * @brief initializeOneCellOnBoard
     * @param j
     * @param i
     * @param width
     * @param heigth
     * @param color
     * @param nameImage
     * Initialize the cell on the UIBoard
     */
    void initializeOneCellOnBoard(int j, int i, unsigned width, unsigned heigth, QColor color, std::optional<std::string> nameImage);

    /**
     * @brief setSignalToButton
     * give a signal of each button of the board
     */
    auto setSignalToButton();

signals:
    /**
     * @brief resend_value_from_cell
     * @param value
     */
    void resend_value_from_cell(Position value);

  public:
    UiBoard();
    ~UiBoard() = default;

    /**
     * @brief initializeBoard
     * @param game
     * Initialize the UI board
     */
    void initializeBoard(Game &game);

    /**
     * @brief setLayoutBoard
     * set a layout for the board
     */
    void setLayoutBoard();

    /**
     * @brief setBorderToPiece
     * @param pos
     * @param posMax
     * @param isBorder
     * Display a border to a piece
     */
    void setBorderToPiece(Position pos, int posMax, bool isBorder);


    /**
     * @brief updateBoard
     * @param game
     * Update the board visually
     */
    void updateBoard(const Game &game);
};

#endif // UIBOARD_H
