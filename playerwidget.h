#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QProgressBar>
#include <QMediaPlayer>
#include <QAudioProbe>

#include "visualisewidget.h"
#include "volumewidget.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = 0);
    virtual ~PlayerWidget();
signals:

public slots:
    void startstop();
    void prevFile();
    void nextFile();
    void volumeUp();
    void volumeDown();

    void positionChanged(qint64);
    void durationChanged(qint64);
    void processBuffer(QAudioBuffer);

protected:
    void restartPlayer();

private:
    bool m_playing;
    QStringList m_files;
    int m_playlistPos;
    QPushButton *m_startstopButton;
    QProgressBar *m_playProgress;
    QMediaPlayer *m_player;
    QAudioProbe *m_probe;
    VisualiseWidget *m_visualizer;
    VolumeWidget *m_volumeWidget;
    qint64 m_position;
    qint64 m_duration;
};

#endif // PLAYERWIDGET_H
