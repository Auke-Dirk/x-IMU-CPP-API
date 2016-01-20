#ifndef SIMPLE_WINDOW_H_
#define SIMPLE_WINDOW_H_

#include <QMainWindow>

namespace Ui {
class SimpleWindow;
}

class SimpleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleWindow(QWidget *parent = 0);
    ~SimpleWindow();

private slots:
    void on_actionExit_triggered();


private:
    Ui::SimpleWindow *ui;
};

#endif // SIMPLE_WINDOW_H_
