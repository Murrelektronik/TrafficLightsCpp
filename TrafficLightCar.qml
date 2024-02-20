import QtQuick
import TrafficLights

Rectangle {
    id: root
    property TrafficLight trafficLight
    width: 50
    height: 130
    color: "black"
    radius: 15
    Column {
        anchors.centerIn: parent
        spacing: 5
        Rectangle {
            id: red
            width: 30
            height: 30
            radius: 15
            color: trafficLight.red ? "red" : "#999"
        }
        Rectangle {
            id: yellow
            width: 30
            height: 30
            radius: 15
            color: trafficLight.yellow ? "yellow" : "#999"
        }
        Rectangle {
            id: green
            width: 30
            height: 30
            radius: 15
            color: trafficLight.green ? "lime" : "#999"
        }
    }
}
