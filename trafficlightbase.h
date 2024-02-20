#pragma once

#include <QObject>
#include <QQmlEngine>

class QStateMachine;
class QState;
class QFinalState;

class TrafficLightBase : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool red READ getRed WRITE setRed NOTIFY redChanged)
    Q_PROPERTY(bool green READ getGreen WRITE setGreen NOTIFY greenChanged)
    Q_PROPERTY(int timeRed READ getTimeRed WRITE setTimeRed NOTIFY timeRedChanged)
    Q_PROPERTY(int timeGreen READ getTimeGreen WRITE setTimeGreen NOTIFY timeGreenChanged)
public:
    explicit TrafficLightBase(QObject *parent = nullptr);

    Q_INVOKABLE
    void start();

    bool getRed() const;
    void setRed(bool value);

    bool getGreen() const;
    void setGreen(bool value);

    int getTimeRed() const;
    void setTimeRed(int value);

    int getTimeGreen() const;
    void setTimeGreen(int value);

signals:
    // property changed signals
    void redChanged();
    void greenChanged();
    void timeRedChanged();
    void timeGreenChanged();

    // transitions
    void initDone();
    void timeRedDone();
    void timeGreenDone();
    void finishDone();

    // output signal
    void done();

protected:
    bool m_red { true };
    bool m_green { false };
    int m_timeRed { 2000 };
    int m_timeGreen { 5000 };
    QStateMachine *m_sm { nullptr };
    QState *m_stateInit { nullptr };
    QState *m_stateRed { nullptr };
    QState *m_stateGreen { nullptr };
    QState *m_stateFinish { nullptr };
    QFinalState *m_stateFinal { nullptr };
    QList<QState *> m_listStates;

    void initTransitions();
    virtual void stateInit();
    virtual void stateRed();
    virtual void stateGreen();
    virtual void stateFinish();
};
