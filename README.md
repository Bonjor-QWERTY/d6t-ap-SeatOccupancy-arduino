# d6t-application-SeatOccupancy-arduino
It is a sample projects for seat occupancy sensing by D6T OMRON MEMS Thermal Sensors and Arduino boards.

D6T sensor series are High Sensitivity Enables Detection
of Stationary Human Presence,

- OMRON's unique MEMS and ASIC technology achieve a high SNR.
- Superior noise immunity with a digital output.
- High-precision area temperature detection with low cross-talk field of
    view characteristics


## Description
this Arduino sample projects for acquiring data from sensors on 2JCIE-EV01.
sample projects output the sensor data to USB-Serial ports.

| example | description                | board   | status of sample code for Seat Occupancy |
|:-------:|:---------------------------|:--------|:-----------------------------------------|
| d6t-1a  | for the element type 1x1   | Arduino |:-----------------------------------------|
| d6t-8l  | for the element type 1x8   | Arduino |                Available                 |
| d6t-44l | for the element type 4x4   | Arduino |:-----------------------------------------|
| d6t-32l | for the element type 32x32 | Arduino |:-----------------------------------------|


## DEMO
sample output for D6T-8L

```
12:18:43.797 -> PTAT:24.1, Temperature:21.5,21.4,21.9,21.8,22.0,21.6,21.2,20.4 [degC], Occupancy:0
12:18:44.066 -> PTAT:24.1, Temperature:21.2,21.5,21.9,21.9,22.0,21.7,21.2,20.5 [degC], Occupancy:0
12:18:44.302 -> PTAT:24.1, Temperature:21.2,21.5,21.9,21.9,22.0,21.7,21.2,20.5 [degC], Occupancy:0
12:18:44.571 -> PTAT:24.1, Temperature:21.1,21.6,21.9,21.9,22.0,21.7,21.2,20.5 [degC], Occupancy:0
12:18:44.807 -> PTAT:24.1, Temperature:21.2,21.4,21.9,21.9,22.0,21.7,21.1,20.5 [degC], Occupancy:0
12:18:45.073 -> PTAT:24.2, Temperature:24.4,21.5,21.9,21.9,22.0,21.6,21.1,20.5 [degC], Occupancy:1
12:18:45.342 -> PTAT:24.1, Temperature:29.0,25.1,22.2,21.9,22.0,21.6,21.2,20.5 [degC], Occupancy:1
12:18:45.577 -> PTAT:24.2, Temperature:28.6,30.0,26.3,22.9,22.0,21.7,21.2,20.5 [degC], Occupancy:1
12:18:45.844 -> PTAT:24.2, Temperature:25.0,31.1,30.9,26.8,22.3,21.7,21.2,20.5 [degC], Occupancy:1
12:18:46.080 -> PTAT:24.2, Temperature:22.3,29.1,31.8,30.6,23.5,21.7,21.2,20.4 [degC], Occupancy:1
12:18:46.348 -> PTAT:24.1, Temperature:21.4,26.7,32.0,31.4,24.5,21.9,21.2,20.4 [degC], Occupancy:1
12:18:46.614 -> PTAT:24.2, Temperature:21.5,27.0,31.9,31.2,24.1,21.8,21.1,20.3 [degC], Occupancy:1
12:18:46.850 -> PTAT:24.2, Temperature:21.6,27.5,32.0,31.0,23.5,21.7,21.1,20.4 [degC], Occupancy:1
12:18:47.120 -> PTAT:24.2, Temperature:21.5,27.9,32.0,30.8,23.1,21.7,21.2,20.4 [degC], Occupancy:1
12:18:47.356 -> PTAT:24.3, Temperature:21.6,28.6,31.8,30.2,22.5,21.7,21.1,20.3 [degC], Occupancy:1
12:18:47.626 -> PTAT:24.2, Temperature:22.1,30.2,31.2,26.2,22.2,21.7,21.1,20.4 [degC], Occupancy:1
12:18:47.860 -> PTAT:24.2, Temperature:26.4,30.6,26.3,22.3,22.0,21.7,21.1,20.4 [degC], Occupancy:1
12:18:48.126 -> PTAT:24.2, Temperature:29.7,25.7,21.9,21.9,21.9,21.6,21.1,20.4 [degC], Occupancy:1
12:18:48.395 -> PTAT:24.2, Temperature:26.1,21.6,21.9,21.9,22.0,21.6,21.0,20.4 [degC], Occupancy:1
12:18:48.629 -> PTAT:24.3, Temperature:22.3,21.5,21.9,21.9,22.0,21.6,21.0,20.4 [degC], Occupancy:1
12:18:48.898 -> PTAT:24.2, Temperature:21.7,21.5,21.9,21.9,22.0,21.6,21.1,20.5 [degC], Occupancy:1
12:18:49.134 -> PTAT:24.3, Temperature:21.8,21.7,21.9,21.9,21.9,21.6,21.1,20.6 [degC], Occupancy:1
12:18:49.402 -> PTAT:24.2, Temperature:22.4,22.0,21.9,21.9,21.9,21.6,21.1,20.6 [degC], Occupancy:0
12:18:49.671 -> PTAT:24.2, Temperature:22.2,21.8,21.8,21.8,21.9,21.7,21.1,20.6 [degC], Occupancy:0
12:18:49.907 -> PTAT:24.3, Temperature:21.1,21.3,21.8,21.8,21.9,21.5,21.1,20.5 [degC], Occupancy:0

```


## Installation
see `https://www.arduino.cc/en/guide/libraries`

### Install from Arduino IDE
1. download .zip from this repo [releases](releases)
    or [master](archive/master.zip) .
2. Import the zip from Arduino IDE

3. Then, you can see the samples in `File >> Examples` menu.
   
4. Select examples for your favorite sensors, build and program to boards.

## Dependencies
None

## Links
- [RaspberryPi sample for D6T on 2JCIE-01-RP1](https://github.com/omron-devhub/d6t-2jcieev01-raspberrypi)

projects by another authors.

- [d6t-grove-tinkerboard project](https://github.com/omron-devhub/d6t-grove-tinkerboard)
- [d6t-grove-m5stack project](https://github.com/omron-devhub/d6t-grove-m5stack)
- [d6t-grove-arduino project](https://github.com/omron-devhub/d6t-grove-arduino)  
    only for element 4x4 type, but libralized.


## Licence
Copyright (c) OMRON Corporation. All rights reserved.

Licensed under the MIT License.

