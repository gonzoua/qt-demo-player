#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PlayerWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    PlayerWidget *m_playerWidget;
};

#endif // MAINWINDOW_H
