#ifndef MOBS_H
#define MOBS_H

#include <QGraphicsItem>
#include <characters.h>
#include <QObject>
//#include "map.h"

class Mobs : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Mobs(QTimer * timer);

    enum Status{
                LEFT,
                RIGHT
               };

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void SetImage(QString path);

    void setMap(Map *map);

    void DeathMob();

    bool isDeathMob();

public slots:
    void SlotTimerMobs();

private:


    bool flag_revers;
    bool death_mob = false;
    short int status_mb = RIGHT;
    short int intersection_v;

    short int speed_fall{5};

    QTimer * tm;

    Map *mp;

    QPixmap mSprites;

    short int width{35};
    short int height{40};


    short int width_pix{54};
    short int height_pix{80};

    short int current_frame_x{41};
    short int current_frame_y{54};
};

#endif // MOBS_H
