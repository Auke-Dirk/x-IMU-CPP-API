#include "ximugui/widgets/simplewindow.h"
#include "ui_simplewindow.h"

SimpleWindow::SimpleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimpleWindow)
{
    ui->setupUi(this);

}

SimpleWindow::~SimpleWindow()
{
    delete ui;
}

void SimpleWindow::on_actionExit_triggered()
{
    this->close();
}
