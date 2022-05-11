#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QGraphicsItem>
#include <QObject>

#include "characters.h"
#include "mobs.h"


Mobs::Mobs(QTimer * timer)
{
    tm = timer;
}


QRectF Mobs::boundingRect() const
{
    return QRectF(0, 0, width, height);
}


void Mobs::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (status_mb == LEFT)
    {
        QTransform transf;
        transf.translate(35, 0.0);
        transf.scale(-1.0, 1.0);
        painter->setTransform(transf, true);
    }

    painter->drawPixmap(0, 0, width, height, mSprites, current_frame_x, current_frame_y, width_pix, height_pix);
}


void Mobs::SetImage(QString path)
{
    mSprites.load(path);
}


void Mobs::setMap(Map *map)
{
    mp = map;
}

void Mobs::SlotTimerMobs()
{
    if (current_frame_x < 316)
    {
        current_frame_x += 138;
    }
    else
    {
        current_frame_x = 41;
    }

    intersection_v = 0;
    flag_revers = 0;
    mp->getListItem()->clear();
    mp->getListItem()->append((scene()->items()));
    //*(mp->getListItem()) = scene()->items();
    foreach(QGraphicsItem *item, *mp->getListItem()) // цикл для проверки на пересечения
    {
        if (item == this && item->pos().y() >= 550)
        {
            continue;
        }

        if (!flag_revers && (dynamic_cast<Block*>(item)) && (((this->pos().x() + 35 + 4  > item->pos().x() && item->pos().y() < this->pos().y() + 35 && item->pos().y() + 50 > this->pos().y() && this->pos().x() < item->pos().x()))\
                                     || (this->pos().x() - 4 < item->pos().x() + 50 && item->pos().y() < this->pos().y() + 35 && item->pos().y() + 50 > this->pos().y() && this->pos().x() > item->pos().x())))
        {
            flag_revers = 1;
        }

        if (!intersection_v && (dynamic_cast<Block*>(item))
                                     && (this->pos().y() + 40 - speed_fall > item->pos().y() && speed_fall < 0 && this->pos().y() < item->pos().y() && this->pos().x() < item->pos().x() + 50 && this->pos().x() + 40 > item->pos().x() ))
        {
            intersection_v = this->pos().y() - item->pos().y();
        }
    }

    status_mb = (status_mb + flag_revers) % 2;

    if (status_mb)
    {
        this->moveBy(-4, 0);
    }
    else
    {
        this->moveBy(4, 0);
        if (this->pos().x() > 1000)
        {
            delete this;
            return;
        }
    }

    if (intersection_v != -40) // если не стоит на блоке
    {
        speed_fall--;
        if (intersection_v < 0) // если препядствие снизу
        {
            this->moveBy(0, -40 - intersection_v);
        }
        else
        {
            this->moveBy(0, - speed_fall);
            if (this->pos().y() > 600)
            {
                delete this;
            }
        }
    }
    else
    {
        speed_fall = 0;
    }

}


void Mobs::DeathMob()
{
    current_frame_x = 445; // устанавливаются координаты спрайта, соответствующему мертвому мобу
    current_frame_y = 83;
    width_pix = 58;
    height_pix = 44;

    death_mob = 1;

    disconnect(tm, &QTimer::timeout, this, &Mobs::SlotTimerMobs);
    this->update();
}


bool Mobs::isDeathMob()
{
    return  death_mob;
}
