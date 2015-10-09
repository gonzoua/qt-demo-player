#ifndef VISUALISEWIDGET_H
#define VISUALISEWIDGET_H

#include <QWidget>
#include "frequencyspectrum.h"

class VisualiseWidget : public QWidget
{
Q_OBJECT
public:
    explicit VisualiseWidget(QWidget *parent = 0);
    virtual ~VisualiseWidget();
    virtual void paintEvent(QPaintEvent *);

    void updateSpectrum(const FrequencySpectrum &);
signals:

public slots:
private:
    int *m_levels;
};

#endif // VISUALISEWIDGET_H
