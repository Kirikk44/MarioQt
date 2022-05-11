#ifndef AUTHORWIN_H
#define AUTHORWIN_H

#include <QDialog>

namespace Ui {
class AboutWin;
}

class AuthorWin : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorWin(QWidget *parent = nullptr);
    ~AuthorWin();

private:
    Ui::AboutWin *ui;
};

#endif // AUTHORWIN_H
