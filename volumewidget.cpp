#include "volumewidget.h"

#include <QPainter>
#include <QTimer>

#define BARS 20
#define MAX_ALPHA 255
#define ALPHA_STEP 10
#define VOLUME_TIMEOUT 1000
#define ALPHA_INTERVAL 50


VolumeWidget::VolumeWidget(int volume, QWidget *parent) : QWidget(parent)
{
    m_volume = volume;
    m_alpha = 0;
    m_fadeoutTimer = new QTimer;
    m_fadeoutTimer->setInterval(100);
    m_fadeoutTimer->setSingleShot(true);
    connect(m_fadeoutTimer, SIGNAL(timeout()), SLOT(fadeoutTick()));
}

VolumeWidget::~VolumeWidget()
{
    delete m_fadeoutTimer;
}

void VolumeWidget::setVolume(int volume)
{
    if (volume > 100)
        volume = 100;
    if (volume < 0)
        volume = 0;

    if (m_volume != volume) {
        m_alpha = MAX_ALPHA;
        m_volume = volume;
        repaint();
        m_fadeoutTimer->start(VOLUME_TIMEOUT);
    }
}

void VolumeWidget::paintEvent(QPaintEvent *)
{
    int barWidth, barHeight, centerX, centerY;

    QPainter painter(this);

    QBrush b(QColor(255, 255, 255, m_alpha));

    barWidth = 3*size().width()/4/(2*BARS - 1);
    barHeight = barWidth * 3;

    centerY = size().height()/2;
    for (int i = 0; i < BARS; i++) {
        centerX = size().width() / 8 + barWidth*2*i + barWidth/2;
        int w = barWidth;
        int h = barHeight;
        if (100/BARS*i >= m_volume) {
            w = h = barWidth/2;
        }

         painter.fillRect(QRect(centerX - w/2, centerY - h/2, w, h), b);
    }

    painter.end();
}

void VolumeWidget::fadeoutTick()
{
    m_alpha -= ALPHA_STEP;
    if (m_alpha < 0)
        m_alpha = 0;
    repaint();
    if (m_alpha)
        m_fadeoutTimer->start(ALPHA_INTERVAL);
}
