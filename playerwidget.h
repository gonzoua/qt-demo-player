#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QProgressBar>
#include <QMediaPlayer>

#include "visualisewidget.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = 0);
    virtual ~PlayerWidget();
signals:

public slots:
    void startstop();
    void positionChanged(qint64);
    void durationChanged(qint64);
private:
    bool m_playing;
    QPushButton *m_startstopButton;
    QProgressBar *m_playProgress;
    QMediaPlayer *m_player;
    VisualiseWidget *m_visualizer;
    qint64 m_position;
    qint64 m_duration;
};

#endif // PLAYERWIDGET_H
