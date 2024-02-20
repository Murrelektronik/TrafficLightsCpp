#include "trafficlight.h"
#include <QStateMachine>
#include <QFinalState>
#include <QTimer>
#include <QDebug>

TrafficLight::TrafficLight(QObject *parent)
    : TrafficLightBase { parent }
    , m_stateYellow(new QState)
    , m_stateYellowAfterGreen(new QState)
    , m_stateRedYellow(new QState)
    , m_timerMaxTime { new QTimer(this) }
{
    m_stateYellow->setObjectName("State Yellow");
    m_stateYellowAfterGreen->setObjectName("State Yellow After Green");
    m_stateRedYellow->setObjectName("State Red Yellow");

    m_sm->addState(m_stateYellow);
    m_sm->addState(m_stateRedYellow);
    m_sm->addState(m_stateYellowAfterGreen);
    m_listStates.append(m_stateYellow);
    m_listStates.append(m_stateRedYellow);
    m_listStates.append(m_stateYellowAfterGreen);

    initTransitions();
    connect(m_stateYellow, &QState::entered, this, &TrafficLight::stateYellow);
    connect(m_stateRedYellow, &QState::entered, this, &TrafficLight::stateRedYellow);
    connect(m_stateYellowAfterGreen, &QState::entered, this, &TrafficLight::stateYellowAfterGreen);
    connect(m_timerMaxTime, &QTimer::timeout, this, [this]() {
        qDebug() << "max time done";
        emit timeGreenDone();
    });
    m_timerMaxTime->setSingleShot(true);
}

bool TrafficLight::getYellow() const
{
    return m_yellow;
}

void TrafficLight::setYellow(bool value)
{
    if (m_yellow == value) {
        return;
    }
    m_yellow = value;
    emit yellowChanged();
}

int TrafficLight::getTimeYellow() const
{
    return m_timeYellow;
}

void TrafficLight::setTimeYellow(int value)
{
    if (m_timeYellow == value) {
        return;
    }
    m_timeYellow = value;
    emit timeYellowChanged();
}

int TrafficLight::getTimeRedYellow() const
{
    return m_timeRedYellow;
}

void TrafficLight::setTimeRedYellow(int value)
{
    if (m_timeRedYellow == value) {
        return;
    }
    m_timeRedYellow = value;
    emit timeRedYellowChanged();
}

int TrafficLight::getTimeYellowAfterGreen() const
{
    return m_timeYellowAfterGreen;
}

void TrafficLight::setTimeYellowAfterGreen(int value)
{
    if (m_timeYellowAfterGreen == value) {
        return;
    }
    m_timeYellowAfterGreen = value;
    emit timeYellowAfterGreenChanged();
}

bool TrafficLight::getStopRequest() const
{
    return m_stopRequest;
}

void TrafficLight::setStopRequest(bool value)
{
    qDebug() << Q_FUNC_INFO << value << m_minTimeDone;
    m_stopRequest = value;
    if (m_minTimeDone) {
        m_timerMaxTime->stop();
        emit timeGreenDone();
    }
}

bool TrafficLight::getIsMainStreet() const
{
    return m_isMainStreet;
}

void TrafficLight::setIsMainStreet(bool value)
{
    if (m_isMainStreet == value) {
        return;
    }
    m_isMainStreet = value;
    emit isMainStreetChanged();
}

void TrafficLight::initTransitions()
{
    qDebug() << Q_FUNC_INFO;
    clearTransisitions();
    m_stateInit->addTransition(this, &TrafficLight::initDone, m_stateRed);
    m_stateRed->addTransition(this, &TrafficLight::timeRedDone, m_stateRedYellow);
    m_stateRedYellow->addTransition(this, &TrafficLight::timeRedYellowDone, m_stateYellow);
    m_stateYellow->addTransition(this, &TrafficLight::timeYellowDone, m_stateGreen);
    m_stateGreen->addTransition(this, &TrafficLight::timeGreenDone, m_stateYellowAfterGreen);
    m_stateYellowAfterGreen->addTransition(this, &TrafficLight::timeYellowAfterGreenDone, m_stateFinish);
    m_stateFinish->addTransition(this, &TrafficLight::finishDone, m_stateFinal);
}

void TrafficLight::stateRed()
{
    qDebug() << Q_FUNC_INFO;
    setYellow(false);
    TrafficLightBase::stateRed();
}

void TrafficLight::stateGreen()
{
    qDebug() << Q_FUNC_INFO << m_isMainStreet << m_stopRequest << m_minTimeDone;
    setYellow(false);
    setRed(false);
    setGreen(true);

    // if (m_isMainStreet) {
    //     QTimer::singleShot(m_timeGreen, this, [this]() {
    //         qDebug() << "min time done";
    //         if (m_stopRequest) {
    //             qDebug() << "min time done and stop request active";
    //             if (m_timerMaxTime->isActive()) {
    //                 m_timerMaxTime->stop();
    //             }
    //             emit timeGreenDone();
    //         }
    //         m_minTimeDone = true;
    //     });
    //     m_timerMaxTime->start(m_timeGreenMax);
    //     return;
    // }
    TrafficLightBase::stateGreen();
}

void TrafficLight::stateFinish()
{
    qDebug() << Q_FUNC_INFO << m_minTimeDone << m_stopRequest;
    m_minTimeDone = false;
    m_stopRequest = false;
    setYellow(false);
    TrafficLightBase::stateFinish();
}

void TrafficLight::stateYellow()
{
    qDebug() << Q_FUNC_INFO;
    setYellow(true);
    QTimer::singleShot(m_timeYellow, this, [this]() { emit timeYellowDone(); });
}

void TrafficLight::stateYellowAfterGreen()
{
    qDebug() << Q_FUNC_INFO;
    setYellow(true);
    setGreen(false);
    QTimer::singleShot(m_timeYellowAfterGreen, this, [this]() { emit timeYellowAfterGreenDone(); });
}

void TrafficLight::stateRedYellow()
{
    qDebug() << Q_FUNC_INFO;
    setYellow(true);
    setRed(true);
    QTimer::singleShot(m_timeRedYellow, this, [this]() { emit timeRedYellowDone(); });
}

void TrafficLight::clearTransisitions()
{
    qDebug() << Q_FUNC_INFO;

    for (QState *state : m_listStates) {
        QList<QAbstractTransition *> transitions = state->transitions();
        for (QAbstractTransition *t : transitions) {
            state->removeTransition(t);
        }
    }
}
