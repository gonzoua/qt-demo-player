#ifndef VISUALISEWIDGET_H
#define VISUALISEWIDGET_H

#include <QWidget>
#include "frequencyspectrum.h"

struct bar_state
{
    int level;
    int painted_level;
    int cap_level;
    int cap_countdown;
};

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
protected slots:
    void repaintTick();

private:
    struct bar_state *m_bars;
};

#endif // VISUALISEWIDGET_H
