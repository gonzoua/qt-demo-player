#include "playerwidget.h"
#include <QGridLayout>

#define playText QString::fromUtf8("\xE2\x96\xB6")
#define pauseText QString::fromUtf8("\xE2\x8F\xB9")

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    m_playing = false;

    m_startstopButton = new QPushButton(this);
    m_startstopButton->setText(playText);
    m_startstopButton->setMinimumWidth(100);
    connect(m_startstopButton, SIGNAL(pressed()), SLOT(startstop()));

    m_playProgress = new QProgressBar(this);
    m_visualizer = new VisualiseWidget(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_visualizer, 0, 0, 1, 2);
    layout->addWidget(m_playProgress, 1, 0, 1, 1);
    layout->addWidget(m_startstopButton, 1, 1, 1, 1);
    setLayout(layout);

    m_player = new QMediaPlayer;
    m_player->setNotifyInterval(500);
    m_player->setMedia(QUrl::fromLocalFile("/Users/gonzo/Downloads/Plach Yeremii - Svitlo i spovid'.mp3"));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(m_player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
}

PlayerWidget::~PlayerWidget()
{

    delete m_player;
}

void PlayerWidget::startstop()
{
    m_playing = !m_playing;

    if (m_playing)
        m_player->play();
    else
        m_player->pause();

    m_startstopButton->setText(m_playing ? pauseText : playText);
}

void PlayerWidget::durationChanged(qint64 duration)
{
    m_playProgress->setMaximum(duration);
    m_playProgress->setValue(0);
}

void PlayerWidget::positionChanged(qint64 position)
{
    m_playProgress->setValue(position);
}
