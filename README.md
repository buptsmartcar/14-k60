# BUPT Smartcar Code Template for MK60
![](https://img.shields.io/badge/BUPTsmartcar-template__K60-brightgreen.svg)
> This is the template for K60 MCU
## What is it?
This is a example project or code template for BUPT smartcar. This project is created by integrating several old templates and some public libraries such as `VCAN(山外) 5.3`, together with some customized code for most common usecases. @Motren909 also made some necessary adjustments to it in order to make it more handy and easy to use.
## Why use it?
Using uniform code template makes it a lot easier for the leader to regulate and provide technical support for all the participants. During the early state, It will also substantially improve your coding efficiency as groups can discuss and exchange their ideas based on projects with similar coding style and variable names.
## How to use it
Simply open `vcan_Kinetis.eww` with `IAR workbench` of version 8.22 or later. For more details you can refer to other tutorials issued later targeting at IAR using or go and ask your Seniors(senpai) directly. Note that for some subtle issues (e.g., project settings, compiler and linker settings) when using IAR, please seek help from Google.

## Project structure
- APP
    + global.c/.h`global variables and constant values`
    + include.h`universal include file`
    + MK60_conf.c/.h`clock and PLL settings`
    + PORT_cfg.h`Pin Reference for each module`
    >This folder contains clock configuration files, global settings, main entry and pin reference for the project.
+ ChipDrivers
    >This folder contains drivers for each function module of the MCU. Normally you do not have to do anything with these files, that is, **No extra modification is needed**.
+ PeriDrivers
    >This folder contains user-specific drivers for your peripherals (外设，如LCD屏幕，超声波模块，陀螺仪等) . You can add your own drivers for your peripherals if needed. The existing files are official drivers from VCAN for their devices such as EagleEye camera, etc.
+ UserCode
    + **motor.c** `motor control`
    + **steer.c** `steer control`
    + img_control.c `image process and control`
    + Karman.c `a karman filter for mixing your gyro and accelerator`
    + control.c `inits and other`
    > This folder contains your own c files. You can play with this folder as you like. Note that there are already several files provided for you. Among them, `motor.c` and `steer.c` are the most important ones containing control algorithm (PID, in this case) for your motor and your steer. `img_control.c` is where you put your image processing algorihm, if you like. `Karman.c` is a off-the-shelf karman filter that can be used to mix data from gyro and acclerator. And `control.c` is a place where you put your code for initializing or other purpose.

## Contact us
    If you have any questions, feel free to reach me at Motren909@foxmail.com
    
