/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCC_SOUND_SOUNDMODEL_H
#define DCC_SOUND_SOUNDMODEL_H

#include <QDBusObjectPath>
#include <QObject>
#include <QMap>
#include <QString>
#include <DDesktopServices>

DWIDGET_USE_NAMESPACE

namespace dcc {
namespace sound {
using SoundEffectList = QList<std::pair<QString, DDesktopServices::SystemSoundEffect>>;

class Port : public QObject
{
    Q_OBJECT
public:
    enum Direction {
        Out = 1,
        In = 2
    };

    explicit Port(QObject * parent) : QObject(parent) {}
    virtual ~Port() {}

    inline QString id() const { return m_id; }
    void setId(const QString &id);

    inline QString name() const { return m_name; }
    void setName(const QString &name);

    inline QString cardName() const { return m_cardName; }
    void setCardName(const QString &cardName);

    inline bool isActive() const { return m_isActive; }
    void setIsActive(bool isActive);

    inline Direction direction() const { return m_direction; }
    void setDirection(const Direction &direction);

    inline uint cardId() const { return m_cardId; }
    void setCardId(const uint &cardId);

Q_SIGNALS:
    void idChanged(QString id) const;
    void nameChanged(QString name) const;
    void cardNameChanged(QString name) const;
    void isActiveChanged(bool ative) const;
    void directionChanged(Direction direction) const;
    void cardIdChanged(uint cardId) const;

private:
    QString m_id;
    QString m_name;
    uint m_cardId;
    QString m_cardName;
    bool m_isActive;
    Direction m_direction;
};

class SoundModel : public QObject
{
    Q_OBJECT
public:
    explicit SoundModel(QObject *parent = 0);
    ~SoundModel();

    inline bool speakerOn() const { return m_speakerOn; }
    void setSpeakerOn(bool speakerOn);

    inline bool isPortEnable() const { return m_portEnable; }
    void setPortEnable(bool enable);

    inline bool reduceNoise() const { return m_reduceNoise; }
    void setReduceNoise(bool reduceNoise);

    inline bool microphoneOn() const { return m_microphoneOn; }
    void setMicrophoneOn(bool microphoneOn);

    inline double speakerBalance() const { return m_speakerBalance; }
    void setSpeakerBalance(double speakerBalance);

    inline double microphoneVolume() const { return m_microphoneVolume; }
    void setMicrophoneVolume(double microphoneVolume);

#ifndef DCC_DISABLE_FEEDBACK
    inline double microphoneFeedback() const { return m_microphoneFeedback; }
    void setMicrophoneFeedback(double microphoneFeedback);
#endif

    void setPort(const Port *port);
    void addPort(Port *port);
    void removePort(const QString &portId, const uint &cardId);
    bool containsPort(const Port *port);
    Port *findPort(const QString &portId, const uint &cardId) const;
    QList<Port *> ports() const;

    inline double speakerVolume() const { return m_speakerVolume; }
    void setSpeakerVolume(double speakerVolume);

    QDBusObjectPath defaultSource() const;
    void setDefaultSource(const QDBusObjectPath &defaultSource);

    QDBusObjectPath defaultSink() const;
    void setDefaultSink(const QDBusObjectPath &defaultSink);

    QString audioCards() const;
    void setAudioCards(const QString &audioCards);

    inline double MaxUIVolume() const { return m_maxUIVolume; }
    void setMaxUIVolume(double value);

    SoundEffectList soundEffectMap() const;

    void setEffectData(DDesktopServices::SystemSoundEffect effect, const bool enable);
    bool queryEffectData(DDesktopServices::SystemSoundEffect effect);

    bool enableSoundEffect() const { return m_enableSoundEffect; }
    void setEnableSoundEffect(bool enableSoundEffect);

    void updateSoundEffectPath(DDesktopServices::SystemSoundEffect effect, const QString &path);
    inline QMap<DDesktopServices::SystemSoundEffect, QString> soundEffectPaths() { return m_soundEffectPaths; }
    const QString soundEffectPathByType(DDesktopServices::SystemSoundEffect effect);

    const QString getNameByEffectType(DDesktopServices::SystemSoundEffect effect) const;
    DDesktopServices::SystemSoundEffect getEffectTypeByGsettingName(const QString &name);

    bool checkSEExist(const QString &name); // SE: Sound Effect

    bool isLaptop() const;
    void setIsLaptop(bool isLaptop);

    bool isIncreaseVolume() const;
    void setIncreaseVolume(bool value);
Q_SIGNALS:
    void speakerOnChanged(bool speakerOn) const;
    void microphoneOnChanged(bool microphoneOn) const;
    void soundEffectOnChanged(bool soundEffectOn) const;
    void speakerVolumeChanged(double speakerVolume) const;
    void speakerBalanceChanged(double speakerBalance) const;
    void microphoneVolumeChanged(double microphoneVolume) const;
    void defaultSourceChanged(const QDBusObjectPath &defaultSource) const;
    void defaultSinkChanged(const QDBusObjectPath &defaultSink) const;
    void audioCardsChanged(const QString &audioCards) const;
    void maxUIVolumeChanged(double value) const;
    void increaseVolumeChanged(bool value) const;
    void reduceNoiseChanged(bool reduceNoise) const;
    void isPortEnableChanged(bool enable) const;

    void setPortChanged(const Port* port) const;
    //发出请求切换扬声器打开/关闭的请求
    void requestSwitchSetEnable(unsigned int cardId,QString cardName, bool enable);
    //查询是否可用
    void requestSwitchEnable(unsigned int cardId,QString cardName);

#ifndef DCC_DISABLE_FEEDBACK
    void microphoneFeedbackChanged(double microphoneFeedback) const;
#endif
    void portAdded(const Port *port);
    void portRemoved(const QString & portId, const uint &cardId);
    void soundEffectDataChanged(DDesktopServices::SystemSoundEffect effect, const bool enable);
    void enableSoundEffectChanged(bool enableSoundEffect);
    void isLaptopChanged(bool isLaptop);

private:
    bool m_speakerOn;
    bool m_microphoneOn;
    bool m_enableSoundEffect;
    bool m_isLaptop;
    bool m_increaseVolume{false};
    bool m_reduceNoise{true};
    bool m_portEnable{false};
    double m_speakerVolume;
    double m_speakerBalance;
    double m_microphoneVolume;
    double m_maxUIVolume;

#ifndef DCC_DISABLE_FEEDBACK
    double m_microphoneFeedback;
#endif
    QList<Port *> m_ports;

    QDBusObjectPath m_defaultSource;
    QDBusObjectPath m_defaultSink;
    QString m_audioCards;

    SoundEffectList m_soundEffectMapPower;
    SoundEffectList m_soundEffectMapBattery;
    QMap<DDesktopServices::SystemSoundEffect, bool> m_soundEffectData;
    QMap<DDesktopServices::SystemSoundEffect, QString> m_soundEffectPaths;
};

} // namespace sound
} // namespace dcc

#endif // DCC_SOUND_SOUNDMODEL_H
