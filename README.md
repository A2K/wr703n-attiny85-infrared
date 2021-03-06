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

![Solered wires](https://raw.githubusercontent.com/A2K/wr703n-attiny85-infrared/master/diagrams/WR703N_wiring.png)

ATtiny85 and LED circuit:

![LED wiring](https://raw.githubusercontent.com/A2K/wr703n-attiny85-infrared/master/diagrams/LED_wiring.png)

For transmitting volume control commands to the WR703N I am using [BetterTouchTool](http://www.boastr.net/) for binding custom hotkeys with "Execute Terminal Command" action like this:
    
    echo '+' | nc -u -w0 192.168.0.13 32000

