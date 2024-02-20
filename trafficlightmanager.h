#pragma once

#include <QObject>
#include <QQmlEngine>

class TrafficLight;
class TrafficLightBase;
class QStateMachine;
class QState;
class QFinalState;

class TrafficLightManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(TrafficLightBase *pedestrianTrafficLights READ getPedestrianTrafficLights WRITE setPedestrianTrafficLights NOTIFY
                       pedestrianTrafficLightsChanged)
    Q_PROPERTY(TrafficLight *carTrafficLightsMain READ getCarTrafficLightsMain WRITE setCarTrafficLightsMain NOTIFY
                       carTrafficLightsMainChanged)
    Q_PROPERTY(TrafficLight *carTrafficLightsSide READ getCarTrafficLightsSide WRITE setCarTrafficLightsSide NOTIFY
                       carTrafficLightsSideChanged)
    Q_PROPERTY(bool requestPedestrian READ getRequestPedestrian WRITE setRequestPedestrian NOTIFY requestPedestrianChanged)
public:
    explicit TrafficLightManager(QObject *parent = nullptr);
    Q_INVOKABLE
    void start();

    TrafficLightBase *getPedestrianTrafficLights() const;
    void setPedestrianTrafficLights(TrafficLightBase *value);

    TrafficLight *getCarTrafficLightsMain() const;
    void setCarTrafficLightsMain(TrafficLight *value);

    TrafficLight *getCarTrafficLightsSide() const;
    void setCarTrafficLightsSide(TrafficLight *value);

    bool getRequestPedestrian() const;
    void setRequestPedestrian(bool value);
public slots:
    void mainStopRequest();

signals:
    void pedestrianTrafficLightsChanged();
    void carTrafficLightsMainChanged();
    void carTrafficLightsSideChanged();

    // transitions
    void initDone();
    void mainStreetDone();
    void sideSteetDone();
    void pedestrianRequest();
    void pedestrianDone();
    void finishDone();

    void requestPedestrianChanged();

private:
    TrafficLightBase *m_pedestrianTrafficLights;
    TrafficLight *m_carTrafficLightsMain;
    TrafficLight *m_carTrafficLightsSide;
    QStateMachine *m_sm { nullptr };
    QState *m_stateInit { nullptr };
    QState *m_stateMainStreet { nullptr };
    QState *m_stateSideStreet { nullptr };
    QState *m_statePedestrian1 { nullptr };
    QState *m_statePedestrian2 { nullptr };
    QState *m_stateFinish { nullptr };
    QFinalState *m_stateFinal { nullptr };
    bool requestPedestrian { false };

    void stateInit();
    void stateMainStreet();
    void stateSeideStreet();
    void statePedestrian1();
    void statePedestrian2();
    void stateFinish();
};
