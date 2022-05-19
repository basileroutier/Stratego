#include "uicell.h"

#include <cmath>

#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

UiCell::UiCell(double x, double y,
                     Position value,
                     double width, double heigth, QColor color, bool isSelectedCell,
                     QGraphicsRectItem * parent)
    : QGraphicsRectItem (parent),
      _x { x }, _y { y },
      _width { width},
      _heigth{heigth},
      _position{value},
      _color{color},
      _isSelectedCell{isSelectedCell}
{

    QRectF rect(_x, _y, width,heigth);
    setRect(rect);
}


void UiCell::paint(
    QPainter * painter,
    [[maybe_unused]] const QStyleOptionGraphicsItem * option,
    [[maybe_unused]] QWidget * widget)
{
    if(_isSelectedCell){
        QPen pen(QColor{194, 8, 8}, 5);
        painter->setPen(pen);
    }
    QBrush brush;
    brush.setColor(_color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect());
}

void UiCell::setBorder(bool border)
{
    _isSelectedCell = border;
    QGraphicsRectItem::update();
}


void UiCell::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    event->accept();
    /*
     * #2 when componant is clicked, emit signal for who listen
     * (a slot elsewhere)
     */
    emit sendValue(_position);
}


