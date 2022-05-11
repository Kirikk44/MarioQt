#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "characters.h"
#include "map.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void DeathCharacterSlot();
    void ResumeGameSlot();
    void NextLvlSlot();


private slots:

    void on_actionHelp_triggered();

  //  void on_actionWorld_1_triggered();

  //  void on_actionWorld2_triggered();

    void on_actionAuthor_triggered();

    void on_actionPlay_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    Character *mario = nullptr;
    Map *map = nullptr;
    QTimer *timer;

    QGraphicsTextItem * text_game_over = nullptr;

    QTimer timer_press_check;

    char attempts = 3;
    char current_world = 1;

};
#endif // MAINWINDOW_H
