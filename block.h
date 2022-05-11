#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>

class Block
        : public QGraphicsItem
{
public:
    Block(int x, int y, char c);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool is_passing();
    void setImage(QPixmap * pix);
private:
    QPixmap *pix_png;
    int frame_x;
    int frame_y;
    bool passing;
};

#endif // BLOCK_H
