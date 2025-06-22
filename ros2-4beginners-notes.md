# Introduction

Notes from Udemy course **ROS2 For Beginner (ROS Jazzy)**


# Set-up environment

## Ubuntu MV on Mac

We are using [multipass](https://canonical.com/multipass) for spinning an Ubuntu VM (noble version)


```bash
$ multipass launch --cpus 2 --memory 2G --disk 32G --name ros2-vm noble
```

[Set up a graphical interface](https://documentation.ubuntu.com/multipass/en/latest/how-to-guides/customise-multipass/set-up-a-graphical-interface/) so that we can use Windows Remote Access to access to the GUI of Ubuntu VM (for graphical simulations).

## Install ROS2 (Jazzy)

Use [Jazzy installation guides](https://docs.ros.org/en/jazzy/Installation.html) to install ROS2 dev environment and tools.

# ROS2 Topics

![ROS2 Topics](images/ros-topics.png)

# ROS2 Services - Client/Server Communication


