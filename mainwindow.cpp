#include <QKeyEvent>

#include "mainwindow.h"
#include "playerwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_playerWidget = new PlayerWidget(this);
    setCentralWidget(m_playerWidget);
}

MainWindow::~MainWindow()
{

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() ==  Qt::Key_Return)
        m_playerWidget->startstop();
    if(event->key() ==  Qt::Key_Left)
        m_playerWidget->prevFile();
    if(event->key() ==  Qt::Key_Right)
        m_playerWidget->nextFile();
    if(event->key() ==  Qt::Key_Up)
        m_playerWidget->volumeUp();
    if(event->key() ==  Qt::Key_Down)
        m_playerWidget->volumeDown();
}

void MainWindow::keyReleaseEvent(QKeyEvent *)
{
}
