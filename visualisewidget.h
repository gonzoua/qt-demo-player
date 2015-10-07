#ifndef VISUALISEWIDGET_H
#define VISUALISEWIDGET_H

#include <QWidget>

class VisualiseWidget : public QWidget
{
Q_OBJECT
public:
    explicit VisualiseWidget(QWidget *parent = 0);
    virtual ~VisualiseWidget();
    virtual void paintEvent(QPaintEvent *);
signals:

public slots:
private:
    int *m_levels;
};

#endif // VISUALISEWIDGET_H
