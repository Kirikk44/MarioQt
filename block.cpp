#include <QPainter>
#include <QDebug>

#include "block.h"

Block::Block(int x, int y, char c)
{
    setPos(x, y);
    if (c == 'd')
    {
        frame_x = 0;
        frame_y = 0;
    }else if (c == 'b')
    {
        frame_x = 34;
        frame_y = 34;
    }
    else if (c == 'o')
    {
        frame_x = 0;
        frame_y = 119;
    }
    else if (c == 'O')
    {
        frame_x = 0;
        frame_y = 136;
    }
    else if (c == 'p')
    {
        frame_x = 17;
        frame_y = 119;
    }
    else if (c == 'P')
    {
        frame_x = 17;
        frame_y = 136;
    }
    else if (c == 'i')
    {
        frame_x = 34;
        frame_y = 119;
    }
    else if (c == 'I')
    {
        frame_x = 34;
        frame_y = 136;
    }
}


QRectF Block::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, 50, 50, *pix_png, frame_x, frame_y, 15, 15);
}

bool Block::is_passing()
{
    return passing;
}

void Block::setImage(QPixmap *pix)
{
    pix_png = pix;
}
