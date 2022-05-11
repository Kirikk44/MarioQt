#include <QPainter>
#include <QDebug>
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>

#include "map.h"
#include "characters.h"
#include "mobs.h"
#include "flag.h"


Map::Map(QGraphicsScene *scene, QTimer *timer, int wd)
{
    if (wd == 1)
        world.open("D:/world1.txt", ios::in);
    else if (wd == 2)
        world.open("D:/world2.txt", ios::in);

    bkgpic.load(":/images/background.png");
    scene_m = scene;
    tm = timer;
    if (!world.is_open()) // TODO: переделать проврку на выдачу ошибки
    {
        return;
    }
    char c;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 12; j >=0; j--)
        {
            c = world.get();

            if (c != ' ' && c != 'm' && c != 'f')
            {
                block = new Block(current_frame_x, current_frame_y, c);
                block->setImage(&bkgpic);
                scene_m->addItem(block);
            }
            if (c == 'm')
            {
                Mobs * mob = new Mobs(tm);
                mob->setPos(current_frame_x, current_frame_y);
                mob->setMap(this);
                connect(tm, &QTimer::timeout, mob, &Mobs::SlotTimerMobs);
                mob->SetImage(":/images/yoshi_battler_rpg_maker_mv_by_retrospriteresources-dac7xms.png");
                scene_m->addItem(mob);
            }

            current_frame_y -= 50;
        }
        current_frame_y = 550;
        current_frame_x += 50;
    }
}


Map::~Map()
{
    world.close();
    list_item = scene_m->items();
    foreach(QGraphicsItem *item, list_item)
    {
        if (! dynamic_cast<Character *>(item))
        {
            delete item;
        }
    }
}


void Map::add_items()
{
    char c;
    while(!world.eof())
    {
        c = world.get();
        if (c == '\n')
        {
            break;
        }

        if (c != ' ' && c != 'm' && c != 'f')
        {
            block = new Block(current_frame_x, current_frame_y, c);
            block->setImage(&bkgpic);
            scene_m->addItem(block);
        }
        else
            if (c == 'm')
            {
                Mobs * mob = new Mobs(tm);
                mob->setPos(current_frame_x, current_frame_y);
                mob->setMap(this);
                connect(tm, &QTimer::timeout, mob, &Mobs::SlotTimerMobs);
                mob->SetImage(":/images/yoshi_battler_rpg_maker_mv_by_retrospriteresources-dac7xms.png");
                scene_m->addItem(mob);
            }
            else
                if (c == 'f')
                {
                    FlagItem * flag_item = new FlagItem(current_frame_x, current_frame_y);
                    scene_m->addItem(flag_item);
                }

        current_frame_y -= 50;
    }

    current_frame_y = 550;
}


bool Map::isEnd()
{
    return world.eof();
}


void Map::setScene(QGraphicsScene *scene)
{
    scene_m = scene;
}


QList<QGraphicsItem *> * Map::getListItem()
{
    return &list_item;
}
