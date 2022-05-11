#include <QDebug>
#include <QTimer>
#include <block.h>

#include "characters.h"
#include "mobs.h"
#include "flag.h"

Character::Character()
{

}

Character::Character(QTimer *timer, Map *map, QString path)
{
    tm = timer;
    mp = map;
    mSprites.load(path);
}

Character::Character(QTimer *timer, Map *map)
{
    tm = timer;
    mp = map;
}

Character::Character(QTimer *timer, QString path)
{
    tm = timer;
    mSprites.load(path);
}

Character::Character(QTimer *timer)
{
        tm = timer;
}

Character::Character(Map *map)
{
    mp = map;
}


QRectF Character::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

 void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
 {
     if (status_chr == LEFT)
     {
         QTransform transf;
         transf.translate(width, 0.0);
         transf.scale(-1.0, 1.0);
         painter->setTransform(transf, true);
     }
     painter->drawPixmap(0, 0, width, height, mSprites, current_frame_x, 0, width/3, height/3);
 }

 void Character::setTimer(QTimer *timer)
 {
     tm = timer;
 }

 void Character::setMap(Map *map)
 {
     mp = map;
 }


 void Character::setImage(QString path)
 {
     mSprites.load(path);

 }

 void Character::toEndSlotTimer()
 {

          int flag_intersection_v = 0;

          foreach(QGraphicsItem *item, *mp->getListItem()) // цикл для проверки на пересечения
          {
              if (item == this)
              {
                  continue;
              }

              if (!flag_intersection_v && (this->pos().y() + 45 - speed_fall > item->pos().y() && speed_fall < 0 \
                                           && this->pos().y() < item->pos().y() && this->pos().x() < item->pos().x() + 50 && this->pos().x() + 45 > item->pos().x()))
              {
                  flag_intersection_v = this->pos().y() - item->pos().y();
              }

          }

          moveBy(8, 0);
          if (this->pos().x() >= 1000)
          {
              disconnect(tm, &QTimer::timeout, this, &Character::toEndSlotTimer);
              emit NextLvlSignal();
              return;
          }
          if (/* проверка на полёт*/ flag_intersection_v != 0)
          {
              if (current_frame_x < 240 || current_frame_x >= 315 ) {current_frame_x = 240;}
              current_frame_x += 31;
              if (current_frame_x >= 315 ) current_frame_x = 240;
          }
          this->update();

          if (flag_intersection_v != -45) // если не стоит на блоке
          {
              if (speed_fall > 0)
                  {
                      speed_fall  = 0;
                  }
                  if (flag_intersection_v < 0) // если препятствие снизу
                  {
                      this->moveBy(0, -45 - flag_intersection_v);
                  }
                  else
                  {
                      this->moveBy(0, - speed_fall);
                  }
                  speed_fall--;
          }
          else
          {
              speed_fall = 0;
          }

 }


 void Character::SlotTimer()
 {

     // 1.  возможно стоит поменять проверку на клавиши(сделать как в змейке в питоне)
     intersection_h = 0; // 0 - нет пересечений; другое число - количество на которое нужно сдвинуть все элемнты
     intersection_v = 0;
     Mobs *mob = nullptr;
     mp->getListItem()->clear();
     mp->getListItem()->append((scene()->items()));

     foreach(QGraphicsItem *item, *mp->getListItem()) // цикл для проверки на пересечения
     {
         if (item == this)
         {
             continue;
         }
         qDebug() << typeid (*item).name();
         if (dynamic_cast<Mobs *>(item))
         {
             qDebug() << typeid (item).name();
             qDebug() << typeid (*item).name();

             mob = dynamic_cast<Mobs *>(item);
             if (mob && speed_fall < -1 && collidesWithItem(mob)  && !mob->isDeathMob())
             {
                 // вызвать смерть моба
                 this->moveBy(0, -40);
                 speed_fall = 20;
                 mob->DeathMob();
                 return;
             }
             else
             if (mob && speed_fall >= 0 && collidesWithItem(mob) && !mob->isDeathMob())
             {
                 emit DeathCharacterSignal();
                 return;
             }
             continue;
         }

         if (dynamic_cast<FlagItem *>(item))
         {
             if (this->x() + 30 >= item->pos().x())
             {
                 //запустить конец мира
                 connect(tm, &QTimer::timeout, this, &Character::toEndSlotTimer);
                 disconnect(tm, &QTimer::timeout, this, &Character::SlotTimer);
             }
         }

         // 45 - размеры Марио; 50 - размеры блока, 8 - длина шага
         if (!intersection_h && (dynamic_cast<Block*>(item))\
                 && ((this->pos().x() + 45 + 8  > item->pos().x() && item->pos().y() < this->pos().y() + 45 && item->pos().y() + 50 > this->pos().y() && this->pos().x() < item->pos().x())\
                || (this->pos().x() - 8 < item->pos().x() + 50 && item->pos().y() < this->pos().y() + 45 && item->pos().y() + 50 > this->pos().y() && this->pos().x() > item->pos().x())))
         {
             intersection_h = this->pos().x() - item->pos().x();
         }

         if (!intersection_v && (dynamic_cast<Block*>(item)) &&
                 ((this->pos().y() - speed_fall < item->pos().y() + 50 && speed_fall > 0 && this->pos().y() > item->pos().y() && this->pos().x() < item->pos().x() + 50 && this->pos().x() + 45 > item->pos().x())\
                                      || (this->pos().y() + 45 - speed_fall > item->pos().y() && speed_fall < 0 && this->pos().y() < item->pos().y() && this->pos().x() < item->pos().x() + 50 && this->pos().x() + 45 > item->pos().x() )))
         {
             intersection_v = this->pos().y() - item->pos().y();
         }

     }


    if(GetAsyncKeyState(VK_LEFT))
    {
        status_chr = LEFT;
        if ( intersection_v != 0) /* проверка на полёт*/
        {
            if (current_frame_x < 240 || current_frame_x >= 315 ) {current_frame_x = 240;}
            current_frame_x += 31;
            if (current_frame_x >= 315 ) current_frame_x = 240;
            this->update();
        }

        if (intersection_h > 0)
        {
            this->moveBy(50 - intersection_h, 0);
        }
        else
            if (this->pos().x() - 8 < 0)
            {
                this->setPos(0, y());
            }else
            {
                this->moveBy(-8, 0);
            }

    }
    else
        if(GetAsyncKeyState(VK_RIGHT))
        {
            status_chr = RIGHT;
            if (intersection_v != 0) /* проверка на полёт*/
            {
                if (current_frame_x < 240 || current_frame_x >= 315 ) {current_frame_x = 240;}
                current_frame_x += 31;
                if (current_frame_x >= 315 ) current_frame_x = 240;
            }
            this->update();
            if (this->pos().x() < 250 || mp->isEnd()) // услови на то, что нужно двигать карту или персонажа
            { // двигаем персонажа

                if(intersection_h < 0)
                {
                    this->moveBy(-45 - intersection_h, 0);
                }
                else
                {
                    if (this->pos().x() + 8 > 1000)
                        this->setPos(1000, y());
                    else
                        this->moveBy(8, 0);
                }
            }
            else
            { // двигаем карту
                int max_cord = 300;

                if (intersection_h < 0)
                {
                    foreach(QGraphicsItem *item, *mp->getListItem()) // цикл для перемещения всей карты
                    {
                        if (item == this)
                        {
                            continue;
                        }

                        item->moveBy(45 + intersection_h, 0);

                        if (item->pos().x()+50 < 0)
                        {
                            delete item;
                            continue;
                        }

                        if (item->pos().x() > max_cord) // проверка на необходимость добавить блоки
                        {
                            max_cord = item->pos().x();
                        }
                    }
                }
                else
                {
                    foreach(QGraphicsItem *item, *mp->getListItem()) // цикл для перемещения всей карты
                    {
                        if (item == this)
                        {
                            continue;
                        }

                        item->moveBy(-8, 0);

                        if (item->pos().x()+50 < 0)
                        {
                            delete item;
                            continue;
                        }

                        if (item->pos().x() > max_cord) // проверка на необходимость добавить блоки
                        {
                            max_cord = item->pos().x();
                        }
                    }
                }
                if (max_cord + 50 - 8 <= 1000) // проверка на необходимость добавить блоки
                {
                   mp->add_items();
                }
            }
        }
        else
        {
            if (current_frame_x != 210 && intersection_v != 0)
            {
                current_frame_x = 210;
                this->update();
            }
        }


    if (intersection_v != -45) // если не стоит на блоке
    {
        if (!GetAsyncKeyState(VK_SPACE) && speed_fall > 0)
            {
                speed_fall  = 0;
            }
            if (intersection_v < 0) // если препядствие снизу
            {
                this->moveBy(0, -45 - intersection_v);
            }
            else
            {
                if (intersection_v > 0 && speed_fall > 0) // если сверху
                {
                    this->moveBy(0, -intersection_v + 50);
                    speed_fall = 0;
                }
                else
                {
                    this->moveBy(0, - speed_fall);
                    if (this->pos().y() > 600)
                        emit DeathCharacterSignal();
                }
            }
            speed_fall--;
    }
    else
    {
        speed_fall = 0;
        if (GetAsyncKeyState(VK_SPACE))
        {
            current_frame_x = 359;
            speed_fall = 20;
            this->moveBy(0, - speed_fall);
        }
    }
}
