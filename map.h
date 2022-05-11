#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>

#include "block.h"

#include <fstream>
using namespace std;

class Map: public QObject
{
    Q_OBJECT
public:
    Map(QGraphicsScene *scene, QTimer * tm, int wd);
    ~Map();

    void add_items();

    bool isEnd();

    void setScene(QGraphicsScene *scene);

    QList<QGraphicsItem *> * getListItem();

private:
    QPixmap bkgpic;

    QGraphicsScene *scene_m;

    QList<QGraphicsItem *> list_item;

    Block *block;

    QTimer * tm;

    ifstream world;

    int current_frame_x =  0;
    int current_frame_y = 550;
};

#endif // MAP_H
