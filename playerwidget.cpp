#include "playerwidget.h"
#include <QGridLayout>
#include <QApplication>

#define playText QString::fromUtf8("\xE2\x96\xB6")
#define pauseText QString::fromUtf8("\xE2\x8F\xB9")

#define VOLUME_STEP 5

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    m_playing = false;
    m_files = qApp->arguments();
    m_files.removeAt(0);
    m_playlistPos = 0;

    m_startstopButton = new QPushButton(this);
    m_startstopButton->setText(playText);
    m_startstopButton->setMinimumWidth(100);
    connect(m_startstopButton, SIGNAL(pressed()), SLOT(startstop()));

    m_playProgress = new QProgressBar(this);
    m_visualizer = new VisualiseWidget(this);
    m_volumeWidget = new VolumeWidget(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_visualizer, 0, 0, 1, 2);
    layout->addWidget(m_volumeWidget, 0, 0, 1, 2);
    m_visualizer->stackUnder(m_volumeWidget);
    layout->addWidget(m_playProgress, 1, 0, 1, 1);
    layout->addWidget(m_startstopButton, 1, 1, 1, 1);
    setLayout(layout);

    m_player = new QMediaPlayer;
    m_player->setNotifyInterval(500);
    m_player->setMedia(QUrl::fromLocalFile(m_files.at(m_playlistPos)));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(m_player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));

    m_player->setVolume(50);
    m_volumeWidget->setVolume(m_player->volume());

    m_playProgress->setTextVisible(0);

    m_probe = new QAudioProbe;
    connect(m_probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
            this, SLOT(processBuffer(QAudioBuffer)));
    m_probe->setSource(m_player);

    connect(&m_spectrumAnalyser, SIGNAL(spectrumChanged(FrequencySpectrum)),
                    this, SLOT(spectrumChanged(FrequencySpectrum)));
}

PlayerWidget::~PlayerWidget()
{

    delete m_player;
    delete m_probe;
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

void PlayerWidget::processBuffer(QAudioBuffer ab)
{
    m_format = ab.format();
    m_audioBuffer.append(QByteArray::fromRawData((const char*)ab.constData(),
                                                   ab.byteCount()));
    m_spectrumBufferSize = m_format.bytesForFrames(SpectrumLengthSamples);
    if (m_spectrumAnalyser.isReady()) {
        if (m_audioBuffer.size() >= m_spectrumBufferSize) {
            m_spectrumBuffer = m_audioBuffer.left(m_spectrumBufferSize);
            m_audioBuffer.remove(0, m_spectrumBufferSize);
            m_spectrumAnalyser.calculate(m_spectrumBuffer, m_format);
        }
    }
}

void PlayerWidget::restartPlayer()
{
    bool resume;

    resume = (m_player->state() == QMediaPlayer::PlayingState);
    if (m_player->state() != QMediaPlayer::StoppedState)
        m_player->stop();
    m_player->setMedia(QUrl::fromLocalFile(m_files.at(m_playlistPos)));
    m_playing = resume;
    if (resume) {
        m_player->play();
    }
}

void PlayerWidget::prevFile()
{
    m_playlistPos -= 1;
    if (m_playlistPos < 0)
        m_playlistPos = m_files.length() - 1;

    restartPlayer();
}

void PlayerWidget::nextFile()
{
    m_playlistPos += 1;
    if (m_playlistPos >= m_files.length())
        m_playlistPos = 0;

    restartPlayer();
}

void PlayerWidget::volumeDown()
{
    int vol = m_player->volume();
    vol -= VOLUME_STEP;
    if (vol < 0)
        vol = 0;
    m_player->setVolume(vol);
    m_volumeWidget->setVolume(vol);
}


void PlayerWidget::volumeUp()
{
    int vol = m_player->volume();
    vol += VOLUME_STEP;
    if (vol > 100)
        vol = 100;
    m_player->setVolume(vol);
    m_volumeWidget->setVolume(vol);
}

void PlayerWidget::spectrumChanged(FrequencySpectrum fs)
{
    m_visualizer->updateSpectrum(fs);
}
