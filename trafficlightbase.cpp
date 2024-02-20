#include "trafficlightbase.h"
#include <QStateMachine>
#include <QFinalState>
#include <QTimer>
#include <QDebug>

TrafficLightBase::TrafficLightBase(QObject *parent)
    : QObject { parent }
    , m_sm { new QStateMachine(this) }
    , m_stateInit { new QState }
    , m_stateRed { new QState }
    , m_stateGreen { new QState }
    , m_stateFinish { new QState }
    , m_stateFinal { new QFinalState }
{
    m_sm->setObjectName("State Machine Traffic Light Base");
    m_stateInit->setObjectName("State Init");
    m_stateRed->setObjectName("State Red");
    m_stateGreen->setObjectName("State Green");
    m_stateFinish->setObjectName("State Finish");
    m_stateFinal->setObjectName("State Final");

    m_sm->addState(m_stateInit);
    m_sm->addState(m_stateRed);
    m_sm->addState(m_stateGreen);
    m_sm->addState(m_stateFinish);
    m_sm->addState(m_stateFinal);

    m_sm->setInitialState(m_stateInit);
    m_listStates.append(m_stateInit);
    m_listStates.append(m_stateRed);
    m_listStates.append(m_stateGreen);
    m_listStates.append(m_stateFinish);

    initTransitions();
    connect(m_stateInit, &QState::entered, this, &TrafficLightBase::stateInit);
    connect(m_stateRed, &QState::entered, this, &TrafficLightBase::stateRed);
    connect(m_stateGreen, &QState::entered, this, &TrafficLightBase::stateGreen);
    connect(m_stateFinish, &QState::entered, this, &TrafficLightBase::stateFinish);

    connect(m_sm, &QStateMachine::started, this, [this]() { qDebug() << "State Machine Traffic Light Base started"; });
    connect(m_sm, &QStateMachine::finished, this, [this]() {
        qDebug() << "State Machine Traffic Light Base finished";
        emit done();
    });
}

void TrafficLightBase::start()
{
    // qDebug() << Q_FUNC_INFO;

    if (m_sm->isRunning()) {
        return;
    }

    m_sm->start();
}

void TrafficLightBase::initTransitions()
{
    // qDebug() << Q_FUNC_INFO;
    m_stateInit->addTransition(this, &TrafficLightBase::initDone, m_stateRed);
    m_stateRed->addTransition(this, &TrafficLightBase::timeRedDone, m_stateGreen);
    m_stateGreen->addTransition(this, &TrafficLightBase::timeGreenDone, m_stateFinish);
    m_stateFinish->addTransition(this, &TrafficLightBase::finishDone, m_stateFinal);
}

bool TrafficLightBase::getRed() const
{
    return m_red;
}

void TrafficLightBase::setRed(bool value)
{
    if (m_red == value) {
        return;
    }
    m_red = value;
    emit redChanged();
}

bool TrafficLightBase::getGreen() const
{
    return m_green;
}

void TrafficLightBase::setGreen(bool value)
{
    if (m_green == value) {
        return;
    }
    m_green = value;
    emit greenChanged();
}

int TrafficLightBase::getTimeRed() const
{
    return m_timeRed;
}

void TrafficLightBase::setTimeRed(int value)
{
    if (m_timeRed == value) {
        return;
    }
    m_timeRed = value;
    emit timeRedChanged();
}

int TrafficLightBase::getTimeGreen() const
{
    return m_timeGreen;
}

void TrafficLightBase::setTimeGreen(int value)
{
    if (m_timeGreen == value) {
        return;
    }
    m_timeGreen = value;
    emit timeGreenChanged();
}

void TrafficLightBase::stateInit()
{
    // qDebug() << Q_FUNC_INFO;
    emit initDone();
}

void TrafficLightBase::stateRed()
{
    // qDebug() << Q_FUNC_INFO;
    setRed(true);
    setGreen(false);
    QTimer::singleShot(m_timeRed, this, [this]() { emit timeRedDone(); });
}

void TrafficLightBase::stateGreen()
{
    // qDebug() << Q_FUNC_INFO;
    setRed(false);
    setGreen(true);
    QTimer::singleShot(m_timeGreen, this, [this]() { emit timeGreenDone(); });
}

void TrafficLightBase::stateFinish()
{
    // qDebug() << Q_FUNC_INFO;
    setRed(true);
    setGreen(false);
    emit finishDone();
}
