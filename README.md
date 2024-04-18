# Audible UV meter

Ultraviolet radiation exposure monitoring with acoustic feedback as a wearable UV sensor solution for blind/visually impaired people:
A simple "audible UV meter" application for a Seeed Studio Wio Terminal and a GUVA-S12SD analog UV sensor ...

## Introduction

Prolonged exposure to ultraviolet (UV) radiation from the sun poses a health risk to the skin and eyes that can lead to premature aging and even cancer.

Individuals with visual impairment may not perceive visual cues like shadows or changes in sunlight intensity. They might not realize when they are exposed to direct sunlight or when UV levels are high. While people usually may get a 'visual impression' of their exposure to intense sunlight, blind people might miss this especially when e.g. cool air, windchill, etc. also prevents the sensation of warmth on exposed skin.
Without visual cues, it's harder to assess the need for sun protection and to recognize the importance of sunscreen, hats, or sunglasses.

 With this in mind, the idea is to design a prototype of a wearable or portable UV index meter with audible notification for blind people.

The proposed solution implements the prototype of an UV radiation exposure monitoring application to assist in the prevention of diseases caused by over exposition to solar UV radiation. Like a usual UV meter, it measures the current intensity level of ultraviolet radiation and (optionally) displays it together with the corresponding UV index and risk level. Additionally it also gives an audible *representation* of the UV index as sequence of tones.

## Setup

The solution can be build with 

* a MCU board, operational power 3.3v - 5.v, at least one available analog pin and two available digital pins, Arduino development environment compatible
* a GUVA-S12D UV sensor board
* a buzzer
* a button switch
* a (rechargeable) battery

The prototype described here is based on a Seeed Studio Wio Terminal since this device already provides build in buttons, a build in buzzer and a TFT display for testing and demonstration purposes.

### Hardware

* [Seeed Studio Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* [DFRobot Gravity Analog UV Sensor V2](https://www.dfrobot.com/product-1273.html)

Optional:
* Seeed Studio Wio Terminal Chassis - Battery (650mAh)

### Wiring

The Gravity: GUVA-S12SD Analog UV Sensor comes with one Gravity: Analog Sensor Cable for Arduino with a 3 pin JST connector to connect to the sensor and a servo type connector with pins for signal (blue), GND (black) and PWR (red).

This sensor needs to connected to the MCU  Board as follows:

* **Signal** - blue wire - to A0
* **PWR** - red wire - to 3.3V / 5.0V
* **GND** - black wire - to GND

### Software / Libraries / Services

 * [Arduino IDE](https://www.arduino.cc/en/software)
 * [LvGL Graphics Library for Wio Terminal](https://github.com/Seeed-Studio/Seeed_Arduino_LvGL)
 * [Arduino library for the GUVA-S12SD UV sensor](https://github.com/dxcfl/arduino-library-GUVA_S12SD)

### Prerequisites

For building this projects the following prerequisites need to be
fulfilled:
 * All hardware components as listed above are available and at hand. 
 * The [Arduino IDE](https://www.arduino.cc/en/software) has been installed and configured for the Wio Terminal as described [here](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/#software).
 * All of the libraries listed above have been added to the Arduino IDE (S*ketch -&gt; Include Library -&gt; Manage Libraries / Add .ZIP Library*)

## Project Documentation

For a detailed description please see 

* the [Wiki](https://github.com/dxcfl/audible_uv_meter/wiki) or
* the project documentation [Audible UV Meter](https://www.hackster.io/dxcfl/audible-uv-meter-bfcbf3) at hackster.io

