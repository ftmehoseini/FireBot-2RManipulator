# FireBot-2RManipulator

This project features the design and development of a two-link robotic arm aimed at extinguishing flames. This mechatronic system uses inverse kinematics, a sensor array, and motor controllers to detect and respond to environmental changes, effectively locating and extinguishing flames within a designated workspace.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [System Components](#system-components)
- [Software Architecture](#software-architecture)
- [Installation](#installation)
- [Video Demo](#video-demo)

## Project Overview
The **Firefighter Robotic Arm Project** leverages a two-link arm mechanism, equipped with servo motors and a flame sensor, to perform precise movements required to detect and extinguish flames. The robot utilizes an Arduino-based control system along with a Graphical User Interface (GUI) for real-time monitoring and control. The arm's movements are optimized for efficiency and responsiveness, capable of adapting to changing flame locations.

## Features
- **Dual-Link Arm**: Precisely controlled links enable reach across the workspace.
- **Flame Detection**: Utilizes a KY-026 Flame Sensor for accurate detection.
- **Trajectory Optimization**: Implements trajectory planning to smooth the arm's motion and enhance positioning accuracy.
- **Graphical User Interface (GUI)**: A MATLAB-based GUI provides real-time status updates on the arm’s position, detection accuracy, and operation speed.

## System Components
- **Arduino Uno**: Central control board.
- **Servos**: MG996R and SG5010 servos power the arm’s movement.
- **Flame Sensor**: KY-026 sensor detects flame presence and position.
- **Pump**: R385 DC water pump for extinguishing detected flames.
- **Motor Driver**: L298n module for driving high-voltage components.
- **Custom Mechanical Parts**: Laser-cut MDF links and 3D-printed brackets.

## Software Architecture
### Kinematics
- The project employs forward and inverse kinematics to determine the arm's movement.
  
### Control Algorithm
- A PID controller is implemented to fine-tune the motion and response speed of the arm to detected flames.
  
### Neural Network (Proposed but not Implemented)
- Initial trials with a neural network were considered for enhanced flame position prediction but faced limitations due to variable environmental conditions.

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/ftmehoseini/FireBot-2RManipulator
   cd FireBot-2RManipulator

## Video Demo
Watch the robot in action:
[![Watch the video](media/firebot.jpg)](/demo-firebot.mp4)
