#ifndef UICELLEPIECE_H
#define UICELLEPIECE_H


#include "uicell.h"

#include <QDebug>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
/**
 * @brief The GHexacellWithMarble class
 * represent an GHexaCell with on more property:
 * the cell can have a marble on it (colored circle)
 * @see GHexaCell
 */
class UiCellPiece : public UiCell
{
  protected:
    bool _withPiece;
    std::string _imageNamePiece;

  public:
    explicit UiCellPiece(double x, double y,
                                 Position value,
                                 double width=30, double heigth=30, QColor color = Qt::green,
                                 const std::string& imageNamePiece="", bool withPiece = false, bool isSelectedPiece=false,
                                 UiCell * parent = nullptr);
    inline bool withPiece() const;
    inline void withPiece(bool withPiece);
    inline std::string getImageNamePiece() const;
    inline void setImageNamePiece(const std::string& imageNamePiece);
    //inline void setBorderToCell(bool withBorder);
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);
};
#pragma GCC diagnostic pop

/**
 * @brief UiCellPiece::withPiece
 * @return boolean
 * return true if the cell contains a piece otherwise false
 */
bool UiCellPiece::withPiece() const
{
    return _withPiece;
}

/**
 * @brief UiCellPiece::withPiece
 * @param withPiece
 * Setter for withPiece
 */
void UiCellPiece::withPiece(bool withPiece)
{
    _withPiece = withPiece;
    QGraphicsRectItem::update();
}

/**
 * @brief UiCell Piece::getImageNamePiece
 * @return string
 * getter for _imageNamePiece
 */
std::string UiCellPiece::getImageNamePiece() const{
    return _imageNamePiece;
}

/**
 * @brief UiCellPiece::setImageNamePiece
 * @param imageNamePiece
 * setter for imageNamePiece
 */
void UiCellPiece::setImageNamePiece(const std::string &imageNamePiece){
    _imageNamePiece = imageNamePiece;
    QGraphicsRectItem::update();
}




#endif // UICELLEPIECE_H
