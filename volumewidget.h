#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include <QWidget>

class QTimer;

class VolumeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeWidget(int volume = 0, QWidget *parent = 0);
    virtual ~VolumeWidget();
    virtual void paintEvent(QPaintEvent *);

    void setVolume(int volume);
    void setInfo(const QString &info);
signals:

public slots:
protected slots:
    void fadeoutTick();

private:
    int m_volume;
    QString m_info;
    int m_alpha;
    QTimer *m_fadeoutTimer;

    bool m_displayVolume;
    bool m_displayInfo;
};

#endif // VOLUMEWIDGET_H
