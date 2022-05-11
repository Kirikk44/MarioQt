#include <QDebug>
#include <QKeyEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorwin.h"
#include "helpwin.h"
#include "characters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qDebug() << "nen2";
    ui->graphicsView->setBackgroundBrush(QColor(92, 148, 252));

    scene.setSceneRect(0, 0, 1000, 600);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->setScene(&scene);

    timer = new QTimer();

    mario = new Character();
    mario->setPos(50, 300);
    mario->setImage(":/images/mario.png");

    qDebug() << "sdf";

    map = new Map(&scene, timer, 1);
    qDebug() << "sdf";
    map->add_items();

    mario->setMap(map);
    mario->setTimer(timer);
    scene.addItem(mario);

    connect(timer, &QTimer::timeout, mario, &Character::SlotTimer);

    connect(mario, &Character::DeathCharacterSignal, this, &MainWindow::DeathCharacterSlot);

    connect(mario, &Character::NextLvlSignal, this, &MainWindow::NextLvlSlot);

}

void MainWindow::DeathCharacterSlot()
{
    timer->stop();
    attempts--;

    delete map;
    mario->setPos(50, 300);

    text_game_over = new QGraphicsTextItem();
    QString string_text;
    if (attempts)
    {
        string_text = "<p>Mario x " + QString::number(attempts) + "</p>" + "<p>Press the space bar to continue";

    }
    else // game over
    {
        string_text = "<p>GAME OVER </p>press the space bar to start over";
    }

    QFont font("Consolas", 20, QFont::Black);
    text_game_over->setHtml(string_text);
    text_game_over->setFont(font);
    text_game_over->setPos(400, 200);
    scene.addItem(text_game_over);

//    timer_press_check = new QTimer();
    timer_press_check.start(45);
//        flag_press_key = 0;
    connect(&timer_press_check, &QTimer::timeout, this, &MainWindow::ResumeGameSlot);
}

void MainWindow::ResumeGameSlot()
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        if (!attempts)
        {
            current_world = 1;
            attempts = 3;
        }

        map = new Map(&scene, timer, current_world);

        map->add_items();
        mario->setMap(map);

        if (text_game_over)
            delete text_game_over;

        timer->start();
        disconnect(&timer_press_check, &QTimer::timeout, this, &MainWindow::ResumeGameSlot);
//        if (timer_press_check)
//            delete timer_press_check;
            timer_press_check.stop();
    }
}

void MainWindow::NextLvlSlot()
{
    timer->stop();

    if (map)
        delete map;
    current_world += 1;
    if (current_world <= 2)
    {
        mario->setPos(50, 300);
        connect(timer, &QTimer::timeout, mario, &Character::SlotTimer);
        text_game_over = new QGraphicsTextItem();
        QString string_text = "<p>Mario x " + QString::number(attempts) + "</p>World " + QString::number(current_world) + "</p>" + "<p>Press the space bar to continue";
        QFont font("Connsolas", 20, QFont::Black);
        text_game_over->setHtml(string_text);
        text_game_over->setFont(font);
        text_game_over->setPos(400, 200);
        scene.addItem(text_game_over);

//        timer_press_check = new QTimer();
        connect(&timer_press_check, &QTimer::timeout, this, &MainWindow::ResumeGameSlot);
        timer_press_check.start(1000/45);
//        flag_press_key = 0;

    }
    else {
        mario->setPos(50, -50);
        current_world = 1;
        attempts = 3;
        text_game_over = new QGraphicsTextItem();
        QString string_text = "<p>You Win!</p>Press the space bar to start a new game";
        QFont font("Connsolas", 20, QFont::Black);
        connect(timer, &QTimer::timeout, mario, &Character::SlotTimer);
        text_game_over->setHtml(string_text);
        text_game_over->setFont(font);
        text_game_over->setPos(300, 200);


        scene.addItem(text_game_over);
//        timer_press_check = new QTimer();
//        flag_press_key = 0;
        connect(&timer_press_check, &QTimer::timeout, this, &MainWindow::ResumeGameSlot);
        timer_press_check.start(1000/45);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    if (timer)
        delete timer;
    if (text_game_over)
        delete text_game_over;
    if (map)
        delete map;
}

void MainWindow::on_actionHelp_triggered()
{
    HelpWin win;
    win.setWindowTitle("Help");
    win.exec();
}

//void MainWindow::on_actionWorld_1_triggered()
//{
//    timer->stop();

//    if (map)
//    {
//        delete map;
//    }
//    map = new Map(&scene, timer, 1);
//    current_world = 1;
//    map->add_items();

//    mario->setPos(50, 300);
//    mario->setMap(map);
//    if (timer_press_check)
//    {
//        delete timer_press_check;
//        disconnect(timer_press_check, &QTimer::timeout, this, &MainWindow::ResumeGameSlot);
//    }

//    timer->start(1000/40);
//}

//void MainWindow::on_actionWorld2_triggered()
//{
//    timer->stop();

//    if (map)
//    {
//        delete map;
//    }
//    map = new Map(&scene, timer, 2);
//    current_world = 2;
//    map->add_items();

//    mario->setPos(50, 300);
//    mario->setMap(map);
//    if (timer_press_check)
//    {
//        delete timer_press_check;
//        disconnect(timer_press_check, &QTimer::timeout, this, &MainWindow::ResumeGameSlot);
//    }

//    timer->start(1000/40);
//}

void MainWindow::on_actionAuthor_triggered()
{
    AuthorWin win;
    win.setWindowTitle("Author");
    win.exec();
}

void MainWindow::on_actionPlay_triggered()
{
    if (!timer->isActive())
        timer->start(1000/40);
}

void MainWindow::on_actionQuit_triggered()
{
    delete this;
}
