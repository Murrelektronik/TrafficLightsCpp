cmake_minimum_required(VERSION 3.16)

project(TrafficLights VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick StateMachine REQUIRED)

qt_add_executable(appTrafficLights
    main.cpp
    trafficlightbase.h
    trafficlightbase.cpp
    trafficlight.h
    trafficlight.cpp
    trafficlightmanager.h
    trafficlightmanager.cpp
)

qt_add_qml_module(appTrafficLights
    URI TrafficLights
    VERSION 1.0
    QML_FILES
        main.qml
        TrafficLightCar.qml
        TrafficLightPedestrian.qml
    RESOURCES
        adjust.png
        QML_FILES MyButton.qml
)

set_target_properties(appTrafficLights PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTrafficLights
    PRIVATE Qt6::Quick Qt6::StateMachine)

install(TARGETS appTrafficLights
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
