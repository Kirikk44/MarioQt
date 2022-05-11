#include <QPainter>

#include "flag.h"
FlagItem::FlagItem(int x , int y)
{
    setPos(x, y);
    pixmap.load(":/images/flag.png");
}


QRectF FlagItem::boundingRect() const
{
    return QRectF(0, 0, 50, 400);
}

void FlagItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
         painter->drawPixmap(0, 0, 50, 400, pixmap);
}
