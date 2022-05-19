#include "uicellepiece.h"

#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QBrush>
#include <QPicture>

UiCellPiece::UiCellPiece(double x, double y,
    Position value,
    double width,
    double heigth, QColor color, const std::string &imageNamePiece,
    bool withPiece, bool isSelectedPiece,
    UiCell * parent)
    : UiCell (x*(width/1.985), y*(heigth/1.987), value, width, heigth, color, isSelectedPiece, parent),_withPiece { withPiece }, _imageNamePiece{imageNamePiece}

{}

void UiCellPiece::paint(
    QPainter * painter,
    [[maybe_unused]] const QStyleOptionGraphicsItem * option,
    [[maybe_unused]] QWidget * widget)
{
    UiCell::paint(painter, option, widget);

    if (_withPiece) {
        QString fileName = "../Images/StrategoGame/";
        fileName+=QString::fromStdString(_imageNamePiece)+".png";

        QPixmap pixmap1(fileName);
        painter->drawPixmap(_x+8,_y+4,50,50, pixmap1);
    }
}
