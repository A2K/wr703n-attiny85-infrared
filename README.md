This project implements Panasonic VSX-523 AV receiver infrared remote control over network protocols.

Hardware components:
- TP-Link WR703N router
- ATtiny85 microcontroller
- Vishay 5mm infrared LED
- 2N2222 transistor
- Two 5.6k Ohm resistors
- One 100 Ohm resistor

WR703N is used for WiFi connectivity, multiple network protocols support and I2C bus control.
ATtiny85 is used for infrared protocol implementation.

Joris Pragt has a great article on soldering I2C and power wires to WR703N in his blog:
http://pragti.ch/kippycam/2012/08/15/Adding-an-I2C-interface-to-the-TL-WR703N/

Here is a backup copy of the photo of soledered wires from that article:

![Solered wires](https://raw.github.com/A2K/wr703n-attiny85-infrared/diagrams/WR703N_wiring.png)

ATtiny85 and LED circuit:

![LED circuit](https://raw.github.com/A2K/wr703n-attiny85-infrared/diagrams/LED_wiring.png)

