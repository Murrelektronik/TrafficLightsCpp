#pragma once

#include "trafficlightbase.h"
#include <QObject>
class QTimer;

class TrafficLight : public TrafficLightBase
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool yellow READ getYellow WRITE setYellow NOTIFY yellowChanged)
    Q_PROPERTY(int timeYellow READ getTimeYellow WRITE setTimeYellow NOTIFY timeYellowChanged)
    Q_PROPERTY(int timeRedYellow READ getTimeRedYellow WRITE setTimeRedYellow NOTIFY timeRedYellowChanged)
    Q_PROPERTY(int timeYellowAfterGreen READ getTimeYellowAfterGreen WRITE setTimeYellowAfterGreen NOTIFY timeYellowAfterGreenChanged)
    Q_PROPERTY(bool isMainStreet READ getIsMainStreet WRITE setIsMainStreet NOTIFY isMainStreetChanged)

public:
    explicit TrafficLight(QObject *parent = nullptr);

    bool getYellow() const;
    void setYellow(bool value);

    int getTimeYellow() const;
    void setTimeYellow(int value);

    int getTimeRedYellow() const;
    void setTimeRedYellow(int value);

    int getTimeYellowAfterGreen() const;
    void setTimeYellowAfterGreen(int value);

    bool getStopRequest() const;
    void setStopRequest(bool value);

    bool getIsMainStreet() const;
    void setIsMainStreet(bool value);

signals:
    void yellowChanged();

    // transitions
    void timeYellowDone();
    void timeRedYellowDone();
    void timeYellowAfterGreenDone();

    void timeYellowChanged();
    void timeRedYellowChanged();

    void timeYellowAfterGreenChanged();

    void isMainStreetChanged();

protected:
    bool m_yellow { false };
    int m_timeYellow { 1000 };
    int m_timeRedYellow { 1000 };
    int m_timeYellowAfterGreen { 2000 };
    int m_timeGreenMax { 20000 };
    QState *m_stateYellow { nullptr };
    QState *m_stateYellowAfterGreen { nullptr };
    QState *m_stateRedYellow { nullptr };
    bool m_stopRequest { false };
    bool m_minTimeDone { false };
    bool m_isMainStreet { false };
    QTimer *m_timerMaxTime { nullptr };
    void initTransitions();

    virtual void stateRed() override;
    virtual void stateGreen() override;
    virtual void stateFinish() override;
    void stateYellow();
    void stateYellowAfterGreen();
    void stateRedYellow();
    void clearTransisitions();

private:
};
