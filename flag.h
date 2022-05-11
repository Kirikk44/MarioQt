#ifndef FLAG_H
#define FLAG_H

#include <QGraphicsItem>
#include <QLabel>

class FlagItem : public QGraphicsItem
{
public:
    FlagItem(int x, int y);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    QPixmap pixmap;

};

#endif // FLAG_H
