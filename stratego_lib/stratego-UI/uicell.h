#ifndef UICELL_H
#define UICELL_H

#include <QGraphicsRectItem>
#include <QObject>
#include "position.h"

/*
 * forward declaration.
 * put include in cpp file not in .h file
 */
class QPainter;
class QPointF;
class QStyleOptionGraphicsItem;
class QGraphicsSceneMouseEvent;

using namespace stratego;

/**
 * @brief The GHexaCell class.
 * represent an hexagon at position x,y and with a "value". this
 * value is emited on click.
 * A cell is a button of the board
 * inherit from QObject to have capability of sending signal.
 */
class UiCell : public QObject, public QGraphicsRectItem
{

    Q_OBJECT

  protected:
    double _x, _y;
    double _width;
    double _heigth;
    Position _position;
  private:
    QColor _color;
    bool _isSelectedCell;

  public:
    explicit UiCell(double x, double y,
                       Position value,
                       double width = 30, double heigth=30, QColor color= Qt::green, bool isSelectedCell=false,
                       QGraphicsRectItem * parent = nullptr);
    /**
     * getters and setters
     *
    **/
    inline double x() const;
    inline double y() const ;
    inline double width() const;
    inline double heigth() const;

    /*
     * Apply a color for each cell / buttons
     */
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    /**
     * @brief setBorder
     * @param border
     * Enable or disable the border of a cell.
     */
    void setBorder(bool border);

  protected:
    /**
     * Capture mouse press event. ghexacell is now clickable.
     * Send a signal with the position of the mouse
     **/
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    /**
     * send a position through a signal.
     *
    **/
  signals:
    void sendValue(Position value);
};


double UiCell::x() const
{
    return _x;
}

double UiCell::y() const
{
    return _y;
}

double UiCell::width() const{
    return _width;
}

double UiCell::heigth() const{
    return _heigth;
}

#endif // UICELL_H
