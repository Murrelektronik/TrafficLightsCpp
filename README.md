# Traffice Lights Demo

The Traffic Lights Demo project is a small simulation of a traffic light system implemented in C++ using the Qt framework. It showcases the functionality of a basic traffic light control system, including the transition between red, yellow, and green lights according to predefined timing intervals.

This project serves as a simple demonstration of how traffic lights function and can be useful for educational purposes or as a starting point for more complex traffic management simulations. It provides a visual representation of traffic light behavior and can be easily extended or modified for different scenarios or experiments related to traffic flow control.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Building from Source](#building-from-source)
  - [Dependencies](#dependencies)
  - [Build Instructions](#build-instructions)
- [License](#license)

## Introduction

A brief introduction to the project and its purpose.

## Features

- List of features or functionalities of the project.

## Requirements

List of dependencies or prerequisites needed to build and run the project.

## Building from Source

### Dependencies

- CMake installe (Version 3.16 or newer)
- Qt-Libraries installed (Version 6.6.0 or newer)
- A C++-Compiler (i.E. GCC, Clang, MSVC, etc.)

### Build Instructions

1. Clone the repository:

```bash
git clone https://github.com/Murrelektronik/TrafficLightsCpp.git
```

2. Change Directory:

```bash
cd TrafficLightsCpp
```

3. Configure:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=<path to qt libraries>
```

4. Build:

```bash
cmake --build build --config Release
```

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/Murrelektronik/TrafficLightsCpp/blob/master/License)



