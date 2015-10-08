#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (a.arguments().length() < 2) {
        fprintf(stderr, "usage: %s file1 file2 file3\n", argv[0]);
        exit(0);
    }
    MainWindow w;
    w.setFixedSize(480, 272);
    w.show();

    return a.exec();
}
