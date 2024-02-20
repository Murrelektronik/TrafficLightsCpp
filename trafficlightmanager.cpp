#include "trafficlightmanager.h"
#include "trafficlightbase.h"
#include "trafficlight.h"
#include <QStateMachine>
#include <QFinalState>
#include <QDebug>

TrafficLightManager::TrafficLightManager(QObject *parent)
    : QObject { parent }
    , m_sm { new QStateMachine(this) }
    , m_stateInit { new QState }
    , m_stateMainStreet { new QState }
    , m_stateSideStreet { new QState }
    , m_statePedestrian1 { new QState }
    , m_statePedestrian2 { new QState }
    , m_stateFinish { new QState }
    , m_stateFinal { new QFinalState }
{
    m_pedestrianTrafficLights = new TrafficLightBase(this);
    m_carTrafficLightsMain = new TrafficLight(this);
    m_carTrafficLightsMain->setIsMainStreet(true);
    m_carTrafficLightsSide = new TrafficLight(this);

    m_sm->setObjectName("State Machine Traffic Light Manager");
    m_stateInit->setObjectName("State Init");
    m_stateMainStreet->setObjectName("State Main Street");
    m_stateSideStreet->setObjectName("State Side Street");
    m_statePedestrian1->setObjectName("State Pedestrian 1");
    m_statePedestrian2->setObjectName("State Pedestrian 2");
    m_stateFinish->setObjectName("State Finish");
    m_stateFinal->setObjectName("State Final");

    m_sm->addState(m_stateInit);
    m_sm->addState(m_stateMainStreet);
    m_sm->addState(m_stateSideStreet);
    m_sm->addState(m_statePedestrian1);
    m_sm->addState(m_statePedestrian2);
    m_sm->addState(m_stateFinish);

    m_sm->setInitialState(m_stateInit);

    connect(m_sm, &QStateMachine::started, this, [this]() { qDebug() << "State Machine Traffic Light Manager started"; });
    connect(m_sm, &QStateMachine::finished, this, [this]() { qDebug() << "State Machine Traffic Light Manager finished"; });

    connect(m_stateInit, &QState::entered, this, &TrafficLightManager::stateInit);
    connect(m_stateMainStreet, &QState::entered, this, &TrafficLightManager::stateMainStreet);
    connect(m_stateSideStreet, &QState::entered, this, &TrafficLightManager::stateSeideStreet);
    connect(m_statePedestrian1, &QState::entered, this, &TrafficLightManager::statePedestrian1);
    connect(m_statePedestrian2, &QState::entered, this, &TrafficLightManager::statePedestrian2);
    connect(m_stateFinish, &QState::entered, this, &TrafficLightManager::stateFinish);

    m_stateInit->addTransition(this, &TrafficLightManager::initDone, m_stateMainStreet);

    m_stateMainStreet->addTransition(this, &TrafficLightManager::mainStreetDone, m_stateSideStreet);
    m_stateMainStreet->addTransition(this, &TrafficLightManager::pedestrianRequest, m_statePedestrian1);

    m_stateSideStreet->addTransition(this, &TrafficLightManager::sideSteetDone, m_stateFinish);
    m_stateSideStreet->addTransition(this, &TrafficLightManager::pedestrianRequest, m_statePedestrian2);

    m_statePedestrian1->addTransition(this, &TrafficLightManager::pedestrianDone, m_stateSideStreet);
    m_statePedestrian2->addTransition(this, &TrafficLightManager::pedestrianDone, m_stateFinish);

    m_stateFinish->addTransition(this, &TrafficLightManager::finishDone, m_stateMainStreet);

    connect(m_pedestrianTrafficLights, &TrafficLightBase::done, this, [this]() {
        setRequestPedestrian(false);
        emit pedestrianDone();
    });
    connect(m_carTrafficLightsMain, &TrafficLight::done, this, [this]() {
        if (requestPedestrian) {
            emit pedestrianRequest();
            return;
        }
        emit mainStreetDone();
    });
    connect(m_carTrafficLightsSide, &TrafficLight::done, this, [this]() {
        if (requestPedestrian) {
            emit pedestrianRequest();
            return;
        }
        emit sideSteetDone();
    });
}

void TrafficLightManager::start()
{
    if (m_sm->isRunning()) {
        return;
    }

    m_sm->start();
}

TrafficLightBase *TrafficLightManager::getPedestrianTrafficLights() const
{
    return m_pedestrianTrafficLights;
}

void TrafficLightManager::setPedestrianTrafficLights(TrafficLightBase *value)
{
    if (m_pedestrianTrafficLights == value) {
        return;
    }
    m_pedestrianTrafficLights = value;
    emit pedestrianTrafficLightsChanged();
}

TrafficLight *TrafficLightManager::getCarTrafficLightsMain() const
{
    return m_carTrafficLightsMain;
}

void TrafficLightManager::setCarTrafficLightsMain(TrafficLight *value)
{
    if (m_carTrafficLightsMain == value) {
        return;
    }
    m_carTrafficLightsMain = value;
    emit carTrafficLightsMainChanged();
}

TrafficLight *TrafficLightManager::getCarTrafficLightsSide() const
{
    return m_carTrafficLightsSide;
}

void TrafficLightManager::setCarTrafficLightsSide(TrafficLight *value)
{
    if (m_carTrafficLightsSide == value) {
        return;
    }
    m_carTrafficLightsSide = value;
    emit carTrafficLightsSideChanged();
}

bool TrafficLightManager::getRequestPedestrian() const
{
    return requestPedestrian;
}

void TrafficLightManager::setRequestPedestrian(bool value)
{
    if (requestPedestrian == value) {
        return;
    }
    requestPedestrian = value;
    if (requestPedestrian) {
        mainStopRequest();
    }
    emit requestPedestrianChanged();
}

void TrafficLightManager::mainStopRequest()
{
    qDebug() << Q_FUNC_INFO;
    m_carTrafficLightsMain->setStopRequest(true);
}

void TrafficLightManager::stateInit()
{
    qDebug() << Q_FUNC_INFO;
    emit initDone();
}

void TrafficLightManager::stateMainStreet()
{
    qDebug() << Q_FUNC_INFO;
    m_carTrafficLightsMain->start();
}

void TrafficLightManager::stateSeideStreet()
{
    qDebug() << Q_FUNC_INFO;
    m_carTrafficLightsSide->start();
}

void TrafficLightManager::statePedestrian1()
{
    qDebug() << Q_FUNC_INFO;
    m_pedestrianTrafficLights->start();
}

void TrafficLightManager::statePedestrian2()
{
    qDebug() << Q_FUNC_INFO;
    m_pedestrianTrafficLights->start();
}

void TrafficLightManager::stateFinish()
{
    qDebug() << Q_FUNC_INFO;
    emit finishDone();
}
