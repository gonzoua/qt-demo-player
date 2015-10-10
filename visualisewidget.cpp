#include <QPainter>
#include <QDebug>
#include <QtMath>

#include "visualisewidget.h"

#define MARGIN 2
#define BARS 32
#define LEVELS 20

QColor colorForLevel(int level)
{
    if (level < 0)
        level = 0;
    if (level > 100)
        level = 100;

    return QColor::fromHsv(120*(100-level)/100, 200, 200);
}

VisualiseWidget::VisualiseWidget(QWidget *parent) : QWidget(parent)
{
    m_levels = new int[BARS];
    for (int i = 0; i < BARS; i++)
        m_levels[i] = LEVELS - i;
}

VisualiseWidget::~VisualiseWidget()
{
    delete[] m_levels;
}

void VisualiseWidget::paintEvent(QPaintEvent *)
{
    int boxWidth;
    int boxHeight;

    QPainter painter(this);
    QBrush b(QColor(0, 0, 0));
    painter.fillRect(QRect(QPoint(0, 0), this->size()), b);

    boxWidth = (size().width() - (BARS + 1)*MARGIN)/BARS;
    boxHeight = (size().height() - (LEVELS + 1)*MARGIN)/LEVELS;

    // center power bars horizontaly
    int offX = (size().width() - ((boxWidth + MARGIN)*BARS + 2*MARGIN))/2;
    for (int b = 0; b < BARS; b++) {
        int origX = offX + MARGIN + (boxWidth + MARGIN)*b;
        for (int l = 0; l < m_levels[b]; l++) {
            int origY = size().height() - MARGIN - (boxHeight + MARGIN)*l - boxHeight;
            QBrush power(colorForLevel(l*100/LEVELS));
            painter.fillRect(QRect(origX, origY, boxWidth, boxHeight), power);
        }
    }

    painter.end();
}

void VisualiseWidget::updateSpectrum(const FrequencySpectrum & spectrum)
{
    int b;
    qreal bins[BARS];

    for (b = 0; b < BARS; b++) {
        bins[b] = 0;
    }

    for (int i = 0; i < spectrum.count(); i++) {
        if (spectrum[i].frequency == 0)
            continue;
        b = int((qSqrt(spectrum[i].frequency/20000)*BARS)) - 1;
        if (b < 0)
            b = 0;
        else if (b >= BARS)
            b = BARS - 1;
        if (bins[b] < spectrum[i].amplitude) {
            bins[b] = spectrum[i].amplitude;
        }
    }

    for (b = 0; b < BARS; b++) {
        m_levels[b] = int(qRound(bins[b]*30));
    }

    repaint();
}
