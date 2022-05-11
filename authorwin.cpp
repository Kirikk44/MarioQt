#include "authorwin.h"
#include "ui_aboutwin.h"

AuthorWin::AuthorWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWin)
{
    ui->setupUi(this);
}

AuthorWin::~AuthorWin()
{
    delete ui;
}
