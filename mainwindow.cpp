#include "mainwindow.h"
#include "playerwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    PlayerWidget *w = new PlayerWidget(this);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{

}
