#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include <QWidget>

class QTimer;

class VolumeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeWidget(QWidget *parent = 0);
    virtual ~VolumeWidget();
    virtual void paintEvent(QPaintEvent *);

    void setVolume(int volume);
signals:

public slots:
protected slots:
    void fadeoutTick();

private:
    int m_volume;
    int m_alpha;
    QTimer *m_fadeoutTimer;
};

#endif // VOLUMEWIDGET_H
