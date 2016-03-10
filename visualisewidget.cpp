#include <QPainter>

#include <QDebug>
#include <QtMath>
#include <QTimer>

#include "visualisewidget.h"
#include <cmath>

#define MARGIN 3
#define BARS 32
#define LEVELS 40

QColor colorForLevel(int level)
{
    level += 20;
    if (level < 0)
        level = 0;
    if (level > 100)
        level = 100;

    return QColor::fromHsv(120*(100-level)/100, 200, 200);
}

VisualiseWidget::VisualiseWidget(QWidget *parent) : QWidget(parent)
{
    m_bars = new struct bar_state[BARS];
    for (int i = 0; i < BARS; i++) {
        m_bars[i].level = 0;
        m_bars[i].painted_level = 0;
        m_bars[i].cap_level = 0;
        m_bars[i].cap_countdown = 0;
    }

    QTimer *repaintTimer = new QTimer(this);
    connect(repaintTimer, SIGNAL(timeout()), this, SLOT(repaintTick()));
    repaintTimer->setSingleShot(false);
    repaintTimer->start(20);
}

VisualiseWidget::~VisualiseWidget()
{
    delete[] m_bars;
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
        int origY;
        int origX = offX + MARGIN + (boxWidth + MARGIN)*b;
        for (int l = 0; l < m_bars[b].painted_level; l++) {
            origY = size().height() - MARGIN - (boxHeight + MARGIN)*l - boxHeight;
            QBrush power(colorForLevel(l*100/LEVELS));
            painter.fillRect(QRect(origX, origY, boxWidth, boxHeight), power);
        }

        origY = size().height() - MARGIN - (boxHeight + MARGIN)*m_bars[b].cap_level - MARGIN;
        QBrush cap(QColor(0xa0, 0xa0, 0xa0));
        painter.fillRect(QRect(origX, origY, boxWidth, MARGIN), cap);
    }

    painter.end();
}

void VisualiseWidget::repaintTick()
{
    bool changed = false;
    for (int i = 0; i < BARS; i++) {
        if (m_bars[i].level > m_bars[i].painted_level) {
            m_bars[i].painted_level++;
            changed = true;
        }
        if (m_bars[i].level < m_bars[i].painted_level) {
            m_bars[i].painted_level--;
            changed = true;
        }
        if (m_bars[i].cap_level < m_bars[i].painted_level) {
            m_bars[i].cap_level = m_bars[i].painted_level;
            changed = true;
        }

        if (m_bars[i].cap_level == m_bars[i].painted_level) {
            m_bars[i].cap_countdown = 10;
        }

        if (m_bars[i].cap_level > m_bars[i].painted_level) {
            if (m_bars[i].cap_countdown == 0) {
                m_bars[i].cap_level -= 2;

                if (m_bars[i].cap_level < m_bars[i].painted_level) {
                    m_bars[i].cap_level = m_bars[i].painted_level;
                }
                changed = true;
            }
            else
                m_bars[i].cap_countdown--;
        }
    }

    if (changed)
        repaint();
}

void VisualiseWidget::updateSpectrum(const FrequencySpectrum & spectrum)
{
    int b;
    qreal bins[BARS];

    for (b = 0; b < BARS; b++) {
        bins[b] = 0;
    }

#define FLOOR 20
#define CEIL 4200

    for (int i = 0; i < spectrum.count(); i++) {
        if (spectrum[i].frequency < FLOOR)
            continue;

        if (spectrum[i].frequency > CEIL)
            continue;

        b = int((((spectrum[i].frequency)-(FLOOR))/((CEIL)-(FLOOR))*BARS));
        if (b < 0)
            b = 0;
        else if (b >= BARS)
            b = BARS - 1;
        if (bins[b] < spectrum[i].amplitude) {
            bins[b] = spectrum[i].amplitude;
        }
    }

    for (b = 0; b < BARS; b++) {
        int new_level = int(qRound(bins[b]*LEVELS));
        m_bars[b].level = new_level;
    }
}
