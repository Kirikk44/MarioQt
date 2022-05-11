#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsView>
#include <QPixmap>

#include "map.h"

#include <windows.h>

// попробовать сделать класс сущности - и пронаследовать от него мобов и персонажей
class Character : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Character();
    Character(QTimer * timer, Map *map, QString path);
    Character(QTimer * timer, Map *map);
    Character(QTimer * timer, QString path);
    Character(QTimer * timer);
    Character(Map *map);

    enum Status{
                RIGHT,
                LEFT
               };

     QRectF boundingRect() const override;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setTimer(QTimer * timer);

     void setMap(Map *map);

     void setImage(QString path);

public slots:
     void SlotTimer();
     void toEndSlotTimer();

private:
    short int width{15*3};
    short int height{15*3};

    int intersection_h;
    int intersection_v;

    short int speed_fall{5};

    QTimer * tm;

    Map *mp;

    QPixmap mSprites;
    short int current_frame_x{210};
    short int current_frame_y{0};
    short int status_chr{RIGHT};

    int count_shift = 0;

signals:
    void DeathCharacterSignal();
    void NextLvlSignal();

};

#endif // CHARACTERS_H
