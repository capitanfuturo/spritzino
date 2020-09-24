# Spritzino - an Arduino based bartender

**WORK IN PROGRESS**
Inspired by the work of [Hacker Shack](https://www.hackster.io/hackershack/smart-bartender-5c430e) I decided to make a smart bartender starting from an Arduino Nano. I live near Venice and my favourite aperitif is Spritz... so here we are.

If you are wondering what Spritz means then [Wikipedia](https://en.wikipedia.org/wiki/Spritz_Veneziano) could help me:

> A Spritz Veneziano (Austrian German: Spritzer, "splash" / "sparkling") or Aperol Spritz, also called just Spritz, is an Italian wine-based cocktail, commonly served as an aperitif in Northeast Italy. It consists of prosecco, Aperol and soda water.

## Stuff used for this project

I made a wooden case for the project but I don't really like it so I prefer not to enter the details in this readme. When I have some time I will improve this thing.
For the rest you must have the following components and the source code of this repository:

### Hardware

* Arduino Nano
* Arduino Motor Shield
* 12V power supplier
* DCDC converter 12V to 5V
* Peristaltic pump
* Jumper wires
* LCD 16x2 with I2C module

## How to

The following paragraphs describe how to wire all the components together.

### Arduino Nano Connections

| PIN | DESCRIPTION |
| --- | --- |
| GND | connected to general GND |
| 5V | connected to general 5V supply |
| A4 | connected to SDA LCD screen PIN  |
| A5 | connected to SCL LCD screen PIN  |
| D2 | connected to left button GND PIN |
| D3 | connected to right button GND PIN |
| D4 | connected to D4 motor shield PIN |
| D7 | connected to D7 motor shield PIN |
| D8 | connected to D8 motor shield PIN |
| D11 | connected to D11 motor shield PIN |
| D12 | connected to D12 motor shield PIN |

### Arduino Motor Shield

| PIN | DESCRIPTION |
| --- | --- |
| GND | connected to general GND |
| 5V | connected to general 5V supply |
| D4 | connected to D4 Arduino Nano PIN |
| D7 | connected to D7 Arduino Nano PIN |
| D8 | connected to D8 Arduino Nano PIN |
| D11 | connected to D11 Arduino Nano PIN |
| D12 | connected to D12 Arduino Nano PIN |
| EXT_POWER GND | connected to 12V power supply -V connector |
| EXT_POWER +M | connected to 12V power supply +V connector |
| M1, M2, M3, M4 | connected to 12V peristaltic motors |

### LCD 16x2

| PIN | DESCRIPTION |
| --- | --- |
| GND | connected to general GND |
| 5V | connected to general 5V supply |
| SDA | connected to A4 Arduino Nano PIN  |
| SCL | connected to A5 Arduino nano PIN  |

### BUTTON
| PIN | DESCRIPTION |
| --- | --- |
| LEFT BUTTON  | connected to D2 Arduino Nano PIN |
| RIGHT BUTTON  | connected to D3 Arduino Nano PIN |

### Hardware Schema

![Schema1](/assets/hw_schema.png)

### UI Schema

![Schema2](/assets/sw_flow.png)

## Photos

![1](/assets/1.jpg)

![2](/assets/2.jpg)

![3](/assets/3.jpg)

## How to contribute

If you like this project star it.

## Contacts

I'm not an expert of Arduino, but I like to learn stuff and try to share my experience. If you want to replicate this project and you have comments or advice feel free to contact me giuseppe.caliendo at gmail.

## Licence

MIT License

Copyright (c) 2020 Giuseppe Caliendo
