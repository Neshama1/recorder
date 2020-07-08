#ifndef AUDIOPROBER_H
#define AUDIOPROBER_H

#include <QAudioProbe>
#include <QObject>
#include <QTimer>
#include <QVariant>
#include <QDebug>

class AudioProber : public QAudioProbe
{
    Q_OBJECT
    Q_PROPERTY(QVariantList volumesList READ volumesList NOTIFY volumesListChanged)
    Q_PROPERTY(int animationIndex READ animationIndex NOTIFY animationIndexChanged)
    
public:
    explicit AudioProber(QObject *parent = nullptr);
    
    void process(QAudioBuffer buffer);
    void processVolumeBar();
    
    QVariantList volumesList() const
    {
        return {m_volumesList.begin(), m_volumesList.end()};
    }
    
    Q_INVOKABLE void setMaxVolumes(int m)
    {
        maxVolumes = m;
    }
    
    int animationIndex()
    {
        return m_animationIndex;
    }
    
    void clearVolumesList()
    {
        while (!m_volumesList.empty())
            m_volumesList.removeFirst();
        emit volumesListChanged();
    }
    
private:
    int m_audioSum = 0, m_audioLen = 0; // used for calculating the value of one volume bar from many
    int m_animationIndex = 0; // which index rectangle is being expanded
    int maxVolumes = 100; // based on width of screen
    
    QList<int> m_volumesList;
    
    QTimer* volumeBarTimer;
    
signals:
    void volumesListChanged();
    void animationIndexChanged();
};

#endif
