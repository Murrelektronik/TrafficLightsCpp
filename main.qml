import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import TrafficLights
import QtQuick.Shapes

Window {
    width: 1000
    height: 740
    visible: true
    title: qsTr("Hello World")

    color: "#ddd"
    TrafficLightManager {
        id: manager
    }

    Text {
        id: title
        text: qsTr("Traffic Lights Demo")
        horizontalAlignment: Qt.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 20
        font.pixelSize: 36
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Rectangle {
        id: main
        color: "#999"
        width: 980
        height: 100
        x: 10
        y: 330
        Shape {
            anchors.centerIn: parent
            ShapePath {
                strokeWidth: 1
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [25, 25]
                startX: -470
                startY: 0
                PathLine {
                    x: 485
                    y: 0
                }
            }
        }
    }

    Rectangle {
        id: side
        color: "#999"
        width: 100
        height: 660
        x: 475
        y: 70
        Shape {
            anchors.centerIn: parent
            ShapePath {
                strokeWidth: 1
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [25, 25]
                startX: 0
                startY: -300
                PathLine {
                    x: 0
                    y: 310
                }
            }
        }
    }

    Rectangle {
        id: center
        color: "#999"
        width: 100
        height: 100
        x: 475
        y: 330

        // border {
        //     width: 1
        //     color: "red"
        // }
        Shape {
            anchors.centerIn: parent
            ShapePath {
                strokeWidth: 1
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [25, 25]
                startX: 0
                startY: -40
                PathLine {
                    x: 0
                    y: 35
                }
            }
        }
        Shape {
            anchors.centerIn: parent
            ShapePath {
                strokeWidth: 1
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [25, 25]
                startX: -40
                startY: 0
                PathLine {
                    x: 50
                    y: 0
                }
            }
        }
    }
    Rectangle {
        id: ped
        color: "#999"
        width: 150
        height: 100
        x: 710
        y: 330

        border {
            width: 1
            color: "white"
        }
        Shape {
            anchors.centerIn: parent
            ShapePath {
                strokeWidth: 15
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [2]
                startX: -67.5
                startY: -42
                PathLine {
                    x: 68
                    y: -42
                }
            }
            ShapePath {
                strokeWidth: 15
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [2]
                startX: -67.5
                startY: -15
                PathLine {
                    x: 68
                    y: -15
                }
            }
            ShapePath {
                strokeWidth: 15
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [2]
                startX: -67.5
                startY: 15
                PathLine {
                    x: 68
                    y: 15
                }
            }
            ShapePath {
                strokeWidth: 15
                strokeColor: "white"

                strokeStyle: ShapePath.DashLine
                dashPattern: [2]
                startX: -67.5
                startY: 42
                PathLine {
                    x: 68
                    y: 42
                }
            }
        }
    }
    Button {
        id: start
        text: "start"
        Material.background: "#1976d2"
        Material.foreground: "white"
        Material.roundedScale: Material.SmallScale
        x: 50
        y: 70
        onClicked: {
            console.log("Button clicked")
            manager.start()
        }
    }

    TrafficLightCar {
        x: 370
        y: 230
        trafficLight: manager.carTrafficLightsMain
        rotation: 90
    }

    TrafficLightCar {
        x: 585
        y: 440
        trafficLight: manager.carTrafficLightsSide
    }

    TrafficLightPedestrian {
        x: 755
        y: 185
        trafficLight: manager.pedestrianTrafficLights
    }
    MyButton {
        id: pestrian
        flat: true
        x: 750
        y: 260
        icon.source: "adjust.png"
        Material.elevation: 0
        onClicked: {
            console.log("Button clicked")
            manager.requestPedestrian = true
        }
    }
}
